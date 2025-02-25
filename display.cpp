//
// Created by pi on 2/14/25.
//

#include "display.h"

#include <cstring>

gpiod_chip* chiplocal;

// Functie om een commando te sturen

void sendCommand(uint8_t cmd) {
    gpioWriteOutput(chiplocal, RS, 0);  // Commando-modus
    gpioWriteOutput(chiplocal, CS1, 1);
    gpioWriteOutput(chiplocal, CS2, 1);

    for (int i = 0; i < 8; i++) {
        gpioWriteOutput(chiplocal, DATA_PINS[i], (cmd >> i) & 1);
    }

    gpioWriteOutput(chiplocal, EN, 1);
    usleep(1);
    gpioWriteOutput(chiplocal, EN, 0);
}

// Functie om data te sturen (pixels of tekst)
void sendData(uint8_t data) {
    gpioWriteOutput(chiplocal, RS, 1); // Data-modus

    for (int i = 0; i < 8; i++) {
        gpioWriteOutput(chiplocal, DATA_PINS[i], (data >> i) & 1);
    }

    gpioWriteOutput(chiplocal, EN, 1);
    usleep(1);
    gpioWriteOutput(chiplocal, EN, 0);
}

// Initialiseer het LCD
void initDisplay(gpiod_chip* chip) {
    chiplocal = chip;

    gpioSetOutputPin(chip, RS);
    gpioSetOutputPin(chip, EN);
    gpioSetOutputPin(chip, CS1);
    gpioSetOutputPin(chip, CS2);
    gpioSetOutputPin(chip, RST);

    for (int i = 0; i < 8; i++) {
        gpioSetOutputPin(chip, DATA_PINS[i]);
    }

    gpioWriteOutput(chip, RST, 1); // Zet reset aan
    usleep(10000);
    sendCommand(0x003F);  // LCD inschakelen
}

// Scherm wissen
void clearScreen() {
    gpioWriteOutput(chiplocal, CS1, 1);
    gpioWriteOutput(chiplocal, CS2, 1);
    for (int page = 0; page < 8; page++) {
        sendCommand(0x00B8 | page); // Pagina selecteren
        sendCommand(0x0040);        // Zet cursor aan begin
        for (int col = 0; col < 64; col++) {
            sendData(0x00);
        }
    }
}

//functie om cursor op de plek te zetten.
void setCursor(uint8_t row = 0, uint8_t offset = 0)
{
    bool check1 = true;
    bool check2 = false;
    uint8_t column = offset;
    if (row > 7)
    {
        row = 7;
    }
    if (offset > 63 && offset <= 127)
    {
        column = offset - 63;
        check1 = false;
        check2 = true;
    }
    else if (offset > 127)
    {
        column = 0;
    }

    sendCommand(0xB8 | row);         // Selecteer een rij
    sendCommand(0x40 | column);      // Zet cursor

    gpioWriteOutput(chiplocal, CS1, check1);
    gpioWriteOutput(chiplocal, CS2, check2);
}


// Simpele functie om tekst weer te geven (geen font-rendering)
void drawText(const char* text, uint8_t row, uint8_t offset) {
    uint8_t cnt = offset;
    for (uint32_t i = 0; i < strlen(text); i++) {
        std::vector<uint8_t> bitmap = getLetterBitmap(text[i]);
        for (size_t y = 0; y < bitmap.size(); y++) {
            setCursor(row, cnt);
            cnt++;
            sendData(bitmap[y]);
        }
    }
}

void drawEmoji(const char* text, uint8_t row, uint8_t offset) {
    uint8_t cnt = offset;
    for (uint32_t i = 0; i < strlen(text); i++) {
        std::vector<uint8_t> bitmap = getEmojiBitmap(text[i]);
        for (size_t y = 0; y < bitmap.size(); y++) {
            setCursor(row, cnt);
            cnt++;
            sendData(bitmap[y]);
        }
    }
}

