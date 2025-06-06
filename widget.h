#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qpainter.h>
#include <qpen.h>
#include <QtEvents>
#include "clockhand.h"
#include "clockdial.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    friend class Dialog;
    friend class ClockHand;
    friend class ClockDial;

    qreal clockRadius;
    qreal clockMargin;
    bool hasSecHand = true;
    bool hasDial = true;
    qreal wWidth;
    ClockDial dial;
private slots:
    void ShowContextMenu(const QPoint& pos);

protected:
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
            m_dragging = true;
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (m_dragging && (event->buttons() & Qt::LeftButton)) {
            move(event->globalPosition().toPoint() - m_dragPosition);
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        Q_UNUSED(event);
        m_dragging = false;
    }

private:
    Ui::Widget *ui;
    QPen *pen;
    ClockHand secHand;
    ClockHand minHand;
    ClockHand hrHand;

    bool m_dragging = false;
    QPoint m_dragPosition;


    void drawDial(QPainter *painter);
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    QPointF clockCenter;
};
#endif // WIDGET_H
