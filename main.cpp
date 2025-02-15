#include <gpiod.h>
#include <iostream>
#include <unistd.h>// Voor sleep()
#include "display.h"
gpiod_chip *chip;
int main() {

	//For Raspberry Pi 5 use gpiochip4 (For Raspberry Pi 4 use gpiochip0)
    const char *chipname = "gpiochip4";

    chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        std::cerr << "Could not open chip." << std::endl;
        return 1;
    }

    
    initDisplay(chip);
    clearScreen();
    sleep(2);
    drawText("Hello There!I print text", 0);
    drawText("By Thijs Hulshof", 7);
    drawText("HAN SolarBoat", 3);
    sleep(2);
    //clearScreen();

    gpiod_chip_close(chip);
    return 0;
}