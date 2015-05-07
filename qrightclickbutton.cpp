#include "qrightclickbutton.h"

QRightClickButton::QRightClickButton(QWidget *parent) :
    QPushButton(parent)
{
}

void QRightClickButton::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);

    if(e->button() == Qt::LeftButton) {
        emit pressed();
    }
    if(e->button() == Qt::RightButton) {
        emit rightClicked();
    }
}

void QRightClickButton::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);

    if(e->button() == Qt::LeftButton) {
        emit released();
    }
}

