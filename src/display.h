#include <U8g2lib.h>

#define WIDTH 400
#define HEIGHT 300

#define BW(_x, _y) (_x), (_y)
#define RED(_x, _y) (_x), ((_y)+HEIGHT)

enum Color {
  white,
  black,
  red
};

class Display {
protected:
    void sendBW();
    void sendRed();

public:
    Display();

    void init();

    void clear();
    void show();

    U8G2 &u8g2();
};
