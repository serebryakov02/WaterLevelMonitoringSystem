#include "indicator.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

Indicator::Indicator(QWidget *parent)
    : QWidget(parent),
      redActive(false),
      greenActive(false),
      yellowActive(false),
      lightsOn(true)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));

    activateNormal();

    timer = new QTimer(this);
    timer->setInterval(300);
    connect(timer, &QTimer::timeout, [=](){
        toggleLights();
    });
    timer->start();
}

QSize Indicator::sizeHint() const
{
    return QSize(120, 350);
}

void Indicator::activateNormal()
{
    greenActive = true;
    redActive = yellowActive = false;
}

void Indicator::activateDangerous()
{
    redActive = true;
    greenActive = yellowActive = false;
}

void Indicator::activateWarning()
{
    yellowActive = true;
    greenActive = redActive = false;
}

void Indicator::paintEvent(QPaintEvent *event)
{
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(Qt::gray); // Fill color

    painter.drawRect(QRectF(0, 0, 120, 330));

    if (redActive) {
        // Draw the three lines
        painter.setBrush((lightsOn == true) ? Qt::red : Qt::black);
        painter.drawEllipse(10, 10, 100, 100);

        painter.setBrush(Qt::black);
        painter.drawEllipse(10, 115, 100, 100);

        painter.setBrush(Qt::black);
        painter.drawEllipse(10, 220, 100, 100);
    }
    else if (greenActive) {
        painter.setBrush(Qt::black);
        painter.drawEllipse(10, 10, 100, 100);

        painter.setBrush((lightsOn == true) ? Qt::green : Qt::black);
        painter.drawEllipse(10, 115, 100, 100);

        painter.setBrush(Qt::black);
        painter.drawEllipse(10, 220, 100, 100);
    }
    else if (yellowActive) {
        painter.setBrush(Qt::black);
        painter.drawEllipse(10, 10, 100, 100);

        painter.setBrush(Qt::black);
        painter.drawEllipse(10, 115, 100, 100);

        painter.setBrush((lightsOn == true) ? Qt::yellow : Qt::black);
        painter.drawEllipse(10, 220, 100, 100);
    }

}

void Indicator::toggleLights()
{
    if(!lightsOn) {
        lightsOn = true;
    }
    else {
        lightsOn = false;
    }
    update();
}
