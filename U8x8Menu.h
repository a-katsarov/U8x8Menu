#ifndef U8x8Menu_h
#define U8x8Menu_h

#include <StandardCplusplus.h>
#include <vector>
#include <U8x8lib.h>
#include "U8x8MenuItem.h"

class U8x8Menu {
public:
    U8x8Menu(U8X8_SSD1306_128X64_NONAME_HW_I2C *lcd, int lcd_rows, int lcd_cols, char * heading = "");
    void addItem(char * label, char * value, void (* cb)());
    void show();
    void next();
    void prev();
    void fire();
    void reset(int item = 0);
    void updateDisplayValue(char * value);
    std::vector<U8x8MenuItem> menuItems;
private:
    U8X8_SSD1306_128X64_NONAME_HW_I2C *_lcd;
    int _rows;
    int _cols;
    int _pointerPosition = 0;
    int _menuItemOnTop = 0;
    int _selectedMenuItem = 0;
    char * _heading;
    int _hasHeading = 0;
    void _render();
    const char * center(char * text);

};

#endif
