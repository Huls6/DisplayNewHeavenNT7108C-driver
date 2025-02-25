//
// Created by pi on 2/14/25.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include <cstdint>
#include <unistd.h>
#include <vector>
#include <gpiod.h>
#include "gpio.h"
#include "bitmapDisplay.h"



// GPIO pinnen defini�ren
#define RS  22
#define EN  27
#define CS1 23
#define CS2 24
#define RST 25

// Datapinnen D0-D7
inline int DATA_PINS[8] = {5, 6, 13, 19, 26, 16, 20, 21};

void sendData(uint8_t data);
void sendCommand(uint8_t cmd);
void initDisplay(gpiod_chip *chip);
void clearScreen();
void setCursor(uint8_t row, uint8_t offset);
void drawText(const char* text, uint8_t row, uint8_t offset);
void drawEmoji(const char* text, uint8_t row, uint8_t offset);


#endif //DISPLAY_H
