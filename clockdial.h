#ifndef CLOCKDIAL_H
#define CLOCKDIAL_H
#include <QPainter>

class Widget;

class ClockDial
{
public:
    ClockDial(Widget *parent = nullptr);
    void draw(QPainter *painter);

    bool hasMinuteMarks = true;
    bool hasFiveMinuteMarks = true;
    bool hasCircle = true;
    bool hasNumbers = true;
    bool hasPoints = false;
    qreal lineMinuteLength = 10;
    qreal lineFiveMinuteLength = 20;
    qreal lineMinuteThickness = 0.5;
    qreal lineFiveMinuteThickness = 2;
    qreal circleThickness = 1;
    qreal pointsMinuteRadius = 3;
    qreal pointsFiveMinuteRadius = 5;

private:
    Widget *cdParent;
    void getMarksStartEnd(QPointF &start, QPointF &end, qreal lineLength, qreal angle);
};

#endif // CLOCKDIAL_H
