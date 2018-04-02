#include "Arduino.h"
#include "U8x8MenuItem.h"

U8x8MenuItem::U8x8MenuItem(int cols) {
    _cols = cols;
}

void U8x8MenuItem::setLabel (char * label) {
    _label = label;
};

void U8x8MenuItem::setDisplayValue (char * value) {
    _value = value;
};

char * buf = (char *) malloc(17);
char * U8x8MenuItem::sprintItem () {
    // char buf[17];
    char * spaces = whiteSpaces(_cols - strlen(_label) - strlen(_value) - 1); // Remove one char for the cursor
    sprintf(buf, "%s%s%s", _label, spaces, _value);
    return buf;
}

void U8x8MenuItem::assingAction (void (* cb)()) {
    _cb = cb;
};

void U8x8MenuItem::fire () {
    _cb();
};

char * str = (char *) malloc(17);
static char * U8x8MenuItem::whiteSpaces(int count) {
    //char str[17];
    strcpy(str, "");
    for (int i = 0; i < count; i++) {
        strcat(str, " ");
    };
    return str;
}
