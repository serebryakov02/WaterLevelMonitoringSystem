#include "watertank.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QWheelEvent>

WaterTank::WaterTank(QWidget *parent)
    : QWidget{parent},
      waterHeight(50),
      timer(new QTimer(this))
{
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));

    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, [=](){
        waterHeight += 15;
        update();

        // Emit signals
        if (waterHeight <= 210) {
            emit normal();
        }
        else if ((waterHeight >= 211) && (waterHeight <= 239)) {
            emit warning();
        }
        else {
            emit danger();
        }
    });
    timer->start();
}

QSize WaterTank::sizeHint() const
{
    return QSize(400, 400);
}

void WaterTank::paintEvent(QPaintEvent *event)
{
    // Set up painter
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);

    QPainter painter(this);
    painter.setPen(pen);

    // Draw the tank
    painter.drawLine(10, 10, 10, 300); // Left
    painter.drawLine(10, 300, 300, 300); // Bottom
    painter.drawLine(300, 300, 300, 10); // Right

    // Draw the water
    painter.setBrush(Qt::blue);
    painter.drawRect(10, 300 - waterHeight, 290, waterHeight);
}

void WaterTank::wheelEvent(QWheelEvent *event)
{
    // Get the rotation angle of the wheel in eighths of a degree.
    QPoint angle = event->angleDelta() / 8;
    // Checks if the vertical angle of the wheel event is negative.
    if ((angle.y() < 0) && (waterHeight > 10)) {
        waterHeight -= 10;
        update();
    }
}
