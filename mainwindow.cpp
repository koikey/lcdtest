#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(600, 200);
    this->setStatusBar(NULL);

    lcdCtrl = new LcdControl;

    /* 各ボタン生成 */
    btnUp = new QRightClickButton(this);
    btnUp->setGeometry( 75,  20, 50, 40);
    btnUp->setText("U");
    btnDown = new QRightClickButton(this);
    btnDown->setGeometry( 75, 100, 50, 40);
    btnDown->setText("D");
    btnLeft = new QRightClickButton(this);
    btnLeft->setGeometry( 20,  60, 50, 40);
    btnLeft->setText("L");
    btnRight = new QRightClickButton(this);
    btnRight->setGeometry(130,  60, 50, 40);
    btnRight->setText("R");

    btnBack = new QRightClickButton(this);
    btnBack->setGeometry( 20, 120, 50, 40);
    btnBack->setText("BACK");
    btnEnter = new QRightClickButton(this);
    btnEnter->setGeometry(130, 120, 50, 40);
    btnEnter->setText("ENT");

    /* ラベル生成 */
    label = new QLabel(this);
    label->setText("R button -> toggle mode on/off");
    label->setGeometry(18, 170, 260, 18);

    labelUp = new QLabel(this);
    labelUp->setText("");
    labelUp->setGeometry(200, 120, 60, 18);
    labelDown = new QLabel(this);
    labelDown->setText("");
    labelDown->setGeometry(260, 120, 60, 18);
    labelLeft = new QLabel(this);
    labelLeft->setText("");
    labelLeft->setGeometry(320, 120, 60, 18);
    labelRight = new QLabel(this);
    labelRight->setText("");
    labelRight->setGeometry(380, 120, 60, 18);
    labelBack = new QLabel(this);
    labelBack->setText("");
    labelBack->setGeometry(200, 140, 60, 18);
    labelEnter = new QLabel(this);
    labelEnter->setText("");
    labelEnter->setGeometry(260, 140, 60, 18);

    /* タイマ生成 */
    timer = new QTimer(this);
    timerSample = new QTimer(this);

    stateBtnUp_Pushed     = false;
    stateBtnUp_Toggled    = false;
    stateBtnDown_Pushed   = false;
    stateBtnDown_Toggled  = false;
    stateBtnLeft_Pushed   = false;
    stateBtnLeft_Toggled  = false;
    stateBtnRight_Pushed  = false;
    stateBtnRight_Toggled = false;
    stateBtnBack_Pushed   = false;
    stateBtnBack_Toggled  = false;
    stateBtnEnter_Pushed  = false;
    stateBtnEnter_Toggled = false;

    /* シグナル/スロット登録 */
    connect(btnUp,    SIGNAL(pressed()),      this, SLOT(pressedBtnUp()));
    connect(btnUp,    SIGNAL(released()),     this, SLOT(releasedBtnUp()));
    connect(btnUp,    SIGNAL(rightClicked()), this, SLOT(rightClickedBtnUp()));
    connect(btnDown,  SIGNAL(pressed()),      this, SLOT(pressedBtnDown()));
    connect(btnDown,  SIGNAL(released()),     this, SLOT(releasedBtnDown()));
    connect(btnDown,  SIGNAL(rightClicked()), this, SLOT(rightClickedBtnDown()));
    connect(btnLeft,  SIGNAL(pressed()),      this, SLOT(pressedBtnLeft()));
    connect(btnLeft,  SIGNAL(released()),     this, SLOT(releasedBtnLeft()));
    connect(btnLeft,  SIGNAL(rightClicked()), this, SLOT(rightClickedBtnLeft()));
    connect(btnRight, SIGNAL(pressed()),      this, SLOT(pressedBtnRight()));
    connect(btnRight, SIGNAL(released()),     this, SLOT(releasedBtnRight()));
    connect(btnRight, SIGNAL(rightClicked()), this, SLOT(rightClickedBtnRight()));
    connect(btnBack,  SIGNAL(pressed()),      this, SLOT(pressedBtnBack()));
    connect(btnBack,  SIGNAL(released()),     this, SLOT(releasedBtnBack()));
    connect(btnBack,  SIGNAL(rightClicked()), this, SLOT(rightClickedBtnBack()));
    connect(btnEnter, SIGNAL(pressed()),      this, SLOT(pressedBtnEnter()));
    connect(btnEnter, SIGNAL(released()),     this, SLOT(releasedBtnEnter()));
    connect(btnEnter, SIGNAL(rightClicked()), this, SLOT(rightClickedBtnEnter()));

    connect(timer,       SIGNAL(timeout()),   this, SLOT(changeBlink()));
    connect(timerSample, SIGNAL(timeout()),   this, SLOT(changeSample()));

    /* Blinkタイマ起動 */
    timer->start(500);

    /* サンプル用タイマ起動 */
    timerSample->start(500);
}

