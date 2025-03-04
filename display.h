//
// Created by pi on 2/14/25.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include <unistd.h>
#include "gpioPins.h"
#include "bitmapDisplay.h"



// GPIO pinnen defini�ren
#define RS  32
#define EN  33
#define CS1 18
#define CS2 5
#define RST 25

// Datapinnen D0-D7 is done via the io-expander

void sendData(uint8_t data);
void sendCommand(uint8_t cmd);
void initDisplay();
void clearScreen();
void setCursor(uint8_t row, uint8_t offset);
void drawText(const char* text, uint8_t row, uint8_t offset);
void drawEmoji(const char* text, uint8_t row, uint8_t offset);


#endif //DISPLAY_H
