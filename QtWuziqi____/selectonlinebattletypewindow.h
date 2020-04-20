#ifndef SELECTONLINEBATTLETYPEWINDOW_H
#define SELECTONLINEBATTLETYPEWINDOW_H

#include <QMainWindow>
#include"enterroomconfigwindow.h"
#include"createroomconfigwindow.h"

namespace Ui {
class SelectOnLineBattleTypeWindow;
}

class SelectOnLineBattleTypeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectOnLineBattleTypeWindow(QMainWindow *mainWindow,QWidget *parent = nullptr);
    ~SelectOnLineBattleTypeWindow();
    void initView();

signals:
     void onlineBattleTypeSelectCancel();

private slots:
    void on_btEnterRoom_clicked();

    void on_btCreateRoom_clicked();
    void onBackRoom();
    void on_btCancel_clicked();
    void onCancelEnterRoom();
    void onReceiveRemoteData(QString);
    void onRoomCreateSuccess(QString);

private:
    Ui::SelectOnLineBattleTypeWindow *ui;
    EnterRoomConfigWindow* enterRoomConfigWindow;
    CreateRoomConfigWindow * createRoomConfigWindow;
    QMainWindow *mainWindow;
};

#endif // SELECTONLINEBATTLETYPEWINDOW_H
