#include <QTime>
#include <QObject>
#include "clockhand.h"
#include "widget.h"

ClockHand::ClockHand(Widget *parent, int type)
{
    hType = type;
    chParent = parent;
}

void ClockHand::getHandCoords(QPointF &destPoint_1, QPointF &destPoint_2)
{
    qreal handAngle = 10;
    int radius = 10;

    QDateTime date = QDateTime::currentDateTime();
    QTime time = date.time();
    switch(hType)
    {
    case hTypeSec:
        handAngle = qDegreesToRadians((time.second() * 6)-90);
        radius = 10;
        break;
    case hTypeMin:
        handAngle = qDegreesToRadians((time.minute() * 6)-90);
        radius = 30;
        break;
    case hTypeHr:
        handAngle = qDegreesToRadians(((time.hour() - (time.hour() > 12 ? - 12 : + 0)) * 30)-90);
        radius = 50;
        break;
    default:
        break;
    }
    //TODO: use percentage of the clockradius for handlength
    qreal x = chParent->clockCenter.rx() + (chParent->clockRadius - radius) * qCos(handAngle);
    qreal y = chParent->clockCenter.ry() + (chParent->clockRadius - radius) * qSin(handAngle);
    QPointF destPoint_outer(x,y);
    qreal x1 = chParent->clockCenter.rx() + (chParent->clockRadius / 6) * qCos(handAngle+qDegreesToRadians(180.0));
    qreal y2 = chParent->clockCenter.ry() + (chParent->clockRadius / 6) * qSin(handAngle+qDegreesToRadians(180.0));
    QPointF destPoint_inner(x1,y2);
    destPoint_1 = destPoint_inner;
    destPoint_2 = destPoint_outer;

}

void ClockHand::draw(QPainter *painter)
{
    painter->setPen(QPen(Qt::white, 3));
    QPointF outer, inner;
    getHandCoords(inner, outer);
    painter->drawLine(chParent->clockCenter, inner);
    painter->drawLine(chParent->clockCenter, outer);
}