MainWindow::~MainWindow()
{
    delete timerSample;
    delete timer;

    delete label;
    delete labelUp;
    delete labelDown;
    delete labelLeft;
    delete labelRight;
    delete labelBack;
    delete labelEnter;

    delete btnUp;
    delete btnDown;
    delete btnLeft;
    delete btnRight;
    delete btnBack;
    delete btnEnter;

    delete lcdCtrl;

    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    /* 背景描画 */
    painter.setPen(QPen(QColor(210, 210, 216), 1, Qt::SolidLine));
    painter.setBrush(QBrush(QColor(210, 210, 216), Qt::SolidPattern));
    painter.drawRect(LCD_BASE_X, LCD_BASE_Y, CHR_WIDTH * COL_MAX+4, CHR_HEIGHT * ROW_MAX+4);

    /* 目盛り描画 */
    const int line_len[] = {
       4, 1, 1, 1, 1, 3, 1, 1, 1, 1, 4, 1, 1, 1, 1, 3, 1, 1, 1, 1, 4
    };
    painter.setPen(QPen(QColor(160, 160, 160), 1, Qt::SolidLine));
    painter.setBrush(QBrush(QColor(160, 160, 160), Qt::SolidPattern));
    for(int i = 0; i < 20+1; i++) {
        painter.drawRect((i * CHR_WIDTH) + LCD_BASE_X, LCD_BASE_Y - line_len[i]-2,
                         1, line_len[i]);
    }

    /* 文字描画 */
    painter.setPen(QPen(QColor(136, 136, 152), 1, Qt::SolidLine));
    painter.setBrush(QBrush(QColor(136, 136, 152), Qt::SolidPattern));
    lcdCtrl->drawLcd(painter);
}

/* 上ボタン押下処理 */
void MainWindow::pressedBtnUp()
{
    if(stateBtnUp_Toggled == false) {
        btnUp->setText("[U]");
        labelUp->setText("  UP");
        stateBtnUp_Pushed = true;
    }
}
void MainWindow::releasedBtnUp()
{
    if(stateBtnUp_Toggled == false) {
        stateBtnUp_Pushed = false;
    } else {
        stateBtnUp_Pushed = !stateBtnUp_Pushed;
    }

    if(isPushedBtnUp()) {
        btnUp->setText("[U]");
        labelUp->setText("  UP");
    } else {
        btnUp->setText("U");
        labelUp->setText("");
    }
}
void MainWindow::rightClickedBtnUp()
{
    stateBtnUp_Toggled = !stateBtnUp_Toggled;
    btnUp->setCheckable(stateBtnUp_Toggled);
}

/* 下ボタン押下処理 */
void MainWindow::pressedBtnDown()
{
    if(stateBtnDown_Toggled == false) {
        btnDown->setText("[D]");
        labelDown->setText("DOWN");
        stateBtnDown_Pushed = true;
    }
}
void MainWindow::releasedBtnDown()
{
    if(stateBtnDown_Toggled == false) {
        stateBtnDown_Pushed = false;
    } else {
        stateBtnDown_Pushed = !stateBtnDown_Pushed;
    }

    if(isPushedBtnDown()) {
        btnDown->setText("[D]");
        labelDown->setText("DOWN");
    } else {
        btnDown->setText("D");
        labelDown->setText("");
    }
}
void MainWindow::rightClickedBtnDown()
{
    stateBtnDown_Toggled = !stateBtnDown_Toggled;
    btnDown->setCheckable(stateBtnDown_Toggled);
}

/* 左ボタン押下処理 */
void MainWindow::pressedBtnLeft()
{
    if(stateBtnLeft_Toggled == false) {
        btnLeft->setText("[L]");
        labelLeft->setText(" LEFT");
        stateBtnLeft_Pushed = true;
    }
}
void MainWindow::releasedBtnLeft()
{
    if(stateBtnLeft_Toggled == false) {
        stateBtnLeft_Pushed = false;
    } else {
        stateBtnLeft_Pushed = !stateBtnLeft_Pushed;
    }

    if(isPushedBtnLeft()) {
        btnLeft->setText("[L]");
        labelLeft->setText(" LEFT");
    } else {
        btnLeft->setText("L");
        labelLeft->setText("");
    }
}
void MainWindow::rightClickedBtnLeft()
{
    stateBtnLeft_Toggled = !stateBtnLeft_Toggled;
    btnLeft->setCheckable(stateBtnLeft_Toggled);
}

