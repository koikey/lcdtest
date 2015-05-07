#ifndef QRIGHTCLICKBUTTON_H
#define QRIGHTCLICKBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class QRightClickButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QRightClickButton(QWidget *parent = 0);

private slots:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void pressed();
    void released();
    void rightClicked();

public slots:

};

#endif // QRIGHTCLICKBUTTON_H
