#include <QPainter>
#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize((CHESS_COLUMES+1)*RECT_WIDTH,(CHESS_ROWS+1)*RECT_HEIGHT);

    BlackTurn=true;
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *)
{
    DrawChessBoard();
    DrawChess();
    DrawItemWithMouse();

    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //获取鼠标点击处棋子点
    QPoint p;
    p.setX((event->pos().x())/RECT_WIDTH);
    p.setY((event->pos().y())/RECT_HEIGHT);

    //检测是否已存在棋子，若存在则返回
    for(int i=0;i<chesses.size();i++)
    {
        Chess chess=chesses[i];
        if(chess.pt==p)
            return;
    }
    //反之，就下子
    Chess chess(p,BlackTurn);
    chesses.append(chess);

    //统计是否已连成五子
    int LeftUp =    CountNearChess(chess,QPoint(-1,-1));
    int Up =        CountNearChess(chess,QPoint(0,-1));
    int RightUp =   CountNearChess(chess,QPoint(1,-1));
    int Left =      CountNearChess(chess,QPoint(-1,0));
    int Right =     CountNearChess(chess,QPoint(1,0));
    int LeftDown =  CountNearChess(chess,QPoint(-1,1));
    int Down =      CountNearChess(chess,QPoint(0,1));
    int RightDown = CountNearChess(chess,QPoint(1,1));
    if((Left+Right)>=4||
       (Up+Down)>=4||
       (LeftUp+RightDown)>=4||
       (RightUp+LeftDown)>=4)
    {
        QString str=BlackTurn? "Black":"White";
        QMessageBox::information(NULL,"GAME OVER",str,QMessageBox::Yes,QMessageBox::Yes);
        chesses.clear();

        return;
    }

    //qDebug()<<Left+Right<<" "<<Up+Down<<" "<<LeftUp+RightDown<<" "<<RightUp+LeftDown;

    //另一方落子
    BlackTurn=!BlackTurn;
}



void MainWindow::DrawChessBoard()
{
     QPainter painter(this);
    painter.setBrush(Qt::gray);
    painter.setPen(QPen(QColor(Qt::black),2));

    for(int i=0;i<CHESS_COLUMES;i++)
    {
        for(int j=0;j<CHESS_ROWS;j++)
        {
            painter.drawRect((i+0.5)*RECT_WIDTH,(j+0.5)*RECT_HEIGHT,RECT_WIDTH,RECT_HEIGHT);
        }
    }
}

void MainWindow::DrawChess()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));

    for(int i=0;i<chesses.size();i++)
    {
        Chess chess=chesses[i];
        if(chess.color)
            painter.setBrush(Qt::black);
        else
            painter.setBrush(Qt::white);

        DrawChessAtPoint(painter,chess.pt);
    }
}

void MainWindow::DrawItemWithMouse()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));

    if(BlackTurn)
        painter.setBrush(Qt::black);
    else
        painter.setBrush(Qt::white);

    painter.drawEllipse(mapFromGlobal(QCursor::pos()),RECT_WIDTH/2,RECT_HEIGHT/2);
}



void MainWindow::DrawChessAtPoint(QPainter &painter, QPoint &p)
{
    int r;
    r=RECT_WIDTH/2;
    r=(int)r*0.9;//棋子大小=格子*0.9

    QPoint pCenter((p.x()+0.5)*RECT_WIDTH,(p.y()+0.5)*RECT_HEIGHT);
    painter.drawEllipse(pCenter,r,r);
}


int MainWindow::CountNearChess(Chess chess, QPoint ptDirection)
{
    int nCount=0;
    chess.pt+=ptDirection;

    while(chesses.contains(chess))
    {
        nCount++;
        chess.pt+=ptDirection;
    }
    return nCount;
}


