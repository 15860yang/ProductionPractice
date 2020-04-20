#include "createroomconfigwindow.h"
#include "ui_createroomconfigwindow.h"

CreateRoomConfigWindow::CreateRoomConfigWindow(QString data,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateRoomConfigWindow)
{
    this->roomNumber = data;
    ui->setupUi(this);
    ui->labelRoomNumber->setText(data);
    connectStatus = RoomConnectionStatus::NO_ONE;
    setWindowIcon(QIcon("E:\\Qt\\Qt_projects\\down\\QtWuziqi____\\res\\logo.png"));
    setWindowTitle("五子棋");
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap("E:\\Qt\\Qt_projects\\down\\QtWuziqi____\\res\\login_picture.png")
                   .scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(palette);
}

CreateRoomConfigWindow::~CreateRoomConfigWindow(){
    delete ui;
}

void CreateRoomConfigWindow::on_btBackRoom_clicked(){
    emit backRoom();
}

void CreateRoomConfigWindow::onSomeOneConnectSuccess(){
    connectStatus = RoomConnectionStatus::CONNECTED;
    ui->labelRoomConnectionInfo->setText("有人连接到房间了");
}

void CreateRoomConfigWindow::on_btStartGame_clicked(){
    if(connectStatus == RoomConnectionStatus::NO_ONE){
        return;
    }else if(connectStatus == RoomConnectionStatus::CONNECTED){
        qDebug()<<"开始游戏  写信息";
        RemoteServiceUtil::getInstant()->writeData("startGame");
        gameWindow = new GameWindow(GameType::ONLINE_BATTLE,this,PlayerStatus::YOU);
        connect(RemoteServiceUtil::getInstant(),SIGNAL(readRemoteData(QString)),gameWindow,SLOT(resolveRemoteData(QString)));
        hide();
        gameWindow->show();
    }
}
