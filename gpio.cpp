//
// Created by pi on 2/14/25.
//

#include "gpio.h"


int gpioSetOutputPin(gpiod_chip *chip, int gpiopin) {
    gpiod_line *line = gpiod_chip_get_line(chip, gpiopin);
    if (!line) {
        std::cerr << "Could not get line." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }
    if (gpiod_line_request_output(line, "default", 0) < 0) {
        std::cerr << "Could not set line as output." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }
    return 0;
}

int gpioSetInputPin(gpiod_chip *chip, int gpiopin) {
    gpiod_line *line = gpiod_chip_get_line(chip, gpiopin);
    if (!line) {
        std::cerr << "Could not get line." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }
    if (gpiod_line_request_input(line, "default") < 0) {
        std::cerr << "Could not set line as input." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }
    return 0;
}

int gpioWriteOutput(gpiod_chip *chip, int gpiopin, int value)
{
    gpiod_line *line = gpiod_chip_get_line(chip, gpiopin);
    if (!line) {
        std::cerr << "Could not get line." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }
    gpiod_line_set_value(line, value);
}