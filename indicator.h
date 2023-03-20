#ifndef INDICATOR_H
#define INDICATOR_H

#include <QWidget>
#include <QTimer>

class Indicator : public QWidget
{
    Q_OBJECT
public:
    explicit Indicator(QWidget *parent = nullptr);

    // QWidget interface
    QSize sizeHint() const override;

public slots:
    void activateNormal(); // Green
    void activateDangerous(); // Red
    void activateWarning(); // Yellow

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool redActive;
    bool greenActive;
    bool yellowActive;

    bool lightsOn;

    void toggleLights();

    QTimer* timer;
};

#endif // INDICATOR_H
