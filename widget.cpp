#include "widget.h"
#include "ui_widget.h"
#include "indicator.h"
#include "watertank.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    Indicator* indicator = new Indicator(this);

    WaterTank* tank = new WaterTank(this);

    connect(tank, &WaterTank::normal, indicator, &Indicator::activateNormal);
    connect(tank, &WaterTank::warning, indicator, &Indicator::activateWarning);
    connect(tank, &WaterTank::danger, indicator, &Indicator::activateDangerous);

    ui->horizontalLayout->addWidget(tank);
    ui->horizontalLayout->addWidget(indicator);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *event)
{
    qDebug() << "h: " << height() << ", w: " << width();
    QWidget::resizeEvent(event);
}