/* 右ボタン押下処理 */
void MainWindow::pressedBtnRight()
{
    if(stateBtnRight_Toggled == false) {
        btnRight->setText("[R]");
        labelRight->setText("RIGHT");
        stateBtnRight_Pushed = true;
    }
}
void MainWindow::releasedBtnRight()
{
    if(stateBtnRight_Toggled == false) {
        stateBtnRight_Pushed = false;
    } else {
        stateBtnRight_Pushed = !stateBtnRight_Pushed;
    }

    if(isPushedBtnRight()) {
        btnRight->setText("[R]");
        labelRight->setText("RIGHT");
    } else {
        btnRight->setText("R");
        labelRight->setText("");
    }
}
void MainWindow::rightClickedBtnRight()
{
    stateBtnRight_Toggled = !stateBtnRight_Toggled;
    btnRight->setCheckable(stateBtnRight_Toggled);
}

/* BACKボタン押下処理 */
void MainWindow::pressedBtnBack()
{
    if(stateBtnBack_Toggled == false) {
        btnBack->setText("[B]");
        labelBack->setText(" BACK");
        stateBtnBack_Pushed = true;
    }
}
void MainWindow::releasedBtnBack()
{
    if(stateBtnBack_Toggled == false) {
        stateBtnBack_Pushed = false;
    } else {
        stateBtnBack_Pushed = !stateBtnBack_Pushed;
    }

    if(isPushedBtnBack()) {
        btnBack->setText("[B]");
        labelBack->setText(" BACK");
    } else {
        btnBack->setText("BACK");
        labelBack->setText("");
    }
}
void MainWindow::rightClickedBtnBack()
{
    stateBtnBack_Toggled = !stateBtnBack_Toggled;
    btnBack->setCheckable(stateBtnBack_Toggled);
}

/* ENTERボタン押下処理 */
void MainWindow::pressedBtnEnter()
{
    if(stateBtnEnter_Toggled == false) {
        btnEnter->setText("[E]");
        labelEnter->setText("ENTER");
        stateBtnEnter_Pushed = true;
    }
}
void MainWindow::releasedBtnEnter()
{
    if(stateBtnEnter_Toggled == false) {
        stateBtnEnter_Pushed = false;
    } else {
        stateBtnEnter_Pushed = !stateBtnEnter_Pushed;
    }

    if(isPushedBtnEnter()) {
        btnEnter->setText("[E]");
        labelEnter->setText("ENTER");
    } else {
        btnEnter->setText("ENT");
        labelEnter->setText("");
    }
}
void MainWindow::rightClickedBtnEnter()
{
    stateBtnEnter_Toggled = !stateBtnEnter_Toggled;
    btnEnter->setCheckable(stateBtnEnter_Toggled);
}

/* 点滅表示処理 */
void MainWindow::changeBlink()
{
    lcdCtrl->changeStateBlink();
    this->update();              /* ウィンドウ再描画 */
}

/* 表示サンプル(5秒毎に表示切替) */
void MainWindow::changeSample()
{
    static int state = 0;
    const unsigned char *pattern = NULL;
    const unsigned char pattern0[ROW_MAX * COL_MAX] = {
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
        0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x00, 0x00, 0x00, 0x00,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
        0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x00, 0x00, 0x00, 0x00
    };
    const unsigned char pattern1[ROW_MAX * COL_MAX] = {
        0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
        0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53,
        0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D,
        0x5E, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    const unsigned char pattern2[ROW_MAX * COL_MAX] = {
        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
        0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73,
        0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D,
        0x7E, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    const unsigned char pattern3[ROW_MAX * COL_MAX] = {
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9,
        0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3,
        0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD,
        0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7
    };
    const unsigned char pattern4[ROW_MAX * COL_MAX] = {
        0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1,
        0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xDB, 0xD9, 0xDA, 0xDB,
        0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5,
        0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEF, 0xF0
    };
    const unsigned char pattern5[ROW_MAX * COL_MAX] = {
        0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA,
        0xFB, 0xFC, 0xFD, 0xFE, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    timerSample->stop();

    /* 表示文字入れ替え */
    switch(state) {
    case 0:         /* 記号/数字 */
        pattern = pattern0;
        break;
    case 1:         /* アルファベット */
        pattern = pattern1;
        break;
    case 2:         /* アルファベット */
        pattern = pattern2;
        break;
    case 3:         /* カナ */
        pattern = pattern3;
        break;
    case 4:         /* カナ */
        pattern = pattern4;
        break;
    case 5:         /* カナ */
        pattern = pattern5;
        break;
    default:
        state = 0;
        break;
    }

    if(pattern != NULL) {
        for(int y = 0; y < ROW_MAX; y++){
            for(int x = 0; x < COL_MAX; x++){
                lcdCtrl->setCharacter( x, y, *(pattern + (y*20) + x) );
            }
        }
    }

    lcdCtrl->setAttribute(  1, 0, ATR_BLK );
    lcdCtrl->setAttribute(  2, 0, ATR_BLK );
    lcdCtrl->setAttribute(  3, 0, ATR_BLK );
    lcdCtrl->setAttribute( 11, 0, ATR_CUR );

    state++;
    if(state > 5) {
        state = 0;
    }

    timerSample->start(5000);
}
