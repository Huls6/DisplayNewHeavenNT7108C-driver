//
// Created by pi on 2/14/25.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include <cstdint>
#include <unistd.h>
#include <gpiod.h>
#include "gpio.h"
#include <vector>


// GPIO pinnen defini�ren
#define RS  22
#define EN  27
#define CS1 23
#define CS2 24
#define RST 25

// Datapinnen D0-D7
inline int DATA_PINS[8] = {5, 6, 13, 19, 26, 16, 20, 21};

void sendData(uint8_t data);
void initDisplay(gpiod_chip *chip);
void clearScreen();
void drawText(const char* text, uint8_t row);
void drawCircle(int x0, int y0, int r);
void sendCommand(uint8_t cmd);
std::vector<uint8_t> getLetterBitmap(char letter);

#endif //DISPLAY_H
