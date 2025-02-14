//
// Created by pi on 2/14/25.
//

#include "display.h"

#include <cstring>

gpiod_chip *chiplocal;

// Functie om een commando te sturen

void sendCommand(uint8_t cmd) {
    gpioWriteOutput(chiplocal,RS, 0);  // Commando-modus
    gpioWriteOutput(chiplocal,CS1, 1);
    gpioWriteOutput(chiplocal,CS2, 1);

    for (int i = 0; i < 8; i++) {
        gpioWriteOutput(chiplocal,DATA_PINS[i], (cmd >> i) & 1);
    }

    gpioWriteOutput(chiplocal,EN, 1);
    usleep(1);
    gpioWriteOutput(chiplocal,EN, 0);
}

// Initialiseer het LCD
void initDisplay(gpiod_chip *chip) {
    chiplocal = chip;

    gpioSetOutputPin(chip,RS);
    gpioSetOutputPin(chip,EN);
    gpioSetOutputPin(chip,CS1);
    gpioSetOutputPin(chip,CS2);
    gpioSetOutputPin(chip,RST);

    for (int i = 0; i < 8; i++) {
        gpioSetOutputPin(chip,DATA_PINS[i]);
    }

    gpioWriteOutput(chip,RST, 1); // Zet reset aan
    usleep(10000);
    sendCommand(0x003F);  // LCD inschakelen
}

// Functie om data te sturen (pixels of tekst)
void sendData(uint8_t data) {
    gpioWriteOutput(chiplocal,RS, 1); // Data-modus

    for (int i = 0; i < 8; i++) {
        gpioWriteOutput(chiplocal,DATA_PINS[i], (data >> i) & 1);
    }

    gpioWriteOutput(chiplocal,EN, 1);
    usleep(1);
    gpioWriteOutput(chiplocal,EN, 0);
}

// Scherm wissen
void clearScreen() {
    gpioWriteOutput(chiplocal,CS1, 1);
    gpioWriteOutput(chiplocal,CS2, 1);
    for (int page = 0; page < 8; page++) {
        sendCommand(0x00B8 | page); // Pagina selecteren
        sendCommand(0x0040);        // Zet cursor aan begin
        for (int col = 0; col < 64; col++) {
            sendData(0x00);
        }
    }
}

// Simpele functie om tekst weer te geven (geen font-rendering)
void drawText(const char* text, uint8_t row) {
    if(row > 7)
    {
        row = 7;
    }
    sendCommand(0xB8|row);  // Selecteer bovenste rij
    sendCommand(0x40);  // Zet cursor aan begin
    gpioWriteOutput(chiplocal,CS1, 1);
    gpioWriteOutput(chiplocal,CS2, 0);
    bool runonce = true;

    for (uint32_t i = 0; i < strlen(text); i++) {
        if (i>11 && runonce == true) {
            runonce = false;
            sendCommand(0x40);  // Zet cursor aan begin
            gpioWriteOutput(chiplocal,CS1, 0);
            gpioWriteOutput(chiplocal,CS2, 1);
        }
        for (uint8_t y = 0; y<=4;y++) {
            sendData(getLetterBitmap(text[i])[y]);
        }
    }

}

// Cirkel tekenen met de Midpoint Circle Algorithm
void drawCircle(int x0, int y0, int r) {
    int x = r, y = 0;
    int err = 0;

    while (x >= y) {
        sendData(0xFF);  // Simpel pixels aanzetten
        y++;
        if (err <= 0) {
            err += 2*y + 1;
        }
        if (err > 0) {
            x--;
            err -= 2*x + 1;
        }
    }
}

