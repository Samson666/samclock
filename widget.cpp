#include "./ui_widget.h"
#include <QTime>
#include <QDebug>
#include <QtMath>
#include <QSizePolicy>
#include <QSettings>
#include <QMenu>
#include "widget.h"
#include "clockhand.h"
#include "dialog.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("SamClock");
    setFixedSize(this->size());
    setAttribute(Qt::WA_TranslucentBackground);
    hasSecHand = true;
    secHand = ClockHand(this, ClockHand::sec);
    minHand = ClockHand(this, ClockHand::min);
    hrHand = ClockHand(this, ClockHand::hr);
    dial = ClockDial(this);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));

    //Remove window Frame
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    using namespace std::chrono_literals;
    startTimer(50ms);
}

void Widget::ShowContextMenu(const QPoint& pos)
{
    QPoint globalPos = mapToGlobal(pos);

    QMenu conMenu;
    conMenu.addAction("Preferrences");
    conMenu.addAction("Close");
    QAction* selectedItem = conMenu.exec(globalPos);
    if(selectedItem)
    {
        if(selectedItem->text() == "Close")
        {
            close();
        }
        else if(selectedItem->text() == "Preferrences")
        {
            Dialog *conf = new Dialog(this);
            conf->show();
        }
    }
}
void Widget::timerEvent(QTimerEvent *event)
{
    update();
}

void Widget::closeEvent(QCloseEvent *event)
{
    //Write conf before closing window
    QSettings settings("JJSoft","SamClock");
    settings.setValue("size", size());
    settings.setValue("hasSecHand", hasSecHand);
    settings.setValue("hasCircle", dial.hasCircle);
    settings.setValue("hasFiveMinuteMarks", dial.hasFiveMinuteMarks);
    settings.setValue("hasMinuteMarks", dial.hasMinuteMarks);
    settings.setValue("hasPoints", dial.hasPoints);
    settings.setValue("hasSweepingSecondHand", hasSweepingSecondHand);
    settings.setValue("hasRoundedHandEdges", hasRoundedHandEdges);
}

void Widget::drawDial(QPainter *painter)
{
    if(hasDial)
        painter->drawEllipse(clockCenter, clockRadius, clockRadius);
}

void Widget::paintEvent(QPaintEvent *event)
{
    wWidth = this->width();
    clockCenter = QPointF(wWidth/2, wWidth/2);

    clockMargin = 1;
    clockRadius = wWidth/2 - clockMargin;

    QPainter painter(this);
    QPen pen(Qt::white);
    pen.setWidth(3);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(pen);

    //Draw Dial
    if(hasDial)
        dial.draw(&painter);
    if(hasSecHand)
        secHand.draw(&painter);
    minHand.draw(&painter);
    hrHand.draw(&painter);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key pressed!";
    if(event->text()=="c")
    {
        qDebug() << "c pressed!";
        Dialog *conf = new Dialog(this);
        conf->show();
    }
    else
    QWidget::keyPressEvent(event);
}

Widget::~Widget()
{
    delete ui;
}
