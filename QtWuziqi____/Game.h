#ifndef GAMEMODEL_H
#define GAMEMODEL_H

// ---- 五子棋游戏模型类 ---- //
#include <vector>
#include <utility>
#include <stdlib.h>
#include <QMessageBox>
#include <QSound>
#include <QDebug>
#include<QMainWindow>
#include <QTimer>
//#include"GameWindow.h"
#include"remoteserviceutil.h"

#define CHESS_ONE_SOUND ":/res/sound/chessone.wav"
#define WIN_SOUND ":/res/sound/win.wav"
#define LOSE_SOUND ":/res/sound/lose.wav"

// 游戏类型，双人还是AI（目前固定让AI下黑子）
enum GameType
{
    ONLINE_BATTLE,//联机对战
    MAN_MACHINE_BATTLE,
    DOUBLE_PLAY,
};

// 游戏状态
enum GameStatus
{
    PLAYING,
    FINISH
};

enum PlayerStatus{
    YOU,
    OTHER
};

enum GameOverType{
    WIN,LOSE,DRAW
};


class Game:public QObject{
    Q_OBJECT

public:
    Game(GameType gameType,QMainWindow* window);

signals:
    void gameOver(GameOverType);


public:
    std::vector<std::vector<int>> gameMapVec; // 存储当前游戏棋盘和棋子的情况,空白为0，白子1，黑子-1
    std::vector<std::vector<int>> scoreMapVec; // 存储各个点位的评分情况，作为AI下棋依据

    QMainWindow* window;

    PlayerStatus playerStatus;
    GameType gameType; // 游戏模式
    GameStatus gameStatus; // 游戏状态

    void startGame(); // 开始游戏
    void calculateScore(); // 计算评分
    void actionByPerson(int row, int col); // 人执行下棋
    void actionByAI(int &clickRow, int &clickCol); // 机器执行下棋
    void updateGameMap(int row, int col); // 每次落子后更新游戏棋盘
    bool isWin(int row, int col); // 判断游戏是否胜利
    bool isDeadGame(); // 判断是否和棋

    static int kBoardMargin; // 棋盘边缘空隙
    static int kRadius; // 棋子半径
    static int kMarkSize; // 落子标记边长
    static int kBlockSize; // 格子的大小
    static int kPosDelta; // 鼠标点击的模糊距离上限
    static int kAIDelay; // AI下棋的思考时间
    static int kBoardSizeNum;// 棋盘尺寸

    void chessOneByAI();// AI下棋
};

#endif // GAMEMODEL_H
