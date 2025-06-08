#include "dialog.h"
#include "ui_dialog.h"
#include "widget.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->clockRadiusSlider->update();
    cParent = (Widget*)parent;
    ui->clockRadiusSlider->setValue(cParent->wWidth);
    ui->checkHasSecHand->setCheckState(cParent->hasSecHand ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    ui->checkHasDialCircle->setCheckState(cParent->dial.hasCircle ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    ui->checkHasMinuteMarks->setCheckState(cParent->dial.hasMinuteMarks ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    ui->checkHasFiveMinuteMarks->setCheckState(cParent->dial.hasFiveMinuteMarks ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    ui->checkHasPoints->setCheckState(cParent->dial.hasPoints ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    ui->checkHasSweepingSecondHand->setCheckState(cParent->hasSweepingSecondHand ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_clockRadiusSlider_valueChanged(int value)
{
    cParent->setFixedSize(value, value);
    cParent->update();
}

void Dialog::on_checkHasSecHand_checkStateChanged(const Qt::CheckState &arg1)
{
    cParent->hasSecHand = arg1 == Qt::CheckState::Checked ? true : false;
    cParent->update();
}

void Dialog::on_checkHasDialCircle_checkStateChanged(const Qt::CheckState &arg1)
{
    cParent->dial.hasCircle = arg1 == Qt::CheckState::Checked ? true : false;
    cParent->update();
}



void Dialog::on_checkHasMinuteMarks_checkStateChanged(const Qt::CheckState &arg1)
{
    cParent->dial.hasMinuteMarks = arg1 == Qt::CheckState::Checked ? true : false;
    cParent->update();
}


void Dialog::on_checkHasFiveMinuteMarks_checkStateChanged(const Qt::CheckState &arg1)
{
    cParent->dial.hasFiveMinuteMarks = arg1 == Qt::CheckState::Checked ? true : false;
    cParent->update();
}


void Dialog::on_checkHasPoints_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1 == Qt::CheckState::Checked)
    {
        cParent->dial.hasPoints = true;
        ui->checkHasFiveMinuteMarks->setDisabled(true);
        ui->checkHasMinuteMarks->setDisabled(true);
    }
    else
    {
        cParent->dial.hasPoints = false;
        ui->checkHasFiveMinuteMarks->setEnabled(true);
        ui->checkHasMinuteMarks->setEnabled(true);
    }
    cParent->update();
}


void Dialog::on_checkHasSweepingSecondHand_checkStateChanged(const Qt::CheckState &arg1)
{
    cParent->hasSweepingSecondHand = arg1 == Qt::CheckState::Checked ? true : false;
    cParent->update();
}

