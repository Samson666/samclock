#ifndef CLOCKHAND_H
#define CLOCKHAND_H

#include <QObject>
#include <QPen>
#include <QWidget>

class Widget;

class ClockHand
{
public:

    enum handType
    {
        sec = 1,
        min = 2,
        hr = 3
    };

    enum handSize
    {
        sizeSec = 90,
        sizeMin = 70,
        sizeHr = 50
    };


    ClockHand(Widget *parent = nullptr, const handType type = sec);
    //Draw the clockhand

    //Calculate the coordinates of the endpoint of the clockpoint


    //Type of hands
    constexpr static int hTypeSec = 1;
    constexpr static int hTypeMin = 2;
    constexpr static int hTypeHr = 3;
    //Length of Clockhands in percent of the radius
    constexpr static qreal lenSec = 90;
    constexpr static qreal lenMin = 70;
    constexpr static qreal lenHr = 50;

    friend class Widget;


signals:

private:
    int hType;
    int len;
    int width;
    Widget *chParent;
    QPen pen;
    QPolygonF *handPolygon;

    void draw(QPainter *painter);
    void getHandCoords(QPointF&, QPointF&);
};

#endif // CLOCKHAND_H
