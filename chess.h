#ifndef CHESS_H
#define CHESS_H

#include <QPoint>

class Chess
{
public:
    Chess();
    Chess(QPoint p,bool bBlack);//reload
    ~Chess();

    bool operator==(const Chess &t) const
    {
        return ((pt==t.pt)&&(color==t.color));
    }

    QPoint pt;//圆心坐标
    bool color;//棋子颜色，因为只有黑白两色，故使用bool值
};

#endif // CHESS_H
