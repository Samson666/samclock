#include <QApplication>
#include <QSettings>
#include "widget.h"

//TODO: switch between UTC and local time
//TODO: use different clock hand styles
//TODO: use different colors (for different elements)

int main(int argc, char *argv[])
{
    QSettings settings("JJSoft","SamClock");
    QApplication a(argc, argv);
    Widget w;
    //Get Conf
    w.move(settings.value("pos", QPoint(100,100)).value<QPoint>());
    w.setFixedSize(settings.value("size", QSize(400,400)).value<QSize>());
    w.hasSecHand = settings.value("hasSecHand", true).toBool();
    w.dial.hasCircle = settings.value("hasCircle", true).toBool();
    w.dial.hasFiveMinuteMarks = settings.value("hasFiveMinuteMarks",true).toBool();
    w.dial.hasMinuteMarks = settings.value("hasMinuteMarks", true).toBool();
    w.dial.hasPoints = settings.value("hasPoints", false).toBool();
    w.hasSweepingSecondHand = settings.value("hasSweepingSecondHand", false).toBool();
    w.hasRoundedHandEdges = settings.value("hasRoundedHandEdges", false).toBool();
    w.show();
    return a.exec();
}
