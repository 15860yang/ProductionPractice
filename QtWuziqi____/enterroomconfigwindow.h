#ifndef ENTERROOMCONFIGWINDOW_H
#define ENTERROOMCONFIGWINDOW_H

#include <QMainWindow>
#include"remoteserviceutil.h"
#include"GameWindow.h"


namespace Ui {
class EnterRoomConfigWindow;
}

class EnterRoomConfigWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void cancelEnterRoom();

public:
    explicit EnterRoomConfigWindow(QMainWindow *selectOnLineBattleTypeWindow,QWidget *parent = nullptr);
    ~EnterRoomConfigWindow();

private slots:
    void on_btConnectRoom_clicked();

    void on_btCancelConnect_clicked();
    void resolveRemoteData(QString data);
    void onRoomConnected();
private:
    Ui::EnterRoomConfigWindow *ui;
    QMainWindow *selectOnLineBattleTypeWindow;

    GameWindow *gameWindow = nullptr;
};

#endif // ENTERROOMCONFIGWINDOW_H
