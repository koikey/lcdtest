#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

#include "qrightclickbutton.h"
#include "lcdcontrol.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool isPushedBtnUp()    { return stateBtnUp_Pushed; }
    bool isPushedBtnDown()  { return stateBtnDown_Pushed; }
    bool isPushedBtnLeft()  { return stateBtnLeft_Pushed; }
    bool isPushedBtnRight() { return stateBtnRight_Pushed; }
    bool isPushedBtnBack()  { return stateBtnBack_Pushed; }
    bool isPushedBtnEnter() { return stateBtnEnter_Pushed; }

private:
    Ui::MainWindow *ui;
    QRightClickButton *btnUp;
    QRightClickButton *btnDown;
    QRightClickButton *btnLeft;
    QRightClickButton *btnRight;
    QRightClickButton *btnBack;
    QRightClickButton *btnEnter;
    QLabel  *label;
    QLabel  *labelUp;
    QLabel  *labelDown;
    QLabel  *labelLeft;
    QLabel  *labelRight;
    QLabel  *labelBack;
    QLabel  *labelEnter;
    QTimer  *timer;
    QTimer  *timerSample;

    LcdControl* lcdCtrl;

    bool stateBtnUp_Pushed;
    bool stateBtnUp_Toggled;
    bool stateBtnDown_Pushed;
    bool stateBtnDown_Toggled;
    bool stateBtnLeft_Pushed;
    bool stateBtnLeft_Toggled;
    bool stateBtnRight_Pushed;
    bool stateBtnRight_Toggled;
    bool stateBtnBack_Pushed;
    bool stateBtnBack_Toggled;
    bool stateBtnEnter_Pushed;
    bool stateBtnEnter_Toggled;

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void pressedBtnUp();
    void releasedBtnUp();
    void rightClickedBtnUp();
    void pressedBtnDown();
    void releasedBtnDown();
    void rightClickedBtnDown();
    void pressedBtnLeft();
    void releasedBtnLeft();
    void rightClickedBtnLeft();
    void pressedBtnRight();
    void releasedBtnRight();
    void rightClickedBtnRight();

    void pressedBtnBack();
    void releasedBtnBack();
    void rightClickedBtnBack();
    void pressedBtnEnter();
    void releasedBtnEnter();
    void rightClickedBtnEnter();

    void changeBlink();
    void changeSample();
};

#endif // MAINWINDOW_H
