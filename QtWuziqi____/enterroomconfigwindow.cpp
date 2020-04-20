#include "enterroomconfigwindow.h"
#include "ui_enterroomconfigwindow.h"

EnterRoomConfigWindow::EnterRoomConfigWindow(QMainWindow *selectOnLineBattleTypeWindow,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EnterRoomConfigWindow)
{
    this->selectOnLineBattleTypeWindow = selectOnLineBattleTypeWindow;
    ui->setupUi(this);
    ui->labelConnectSuccess->setVisible(false);
    setWindowIcon(QIcon("E:\\Qt\\Qt_projects\\down\\QtWuziqi____\\res\\logo.png"));
    setWindowTitle("五子棋");
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap("E:\\Qt\\Qt_projects\\down\\QtWuziqi____\\res\\login_picture.png")
                   .scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(palette);
}

EnterRoomConfigWindow::~EnterRoomConfigWindow(){
    delete ui;
}

void EnterRoomConfigWindow::on_btConnectRoom_clicked(){
    QStringList strList = ui->etRoomNumber->text().split("#");
    connect(RemoteServiceUtil::getInstant(),SIGNAL(roomConnected()),this,SLOT(onRoomConnected()));
    connect(RemoteServiceUtil::getInstant(),SIGNAL(readRemoteData(QString)),this,SLOT(resolveRemoteData(QString)));
    RemoteServiceUtil::getInstant()->connectToRemoteServer(strList[0],strList[1].toUShort());
}

void EnterRoomConfigWindow::onRoomConnected(){
    qDebug()<<"房间连接成功了";
    ui->labelConnectSuccess->setVisible(true);
}

void EnterRoomConfigWindow::resolveRemoteData(QString data){
    qDebug()<<"接收到消息了 ： "<<data;
    if(QString(data) == "startGame" && !isHidden()){
        gameWindow = new GameWindow(GameType::ONLINE_BATTLE,this,PlayerStatus::OTHER);
        hide();
        connect(RemoteServiceUtil::getInstant(),SIGNAL(readRemoteData(QString)),gameWindow,SLOT(resolveRemoteData(QString)));
//        disconnect(RemoteServiceUtil::getInstant(),SIGNAL(readRemoteData(QString)),this,SLOT(resolveRemoteData(QString)));
        gameWindow->show();
    }
}

void EnterRoomConfigWindow::on_btCancelConnect_clicked(){
    emit cancelEnterRoom();
}
