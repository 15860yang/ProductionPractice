#ifndef SNOWMANWINDOW_H
#define SNOWMANWINDOW_H

#include <QMainWindow>
#include"GameWindow.h"
#include"selectonlinebattletypewindow.h"
namespace Ui {
class SnowManWindow;
}

class SnowManWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SnowManWindow(QWidget *parent = nullptr);
    ~SnowManWindow();
    void initView();
    void checkWindow();
private slots:
    void on_btManMachineBattle_clicked();

    void on_btDoublePlay_clicked();

    void on_btOnlineBattle_clicked();
    void cancelOnlineBattle();
private:
    Ui::SnowManWindow *ui;
    QMainWindow *gameWindow = nullptr;
    SelectOnLineBattleTypeWindow* selectBattleTypeWindow = nullptr;

};

#endif // SNOWMANWINDOW_H
