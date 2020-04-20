#include "snowmanwindow.h"
#include "ui_snowmanwindow.h"

SnowManWindow::SnowManWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::SnowManWindow){
    ui->setupUi(this);
    initView();
}

void SnowManWindow::initView(){
    setFixedSize(600,600);

    setWindowIcon(QIcon("E:\\Qt\\Qt_projects\\down\\QtWuziqi____\\res\\logo.png"));
    setWindowTitle("五子棋");
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap("E:\\Qt\\Qt_projects\\down\\QtWuziqi____\\res\\login_picture.png")
                   .scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(palette);
}

void SnowManWindow::checkWindow(){
    if(gameWindow != nullptr){
        gameWindow->close();
        delete gameWindow;
    }
}

void SnowManWindow::on_btManMachineBattle_clicked(){
    checkWindow();
    gameWindow = new GameWindow(GameType::MAN_MACHINE_BATTLE,this);
    gameWindow->show();
    this->hide();
}

void SnowManWindow::on_btDoublePlay_clicked(){
    checkWindow();
    gameWindow = new GameWindow(GameType::DOUBLE_PLAY,this);
    gameWindow->show();
    this->hide();
}

void SnowManWindow::on_btOnlineBattle_clicked(){
    selectBattleTypeWindow = new SelectOnLineBattleTypeWindow(this);
    //关注了他的cancel信号，以便在选择Window里面点击cancel键之后能返回到SnowmanWindow主界面
    connect(selectBattleTypeWindow,SIGNAL(onlineBattleTypeSelectCancel()),this,SLOT(cancelOnlineBattle()));
    selectBattleTypeWindow->show();
    hide();
}
//监听SelectOnLineBattleTypeWindow的onlineBattleTypeSelectCancel信号，onlineBattleTypeSelectCancel是由cancel键被点击触发的
void SnowManWindow::cancelOnlineBattle(){
    qDebug()<<"到这里了 ";
    if(selectBattleTypeWindow != nullptr){
        selectBattleTypeWindow->close();
        delete selectBattleTypeWindow;
    }
    show();
}


SnowManWindow::~SnowManWindow(){
    delete ui;
}
