#include "Arduino.h"
#include "U8x8Menu.h"

U8x8Menu::U8x8Menu(U8X8_SSD1306_128X64_NONAME_HW_I2C *lcd, int lcd_rows, int lcd_cols, char * heading = "") {
    _lcd = lcd;
    _cols = lcd_cols;
    if (strlen(heading) > 0) {
        _hasHeading = 1;
        _rows -= 1;
    }
    _rows = lcd_rows - _hasHeading;
    _heading = heading;
};

void U8x8Menu::addItem( char * label, char * value, void (* cb)(int index) ) {
    U8x8MenuItem item(_cols);
    item.setLabel(label);
    item.setDisplayValue(value);
    item.assingAction(cb);
    menuItems.push_back(item);
};

void U8x8Menu::show() {
    delay(100);
    _lcd->clear();
    _render();
}

void U8x8Menu::_render() {
    int limit = _rows;
    int items = menuItems.size();
    if (_rows > items) {
        limit = items;
    }
    if (_hasHeading == 1) {
        _lcd->setCursor(0, 0);
        char * result = center(_heading);
        _lcd->setInverseFont(1);
        _lcd->drawString(0, 0, center(_heading));
        _lcd->setInverseFont(0);
    }

    for (int i = _hasHeading; i < _rows + _hasHeading; i++) {
        if (i != _pointerPosition + _hasHeading) {
            _lcd->setCursor(0, i);
            _lcd->print(" ");
        }
    }

    if (_pointerPosition > limit) {
        _pointerPosition = limit;
    }
    _lcd->setCursor(0, _pointerPosition + _hasHeading);
    _lcd->print(">");
    for (int i = _hasHeading; i < limit + _hasHeading; i++ ) {
        _lcd->setCursor(1, i);
	_lcd->print(menuItems[i + _menuItemOnTop - _hasHeading].sprintItem());
    }
}

void U8x8Menu::next() {
    _pointerPosition += 1;
    int size = menuItems.size();

    int limit = _rows - 1;
    if (_rows >= size) {
        limit = size - 1;
        if (_pointerPosition > limit) {
            _pointerPosition = limit;
        }
    } else {
        if (_pointerPosition > limit) {
            _pointerPosition = limit;
            _menuItemOnTop++;
            if (_menuItemOnTop > size - _rows) {
                _menuItemOnTop = size - _rows;
            }
        }
    }
    _selectedMenuItem = _pointerPosition + _menuItemOnTop;
    _render();
}

void U8x8Menu::prev() {
    _pointerPosition -= 1;
    if (_pointerPosition < 0) {
        _pointerPosition = 0;
        _menuItemOnTop--;
        if (_menuItemOnTop < 0) {
            _menuItemOnTop = 0;
        }
    }
    _selectedMenuItem = _pointerPosition + _menuItemOnTop; // compensate for pointer shifting
    _render();
}

void U8x8Menu::fire () {
    menuItems[_selectedMenuItem].fire(_selectedMenuItem);
}

void U8x8Menu::reset (int item = 0) {
    _menuItemOnTop = 0;
    _pointerPosition = 0;
    _selectedMenuItem = 0;
    for (int i = 0; i < item; i++) {
        next();
    }
}

void U8x8Menu::updateDisplayValue(char * value) {
    menuItems[_selectedMenuItem].setDisplayValue(value);
}

char * buffer = (char *) malloc(16);
const char * U8x8Menu::center(char * text) {
    // char buffer[17];
    int leading_spaces_count = (_cols - strlen(text)) / 2;
    char * leading_spaces = U8x8MenuItem::whiteSpaces(leading_spaces_count);
    char * trailing_spaces = U8x8MenuItem::whiteSpaces(_cols - strlen(text) - leading_spaces_count);
    sprintf(buffer, "%s%s%s", leading_spaces, text, trailing_spaces);
    return buffer;
}
