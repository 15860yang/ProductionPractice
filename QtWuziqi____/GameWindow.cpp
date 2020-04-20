#include "GameWindow.h"

// -------全局遍历-------//
#define CHESS_ONE_SOUND ":/res/sound/chessone.wav"
#define WIN_SOUND ":/res/sound/win.wav"
#define LOSE_SOUND ":/res/sound/lose.wav"

// -------------------- //

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent){
    // 设置棋盘大小
    setFixedSize(Game::kBoardMargin * 2 + Game::kBlockSize * Game::kBoardSizeNum, Game::kBoardMargin * 2 + Game::kBlockSize * Game::kBoardSizeNum);
    // 开启鼠标hover功能，这两句一般要设置window的
    setMouseTracking(true);
    initMenu();
}

GameWindow::GameWindow(GameType type, QMainWindow* window, PlayerStatus playerStatus): QMainWindow(nullptr){
    this->window = window;
    // 设置棋盘大小
    setFixedSize(Game::kBoardMargin * 2 + Game::kBlockSize * Game::kBoardSizeNum, Game::kBoardMargin * 2 + Game::kBlockSize * Game::kBoardSizeNum);
    // 开启鼠标hover功能，这两句一般要设置window的
    setMouseTracking(true);

    initMenu();
    initGame(type,playerStatus);
}


void GameWindow::initMenu(){
    // 添加菜单
    QMenu *gameMenu = menuBar()->addMenu(tr("游戏")); // menuBar默认是存在的，直接加菜单就可以了
    QAction *actionPVP = new QAction("认输", this);
    gameMenu->addAction(actionPVP);

    connect(menuBar(),SIGNAL(triggered(QAction*)),this,SLOT(triggerMenu(QAction*)));
}

void GameWindow::triggerMenu(QAction* action){
    if(action->text() == "认输"){
        game->gameStatus = GameStatus::FINISH;
        if(game->gameType == GameType::ONLINE_BATTLE){
            RemoteServiceUtil::getInstant()->writeData("gameOver#000");
        }
        gameOver(GameOverType::LOSE);
    }
}

void GameWindow::initGame(GameType gameType,PlayerStatus playerStatus){
    // 初始化游戏模型
    game = new Game(gameType,this);
    game->gameStatus = GameStatus::PLAYING;
    connect(game,SIGNAL(gameOver(GameOverType)),this,SLOT(gameOver(GameOverType)));
    game->playerStatus = playerStatus;
    game->startGame();
    update();
}

void GameWindow::resolveRemoteData(QString data){
    qDebug()<<"客户端接收到另一方发来的消息 "<<data;
    QStringList ls = data.split("#");
    if(ls[0] == "step"){
        int row = toInt(ls[1]);
        int col = toInt(ls[2]);
        qDebug()<<"row = "<<row<<",col = "<<col;
        game->actionByPerson(row, col);
        QSound::play(CHESS_ONE_SOUND);
        // 重绘
        update();
        game->playerStatus = PlayerStatus::YOU;
        if(game->isWin(row,col)){
            emit gameOver(GameOverType::LOSE);
        }
    }else if(ls[0] == "gameOver"){
        if(game->gameStatus == GameStatus::FINISH){
            return;
        }
        game->gameStatus = GameStatus::FINISH;
        QSound::play(WIN_SOUND);
        QMessageBox::about(window,"游戏结束","对方认输");
        this->close();
        window->show();
    }
}

int GameWindow::toInt(QString data){
    int res = 0;
    std::string sss = data.toLatin1().toStdString().c_str();
    for(int i = 0; i < sss.size() ;i++){
        res = res*10 + (int)(sss[i]);
    }
    return res;
}

void GameWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
//    QPen pen; // 调整线条宽度
//    pen.setWidth(2);
//    painter.setPen(pen);
    for (int i = 0; i < Game::kBoardSizeNum + 1; i++){
        painter.drawLine(Game::kBoardMargin + Game::kBlockSize * i,
                         Game::kBoardMargin, Game::kBoardMargin + Game::kBlockSize * i, size().height() - Game::kBoardMargin);
        painter.drawLine(Game::kBoardMargin, Game::kBoardMargin + Game::kBlockSize * i,
                         size().width() - Game::kBoardMargin, Game::kBoardMargin + Game::kBlockSize * i);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    // 绘制落子标记(防止鼠标出框越界)
    if (clickPosRow > 0 && clickPosRow < Game::kBoardSizeNum &&
        clickPosCol > 0 && clickPosCol < Game::kBoardSizeNum &&
        game->gameMapVec[clickPosRow][clickPosCol] == 0){
        if (game->playerStatus == YOU){
            brush.setColor(Qt::white);
        }else{
            brush.setColor(Qt::black);
        }
        painter.setBrush(brush);
        painter.drawRect(Game::kBoardMargin + Game::kBlockSize * clickPosCol - Game::kMarkSize / 2, Game::kBoardMargin + Game::kBlockSize * clickPosRow - Game::kMarkSize / 2, Game::kMarkSize, Game::kMarkSize);
    }

    // 绘制棋子 
    for (int i = 0; i < Game::kBoardSizeNum; i++)
        for (int j = 0; j < Game::kBoardSizeNum; j++)
        {
            if (game->gameMapVec[i][j] == 1) {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(Game::kBoardMargin + Game::kBlockSize * j - Game::kRadius,
                                    Game::kBoardMargin + Game::kBlockSize * i - Game::kRadius, Game::kRadius * 2, Game::kRadius * 2);
            }
            else if (game->gameMapVec[i][j] == -1){
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(Game::kBoardMargin + Game::kBlockSize * j - Game::kRadius,
                                    Game::kBoardMargin + Game::kBlockSize * i - Game::kRadius, Game::kRadius * 2, Game::kRadius * 2);
            }
        }
    painter.end();
}

