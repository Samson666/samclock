#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class Widget;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_clockRadiusSlider_valueChanged(int value);
    void on_checkHasSecHand_checkStateChanged(const Qt::CheckState &arg1);
    void on_checkHasDialCircle_checkStateChanged(const Qt::CheckState &arg1);
    void on_checkHasMinuteMarks_checkStateChanged(const Qt::CheckState &arg1);
    void on_checkHasFiveMinuteMarks_checkStateChanged(const Qt::CheckState &arg1);
    void on_checkHasPoints_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::Dialog *ui;
    Widget *cParent;
};

#endif // DIALOG_H
