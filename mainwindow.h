#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

#include <QTcpServer>
#include <QTcpSocket>
#define LCDVIEW_CMD_UDP_PORT		(5001)
#define LCDVIEW_CMD_BITMASK_PRINT	(0x80)
#define LCDVIEW_CMD_BITMASK_ROW		(0x40)
#define LCDVIEW_CMD_BITMASK_COL		(0x3F)

#include "qrightclickbutton.h"
#include "lcdcontrol.h"

namespace Ui {
class MainWindow;
}

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
#include "presskey.h"
extern int presskey( int key_type, int evt_type );
#ifdef __cplusplus
}
#endif /* __cplusplus */

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

	void setCharCode(int col, int row, unsigned char code);
private:
	bool initTcpSocket( void );	// TCPソケット初期化
	QTcpServer	*m_TcpServer;	// TCPサーバー
	QTcpSocket	*m_TcpSocket;	// TCPソケットディスクリプタ

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
	
	//unsigned char m_CharCode[ROW_MAX][COL_MAX];

protected:
    void paintEvent(QPaintEvent *);

public slots:
	void acceptConnection( void );	// TCP接続時の処理
	void recievedLcdCmd( void );	// 受信データのコマンド解析処理

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

//    void changeBlink();
//    void changeSample();
};

#endif // MAINWINDOW_H
