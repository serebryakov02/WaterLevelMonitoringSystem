#ifndef WATERTANK_H
#define WATERTANK_H

#include <QWidget>
#include <QTimer>

class WaterTank : public QWidget
{
    Q_OBJECT
public:
    explicit WaterTank(QWidget *parent = nullptr);

    // QWidget interface
    QSize sizeHint() const override;

signals:
    void normal(); // Green
    void warning(); // Yellow
    void danger(); // Red

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    int waterHeight; // Comes from the sensor on the tank
    QTimer* timer;
};

#endif // WATERTANK_H
