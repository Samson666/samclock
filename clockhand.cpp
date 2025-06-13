#include <QTime>
#include <QObject>
#include "clockhand.h"
#include "widget.h"
#include <QGradient>

ClockHand::ClockHand(Widget *parent, const handType type)
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
    case sec:
        handAngle = qDegreesToRadians(((time.second()+ (chParent->hasSweepingSecondHand ? time.msec()/1000.0 : 0.0)) * 6.0)-90.0);
        radius = 10;
        break;
    case min:
        handAngle = qDegreesToRadians((time.minute() * 6)-90);
        radius = 30;
        break;
    case hr:
        handAngle = qDegreesToRadians((((time.hour() - (time.hour() > 12.0 ? - 12.0 : + 0))+(time.minute()/60.0)) * 30.0)-90.0);
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
    //painter->setPen(QPen(Qt::gray, 10,Qt::SolidLine,chParent->hasRoundedHandEdges ? Qt::RoundCap : Qt::SquareCap));
    QPen p(Qt::gray, 10,Qt::SolidLine,chParent->hasRoundedHandEdges ? Qt::RoundCap : Qt::SquareCap);
    QGradient g(QGradient::Preset::MarbleWall);
    QBrush b(g);
    p.setBrush(b);
    painter->setPen(p);
    QPointF outer, inner;
    getHandCoords(inner, outer);
    painter->drawLine(chParent->clockCenter, inner);
    painter->drawLine(chParent->clockCenter, outer);
}
