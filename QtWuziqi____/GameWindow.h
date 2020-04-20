#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Game.h"
#include<QMenuBar>
#include<QPainter>
#include<QMouseEvent>
#include <math.h>
#include"remoteserviceutil.h"

class GameWindow : public QMainWindow{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = 0);
    GameWindow(GameType type,QMainWindow* window, PlayerStatus playerStatus = PlayerStatus::YOU);

    ~GameWindow();
protected:
    // 绘制
    void paintEvent(QPaintEvent *event);
    // 监听鼠标移动情况，方便落子
    void mouseMoveEvent(QMouseEvent *event);
    // 实际落子
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Game *game; // 游戏指针
    int clickPosRow, clickPosCol; // 存储将点击的位置
    QMainWindow *window;
    int toInt(QString data);
    void initGame(GameType gameType,PlayerStatus playerStatus = PlayerStatus::YOU);
    void initMenu();
    bool checkGameStatus();
private slots:
    void chessOneByPerson(); // 人执行
    void triggerMenu(QAction *action);
    void gameOver(GameOverType type);
    void resolveRemoteData(QString);
};

#endif // MAINWINDOW_H
