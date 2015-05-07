#include "lcdcontrol.h"

#include "chrpattern00.h"
#include "chrpattern01.h"
#include "chrpattern02.h"
#include "chrpattern03.h"
#include "chrpattern04.h"
#include "chrpattern05.h"
#include "chrpattern06.h"
#include "chrpattern07.h"
#include "chrpattern08.h"
#include "chrpattern09.h"
#include "chrpattern10.h"
#include "chrpattern11.h"
#include "chrpattern12.h"
#include "chrpattern13.h"
#include "chrpattern14.h"
#include "chrpattern15.h"

LcdControl::LcdControl()
{
    /* 表示領域クリア */
    mutex.lock();
    for(int row = 0; row < ROW_MAX; row++){
        for(int col = 0; col < COL_MAX; col++){
            lcdCharacterField.line[row].data[col] = 0x00;
            lcdAttributeField.line[row].data[col] = 0x00;
        }
    }
    mutex.unlock();

    stateBlink = false;
}

LcdControl::~LcdControl()
{
}

/* 文字コード設定(1データ) */
void LcdControl::setCharacter(int col, int row, const unsigned char code)
{
    mutex.lock();
    lcdCharacterField.line[row].data[col] = code;
    mutex.unlock();
}

/* 文字コード設定(全データ) */
void LcdControl::setAllCharacter(lcddata& lcddata)
{
    mutex.lock();
    for(int row = 0; row < ROW_MAX; row++){
        for(int col = 0; col < COL_MAX; col++){
            lcdCharacterField.line[row].data[col] = lcddata.line[row].data[col];
        }
    }
    mutex.unlock();
}

/* 属性設定(1データ) */
void LcdControl::setAttribute(int col, int row, const unsigned char attr)
{
    mutex.lock();
    lcdAttributeField.line[row].data[col] = attr;
    mutex.unlock();
}

/* 属性設定(全データ) */
void LcdControl::setAllAttribute(lcddata& lcddata)
{
    mutex.lock();
    for(int row = 0; row < ROW_MAX; row++){
        for(int col = 0; col < COL_MAX; col++){
            lcdAttributeField.line[row].data[col] = lcddata.line[row].data[col];
        }
    }
    mutex.unlock();
}

/* Blinkステータス切換 */
void LcdControl::changeStateBlink()
{
    stateBlink = !stateBlink;
}

/* 1画面描画 */
void LcdControl::drawLcd(QPainter& painter)
{
    mutex.lock();
    for(int y = 0; y < ROW_MAX; y++) {
        for(int x = 0; x < COL_MAX; x++) {
            drawLcdCharacter(painter,
                             lcdCharacterField.line[y].data[x],
                             lcdAttributeField.line[y].data[x],
                             x, y);
        }
    }
    mutex.unlock();
}

/* 1文字描画 */
void LcdControl::drawLcdCharacter(QPainter& painter,int code,int attr,int posx, int posy)
{
    const char *chrdata = NULL;
    int code_h = (code & 0xf0) >> 4;
    int code_l = (code & 0x0f);

    /* ブリンクON時は描画を行わない */
    if(attr == ATR_BLK && stateBlink == true) {
        return;
    }

    /* カーソル時描画 */
    if(attr == ATR_CUR && stateBlink == true) {
        chrdata = chrpattern15[0x0f];
    } else {
        /* 描画文字パターンテーブル取得 */
        switch(code_h)
        {
        case 0:
            chrdata = chrpattern00[code_l];
            break;
        case 1:
            chrdata = chrpattern01[code_l];
            break;
        case 2:
            chrdata = chrpattern02[code_l];
            break;
        case 3:
            chrdata = chrpattern03[code_l];
            break;
        case 4:
            chrdata = chrpattern04[code_l];
            break;
        case 5:
            chrdata = chrpattern05[code_l];
            break;
        case 6:
            chrdata = chrpattern06[code_l];
            break;
        case 7:
            chrdata = chrpattern07[code_l];
            break;
        case 8:
            chrdata = chrpattern08[code_l];
            break;
        case 9:
            chrdata = chrpattern09[code_l];
            break;
        case 10:
            chrdata = chrpattern10[code_l];
            break;
        case 11:
            chrdata = chrpattern11[code_l];
            break;
        case 12:
            chrdata = chrpattern12[code_l];
            break;
        case 13:
            chrdata = chrpattern13[code_l];
            break;
        case 14:
            chrdata = chrpattern14[code_l];
            break;
        case 15:
            chrdata = chrpattern15[code_l];
            break;
        default:
            return;
        }
    }

    /* 1文字分描画 */
    for(int row = 0; row < LCD_CHR_HEIGHT; row++){
        char data = chrdata[row];
        for(int col = 0; col < LCD_CHR_WIDTH; col++){
            if((data >> ((LCD_CHR_WIDTH-1)-col)) & 0x01){
                /* 1dot描画 */
                painter.drawRect(col*3 + posx * CHR_WIDTH  + LCD_BASE_X + 4,
                                 row*3 + posy * CHR_HEIGHT + LCD_BASE_Y + 6,
                                 2, 2);
            }
        }
    }
}
