#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QVector>

#include "chess.h"

//定义一些常量
#define CHESS_ROWS     15
#define CHESS_COLUMES  15
#define RECT_WIDTH     50
#define RECT_HEIGHT    50

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
private:
    void DrawChessBoard();
    void DrawChess();
    void DrawItemWithMouse();

    void DrawChessAtPoint(QPainter &painter,QPoint &p);

    int CountNearChess(Chess chess,QPoint ptDirection);

    QVector<Chess> chesses;
    bool BlackTurn;   //当前该黑棋下


};

#endif // MAINWINDOW_H
