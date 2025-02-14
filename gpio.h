//
// Created by pi on 2/14/25.
//

#ifndef GPIO_H
#define GPIO_H

#include <gpiod.h>
#include <iostream>

int gpioSetOutputPin(gpiod_chip *chip, int gpiopin);
int gpioSetInputPin(gpiod_chip *chip, int gpiopin);
int gpioWriteOutput(gpiod_chip *chip, int gpiopin, int value);



#endif //GPIO_H
