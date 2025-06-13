#include <QObject>
#include "clockdial.h"
#include "widget.h"
#include <QDebug>

ClockDial::ClockDial(Widget *parent)
{
    cdParent = parent;
}

void ClockDial::getMarksStartEnd(QPointF &start, QPointF &end, qreal lineLength, qreal angle)
{
    qreal startX = cdParent->clockCenter.rx() + (cdParent->clockRadius) * qCos(angle);
    qreal startY = cdParent->clockCenter.ry() + (cdParent->clockRadius) * qSin(angle);
    qreal endX = cdParent->clockCenter.rx() + (cdParent->clockRadius - lineLength) * qCos(angle);
    qreal endY = cdParent->clockCenter.ry() + (cdParent->clockRadius - lineLength) * qSin(angle);
    start = QPointF(startX, startY);
    end = QPointF(endX, endY);
}

void ClockDial::draw(QPainter *painter)
{
    qreal lineLength = 0 , lineThickness = 0;
    QPointF start(0,0);
    QPointF end(0,0);

    if(hasMinuteMarks || hasFiveMinuteMarks)
    {
        for(int i=0; i<360; i+=6)
        {
            qreal angle = qDegreesToRadians((qreal)i);

            if(i%30 == false)
            {
                if(hasFiveMinuteMarks)
                {
                    lineLength = lineFiveMinuteLength;
                    lineThickness = lineFiveMinuteThickness;
                }
                else
                {
                    lineLength = lineMinuteLength;
                    lineThickness = lineMinuteThickness;
                }
                getMarksStartEnd(start, end, lineLength, angle);
                painter->setPen(QPen(Qt::gray, lineThickness));
                //painter->setBrush(QBrush(QColor(255,255,255,255), Qt::SolidPattern));
                hasPoints==true ? painter->drawEllipse(start, pointsFiveMinuteRadius, pointsFiveMinuteRadius) : painter->drawLine(start, end);
                painter->setBrush(Qt::NoBrush);
            }
            else
            {
                if(hasMinuteMarks)
                    {
                        lineLength = lineMinuteLength;
                        lineThickness = lineMinuteThickness;
                        getMarksStartEnd(start, end, lineLength, angle);
                        painter->setPen(QPen(Qt::white, lineThickness));
                        painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
                        hasPoints==true ? painter->drawEllipse(start, pointsMinuteRadius, pointsMinuteRadius) : painter->drawLine(start, end);
                        painter->setBrush(Qt::NoBrush);
                    }
            }
        }
    }

    if(hasCircle)
    {
        painter->setPen(QPen(Qt::gray, circleThickness));
        painter->drawEllipse(cdParent->clockCenter, cdParent->clockRadius, cdParent->clockRadius);
    }
}