// Functie die de letter 'A' tot 'Z' omzet in 5x7 bitmaps
std::vector<uint8_t> getLetterBitmap(char letter) {
    switch (letter) {
        case 'A': return { 0x7E, 0x11, 0x11, 0x11, 0x7E };
        case 'B': return { 0x7F, 0x49, 0x49, 0x49, 0x36 };
        case 'C': return { 0x3E, 0x41, 0x41, 0x41, 0x22 };
        case 'D': return { 0x7F, 0x41, 0x41, 0x41, 0x3E };
        case 'E': return { 0x7F, 0x49, 0x49, 0x49, 0x41 };
        case 'F': return { 0x7F, 0x48, 0x48, 0x48, 0x40 };
        case 'G': return { 0x3E, 0x41, 0x49, 0x49, 0x2E };
        case 'H': return { 0x7F, 0x08, 0x08, 0x08, 0x7F };
        case 'I': return { 0x00, 0x41, 0x7F, 0x41, 0x00 };
        case 'J': return { 0x02, 0x01, 0x01, 0x01, 0x7E };
        case 'K': return { 0x7F, 0x08, 0x14, 0x22, 0x41 };
        case 'L': return { 0x7F, 0x01, 0x01, 0x01, 0x01 };
        case 'M': return { 0x7F, 0x20, 0x10, 0x20, 0x7F };
        case 'N': return { 0x7F, 0x20, 0x10, 0x08, 0x7F };
        case 'O': return { 0x3E, 0x41, 0x41, 0x41, 0x3E };
        case 'P': return { 0x7F, 0x09, 0x09, 0x09, 0x06 };
        case 'Q': return { 0x3E, 0x41, 0x41, 0x21, 0x3E };
        case 'R': return { 0x7F, 0x48, 0x48, 0x48, 0x78 };
        case 'S': return { 0x46, 0x49, 0x49, 0x49, 0x31 };
        case 'T': return { 0x01, 0x01, 0x7F, 0x01, 0x01 };
        case 'U': return { 0x3F, 0x01, 0x01, 0x01, 0x3F };
        case 'V': return { 0x1F, 0x20, 0x40, 0x20, 0x1F };
        case 'W': return { 0x7F, 0x01, 0x1E, 0x01, 0x7F };
        case 'X': return { 0x63, 0x14, 0x08, 0x14, 0x63 };
        case 'Y': return { 0x30, 0x0C, 0x03, 0x0C, 0x30 };
        case 'Z': return { 0x61, 0x51, 0x49, 0x45, 0x43 };

        // Kleine letters a-z
        case 'a': return { 0x20, 0x54, 0x54, 0x54, 0x78 };
        case 'b': return { 0x7F, 0x48, 0x48, 0x48, 0x30 };
        case 'c': return { 0x38, 0x44, 0x44, 0x44, 0x20 };
        case 'd': return { 0x30, 0x48, 0x48, 0x48, 0x7F };
        case 'e': return { 0x38, 0x54, 0x54, 0x54, 0x18 };
        case 'f': return { 0x08, 0x7E, 0x09, 0x01, 0x02 };
        case 'g': return { 0x0C, 0x52, 0x52, 0x52, 0x3E };
        case 'h': return { 0x7F, 0x08, 0x08, 0x08, 0x70 };
        case 'i': return { 0x00, 0x48, 0x7D, 0x40, 0x00 };
        case 'j': return { 0x20, 0x40, 0x40, 0x3D, 0x00 };
        case 'k': return { 0x7F, 0x10, 0x28, 0x44, 0x00 };
        case 'l': return { 0x00, 0x41, 0x7F, 0x40, 0x00 };
        case 'm': return { 0x7C, 0x04, 0x18, 0x04, 0x78 };
        case 'n': return { 0x7C, 0x08, 0x04, 0x04, 0x78 };
        case 'o': return { 0x38, 0x44, 0x44, 0x44, 0x38 };
        case 'p': return { 0x7C, 0x14, 0x14, 0x14, 0x08 };
        case 'q': return { 0x08, 0x14, 0x14, 0x14, 0x7C };
        case 'r': return { 0x7C, 0x08, 0x04, 0x04, 0x08 };
        case 's': return { 0x48, 0x54, 0x54, 0x54, 0x20 };
        case 't': return { 0x04, 0x3F, 0x44, 0x40, 0x20 };
        case 'u': return { 0x3C, 0x40, 0x40, 0x20, 0x7C };
        case 'v': return { 0x1C, 0x20, 0x40, 0x20, 0x1C };
        case 'w': return { 0x3C, 0x40, 0x30, 0x40, 0x3C };
        case 'x': return { 0x44, 0x28, 0x10, 0x28, 0x44 };
        case 'y': return { 0x0C, 0x50, 0x50, 0x50, 0x3C };
        case 'z': return { 0x44, 0x64, 0x54, 0x4C, 0x44 };

        // Speciale tekens
        case ' ': return { 0x00, 0x00, 0x00, 0x00, 0x00 }; // Spatie
        case '!': return { 0x00, 0x00, 0x5F, 0x00, 0x00 }; // Uitroepteken
        case '?': return { 0x20, 0x40, 0x4D, 0x48, 0x30 }; // Vraagteken
        case '.': return { 0x00, 0x00, 0x40, 0x00, 0x00 }; // Punt
        default: return { 0x00, 0x00, 0x00, 0x00, 0x00 }; // Onbekend teken
    }
}