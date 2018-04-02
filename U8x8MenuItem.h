#ifndef U8x8MenuItem_h
#define U8x8MenuItem_h

class U8x8MenuItem {
public:
    U8x8MenuItem(int cols);
    void setLabel(char * label);
    void setDisplayValue(char * value);
    void assingAction(void (* cb)(int index));
    void fire(int index);
    char * sprintItem();
    static char * whiteSpaces(int count);
private:
    char * _label;
    char * _value;
    int _cols;
    void (* _cb)(int index);
};

#endif
