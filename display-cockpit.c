#include <display.h>
#include <PCF8574.h>
#include <stdio.h>

void app_main(void)
{
    i2c_master_init();
    initDisplay();
    clearScreen();

    for (int i =0; i < 8; i++) {
        drawText("|",i,30);
        drawText("|",i,98);
    }
    drawEmoji("E",0,108);
    drawText("100%",1,102);

    drawText("Temp:", 0, 1);
    drawText("75*C",1,5);

    drawText("Hoek:", 4,1);
    drawText("10*", 5,5);

}
