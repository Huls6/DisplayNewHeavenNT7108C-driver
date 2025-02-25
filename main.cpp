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
    for (int i =0; i < 8; i++) {
        drawText("|",i,30);
        drawText("|",i,98);
    }
    drawEmoji("M",0,108);
    drawText("100%",1,102);

    drawText("Temp:", 0, 1);
    drawText("75*C",1,5);

    drawText("Hoek:", 4,1);
    drawText("10*", 5,5);



    sleep(2);
    //clearScreen();

    gpiod_chip_close(chip);
    return 0;
}