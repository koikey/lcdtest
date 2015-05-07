#ifndef LCDCONTROL_H
#define LCDCONTROL_H

#include <QPainter>
#include <QMutex>

#define COL_MAX         (20)    /* 表示桁数 */
#define ROW_MAX         (2)     /* 表示行数 */

#define LCD_BASE_X      (200)
#define LCD_BASE_Y      (50)
#define LCD_CHR_WIDTH   (5)
#define LCD_CHR_HEIGHT  (8)
#define CHR_WIDTH       ((LCD_CHR_WIDTH + 1) * 3)
#define CHR_HEIGHT      ((LCD_CHR_HEIGHT + 1) * 3)

#define ATR_NOM         (0x00)  /* 通常表示 */
#define ATR_BLK         (0x01)  /* ブリンク表示 */
#define ATR_CUR         (0x02)  /* カーソル表示 */

struct lcdline {
    unsigned char   data[COL_MAX];
};

struct lcddata {
    lcdline         line[ROW_MAX];
};

class LcdControl
{
public:
    LcdControl();
    ~LcdControl();

    void setCharacter(int col, int row, const unsigned char code);
    void setAllCharacter(lcddata& lcddata);
    void setAttribute(int col, int row, const unsigned char attr);
    void setAllAttribute(lcddata& lcddata);

    void changeStateBlink();

    void drawLcd(QPainter& painter);
    void drawLcdCharacter(QPainter& painter,int code,int attr, int posx, int posy);

private:
    QMutex  mutex;

    lcddata lcdCharacterField;
    lcddata lcdAttributeField;
    bool stateBlink;
};

#endif // LCDCONTROL_H
