#ifndef CREATEROOMCONFIGWINDOW_H
#define CREATEROOMCONFIGWINDOW_H

#include <QMainWindow>
#include"GameWindow.h"
#include"remoteserviceutil.h"
namespace Ui {
class CreateRoomConfigWindow;
}

enum RoomConnectionStatus{
    NO_ONE,CONNECTED
};


class CreateRoomConfigWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateRoomConfigWindow(QString data,QWidget *parent = nullptr);
    ~CreateRoomConfigWindow();

signals:
    void backRoom();
private slots:
    void onSomeOneConnectSuccess();
    void on_btBackRoom_clicked();

    void on_btStartGame_clicked();

private:
    Ui::CreateRoomConfigWindow *ui;
    RoomConnectionStatus connectStatus;
    QString roomNumber;
    GameWindow *gameWindow;
};

#endif // CREATEROOMCONFIGWINDOW_H
