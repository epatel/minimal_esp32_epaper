#include <Arduino.h>

#include "display.h"

#include "buff.h"
#include "epd.h"


// Fake 2 colors by extending bitmap to double height
// Draw in lower half (+HEIGHT) for second color (red)
static U8G2_BITMAP _u8g2(WIDTH, HEIGHT * 2, U8G2_R0);

Display::Display()
{
}

void Display::init()
{
    EPD_initSPI();
    EPD_dispIndex = 14; // 4.2 inch b
    clear();
}

void Display::clear()
{
    _u8g2.begin();
}

void Display::sendBW()
{
    for (short y = 0; y < HEIGHT; y++)
    {
        for (short x = 0; x < WIDTH / 8; x++)
        {
            byte b = 0;
            for (char i = 0; i < 8; i++)
            {
                b |= u8x8_GetBitmapPixel(NULL, x * 8 + i, y) ? 0x80 >> i : 0;
            }
            EPD_SendData(~b);
        }
    }
}

void Display::sendRed()
{
    for (short y = 0; y < HEIGHT; y++)
    {
        for (short x = 0; x < WIDTH / 8; x++)
        {
            byte b = 0;
            for (char i = 0; i < 8; i++)
            {
                b |= u8x8_GetBitmapPixel(NULL, x * 8 + i, HEIGHT + y) ? 0x80 >> i : 0;
            }
            EPD_SendData(~b);
        }
    }
}

void Display::show()
{
    u8g2_SendBuffer(_u8g2.getU8g2());

    EPD_dispInit();
    delay(2);

    // Send bw data
    sendBW();
    delay(2);

    int code = EPD_dispMass[EPD_dispIndex].next;

    if (code != -1)
    {
        // Do the selection of the next data channel
        EPD_SendCommand(code);
        delay(2);

        // Send red data
        sendRed();
        delay(2);
    }

    // Done, sleep display
    EPD_dispMass[EPD_dispIndex].show();
}

U8G2 &Display::u8g2()
{
    return _u8g2;
}
