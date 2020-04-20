#include "selectonlinebattletypewindow.h"
#include "ui_selectonlinebattletypewindow.h"

SelectOnLineBattleTypeWindow::SelectOnLineBattleTypeWindow(QMainWindow *mainWindow,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectOnLineBattleTypeWindow)
{
    this->mainWindow = mainWindow;
    initView();
}

void SelectOnLineBattleTypeWindow::initView(){
    ui->setupUi(this);

    setFixedSize(450,260);

    setWindowIcon(QIcon("E:\\Qt\\Qt_projects\\down\\QtWuziqi____\\res\\logo.png"));
    setWindowTitle("五子棋");
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap("E:\\Qt\\Qt_projects\\down\\QtWuziqi____\\res\\login_picture.png")
                   .scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(palette);
}

SelectOnLineBattleTypeWindow::~SelectOnLineBattleTypeWindow(){
    delete ui;
}

//进入房间按钮的槽函数，会监听进入房间按钮的click信号
void SelectOnLineBattleTypeWindow::on_btEnterRoom_clicked(){
    enterRoomConfigWindow = new EnterRoomConfigWindow(this);
    connect(enterRoomConfigWindow,SIGNAL(cancelEnterRoom()),this,SLOT(onCancelEnterRoom()));
    enterRoomConfigWindow->show();
    hide();
}

void SelectOnLineBattleTypeWindow::on_btCreateRoom_clicked(){
    connect(RemoteServiceUtil::getInstant(),SIGNAL(roomCreateSuccess(QString)),this,SLOT(onRoomCreateSuccess(QString)));
    connect(RemoteServiceUtil::getInstant(),SIGNAL(readRemoteData(QString)),this,SLOT(onReceiveRemoteData(QString)));
    RemoteServiceUtil::getInstant()->createRoom();
}

void SelectOnLineBattleTypeWindow::on_btCancel_clicked(){
    emit onlineBattleTypeSelectCancel();
}

void SelectOnLineBattleTypeWindow::onCancelEnterRoom(){
    if(enterRoomConfigWindow != nullptr){
        enterRoomConfigWindow->close();
        delete enterRoomConfigWindow;
    }
    show();
}

void SelectOnLineBattleTypeWindow::onRoomCreateSuccess(QString data){
    qDebug()<<"房间创建成功，进入准备游戏界面。";
    createRoomConfigWindow = new CreateRoomConfigWindow(data);
    connect(createRoomConfigWindow,SIGNAL(backRoom()),this,SLOT(onBackRoom()));
    connect(RemoteServiceUtil::getInstant(),SIGNAL(hasSomeOneConnectSuccess()),createRoomConfigWindow,SLOT(onSomeOneConnectSuccess()));
    hide();
    createRoomConfigWindow->show();
}

void SelectOnLineBattleTypeWindow::onBackRoom(){
    if(createRoomConfigWindow != nullptr){
        createRoomConfigWindow->close();
        delete createRoomConfigWindow;
        RemoteServiceUtil::getInstant()->releaseData();
    }
    show();
}

void SelectOnLineBattleTypeWindow::onReceiveRemoteData(QString data){
    qDebug()<<"接收到数据了 data = "<<QString(data);
}