bool GameWindow::checkGameStatus(){
    if(game->gameStatus == FINISH){
        return false;
    }
    return true;
}

void GameWindow::mouseMoveEvent(QMouseEvent *event){
    if(!checkGameStatus())return;
    // 通过鼠标的hover确定落子的标记
    int x = event->x();
    int y = event->y();

    // 棋盘边缘不能落子
    if (x >= Game::kBoardMargin + Game::kBlockSize / 2 &&
            x < size().width() - Game::kBoardMargin &&
            y >= Game::kBoardMargin + Game::kBlockSize / 2 &&
            y < size().height()- Game::kBoardMargin)
    {
        // 获取最近的左上角的点
        int col = x / Game::kBlockSize;
        int row = y / Game::kBlockSize;

        int leftTopPosX = Game::kBoardMargin + Game::kBlockSize * col;
        int leftTopPosY = Game::kBoardMargin + Game::kBlockSize * row;

        // 根据距离算出合适的点击位置,一共四个点，根据半径距离选最近的
        clickPosRow = -1; // 初始化最终的值
        clickPosCol = -1;
        int len = 0; // 计算完后取整就可以了

        // 确定一个误差在范围内的点，且只可能确定一个出来
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < Game::kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - Game::kBlockSize) * (x - leftTopPosX - Game::kBlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < Game::kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col + 1;
        }
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - Game::kBlockSize) * (y - leftTopPosY - Game::kBlockSize));
        if (len < Game::kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - Game::kBlockSize) * (x - leftTopPosX - Game::kBlockSize) + (y - leftTopPosY - Game::kBlockSize) * (y - leftTopPosY - Game::kBlockSize));
        if (len < Game::kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
        }
        // 存了坐标后也要重绘
        update();
    }
}

void GameWindow::gameOver(GameOverType type){
    if(type == GameOverType::WIN){
        QSound::play(WIN_SOUND);
        QMessageBox::about(window,"游戏结束","你赢了");
    }if(type == GameOverType::LOSE){
        QSound::play(LOSE_SOUND);
        QMessageBox::about(window,"游戏结束","你输了");
    }if(type == GameOverType::DRAW){
        QSound::play(LOSE_SOUND);
        QMessageBox::about(window,"游戏结束","平局");
    }
    window->show();
    this->close();
}

void GameWindow::mouseReleaseEvent(QMouseEvent *event){
    if(!checkGameStatus())return;
    // 人机下棋，并且不能抢机器的棋
    if(game->gameType == MAN_MACHINE_BATTLE){
        if(game->playerStatus == YOU){
            chessOneByPerson();
        }
    }else if (game->gameType == DOUBLE_PLAY) {
        chessOneByPerson();
    }else if(game->gameType == ONLINE_BATTLE){
        if(game->playerStatus == YOU){
            chessOneByPerson();
        }
    }
}

void GameWindow::chessOneByPerson(){
    // 根据当前存储的坐标下子
    // 只有有效点击才下子，并且该处没有子
    if (clickPosRow != -1 && clickPosCol != -1 && game->gameMapVec[clickPosRow][clickPosCol] == 0){

        if(game->gameType == GameType::ONLINE_BATTLE){
            //如果是联机对战的话，在重绘之后就要把结果发送到另一端了
            QString data;
            qDebug()<<"clickPosRow = "<<clickPosRow<<",clickPosCol = "<<clickPosCol;
            data.append("step").append("#").append((char)clickPosRow).append("#").append((char)clickPosCol);
            RemoteServiceUtil::getInstant()->writeData(data);
        }

        game->actionByPerson(clickPosRow, clickPosCol);
        QSound::play(CHESS_ONE_SOUND);
        // 重绘
        update();
    }
}

GameWindow::~GameWindow(){
    if (game){
        delete game;
        game = nullptr;
    }
}
