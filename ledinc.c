//#include <ws2811.h>
//#include <unistd.h>
//#include <cstdlib>
//#include <ctime>

//numpix = 50

//ws2811_t ledstring =
//{	
	//.freq = TARGET_FREQ,
	//.dmanum = DMA,
	//.channel = {
		//[0] = {
			//.gpionum = 18,
			//.count = numpix,
			//.brightness = 255,
			//.strip_type = ST?,
		//},
		//[1] = {0}
	//}
//};

//int main() 
//{
	//srand(time(NULL));
	//if (ws2811_init(&ledstring) != WS2811_SUCCESS) {
		//std::cerr << "no" << std::endl;
		//return -1;
	//for (int i = 0,i = numpix-1,i++) {
		//int r = rand() % 255;
		//int g = rand() % 255;
		//int b = rand() % 255;
		//ledstring.channel[0].leds[i] = (r<<16) | (g<<8) | b;	
	//}

	//ws2811_render(&ledstring);
	//sleep(2);

	//return 0; 
//}


#include "ws2811.h"
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define LED_COUNT 50              // Number of LEDs in your strip
#define GPIO_PIN 18               // Usually GPIO 18 (PWM0)
#define DMA 10
#define STRIP_TYPE WS2811_STRIP_RGB // For WS2811

bool flag = true;

ws2811_t ledstring =
{
    .render_wait_time = 0,                   //< time in µs before the next render can run
    .device = 0,                //< Private data for driver use
    .rpi_hw = 0,                   //< RPI Hardware Information
    .freq = WS2811_TARGET_FREQ,
    .dmanum = DMA,
    .channel =
    {
        [0] =
        {
            .gpionum = GPIO_PIN,
            .count = LED_COUNT,
            .invert = 0,
            .brightness = 255,
            .strip_type = STRIP_TYPE,
        },
        [1] =
        {
            .gpionum = 0,
            .count = 0,
            .invert = 0,
            .brightness = 0,
        },
    },
};

int getInfo(int *avgX, int *avgY) {
    FILE *fvar = fopen("pixelPoints2.txt","r");
    if (fvar == NULL) {
	//cuz stdio.h
	printf("error -- file openings");
	return 1;
    }
    
    char readbuffer[40];
    
    int ledcount = 0; 
    
    while (fgets(readbuffer,sizeof(readbuffer), fvar)!=NULL) {
    //goest hrough each sp[ecific line

	sscanf(readbuffer,"%d,%d",&avgX[ledcount],&avgY[ledcount]);
	
	ledcount++;
    }
    
    fclose(fvar);
    return 0;
    
}

struct array_struct {
    int index;
    int posX;
    int posY;
};

int comparearrayXASC(const void *const tuple1, const void *const tuple2) {
    const struct array_struct *s1;
    const struct array_struct *s2;
    
    s1 = tuple1;
    s2 = tuple2;
    
    return s1->posX - s2->posX;
}

int comparearrayXDSC(const void *const tuple1, const void *const tuple2) {
    const struct array_struct *s1;
    const struct array_struct *s2;
    
    s1 = tuple1;
    s2 = tuple2;
    
    return s2->posX - s1->posX;
}

int comparearrayYASC(const void *const tuple1, const void *const tuple2) {
    const struct array_struct *s1;
    const struct array_struct *s2;
    
    s1 = tuple1;
    s2 = tuple2;
    
    return s1->posY - s2->posY;
}

int comparearrayYDSC(const void *const tuple1, const void *const tuple2) {
    const struct array_struct *s1;
    const struct array_struct *s2;
    
    s1 = tuple1;
    s2 = tuple2;
    
    return s2->posY - s1->posY;
}

int main()
{
    int avgX[LED_COUNT];
    int avgY[LED_COUNT];
    size_t size;
    size_t count;

    getInfo(avgX,avgY);
    
    struct array_struct pixelArray[LED_COUNT];
    
    for (int i = 0; i<LED_COUNT; i++) {
	pixelArray[i].index = i;
	pixelArray[i].posX = avgX[i];
	pixelArray[i].posY = avgY[i];
    }
        
    size = sizeof(pixelArray[0]);
    count = sizeof(pixelArray)/size;
    
    qsort(pixelArray, count, size, comparearrayXASC);
    
    for (int i = 0; i < LED_COUNT; i++) {
	printf("%d, %d, %d\n", pixelArray[i].index, pixelArray[i].posX, pixelArray[i].posY);
    }
    
    
    
    if (ws2811_init(&ledstring))
        return -1;
    
    for (int i = 0; i < LED_COUNT; i++) {
	ledstring.channel[0].leds[pixelArray[i].index] = 0x00FF00;
	ws2811_render(&ledstring);
	usleep(500000);
	ledstring.channel[0].leds[pixelArray[i].index] = 0x000000;
	ws2811_render(&ledstring);
	
    }

    qsort(pixelArray, count, size, comparearrayXDSC);
    
    for (int i = 1; i < LED_COUNT; i++) {
	ledstring.channel[0].leds[pixelArray[i].index] = 0x00FF00;
	ws2811_render(&ledstring);
	usleep(500000);
	ledstring.channel[0].leds[pixelArray[i].index] = 0x000000;
	ws2811_render(&ledstring);
	
    }	

    
    //while (flag = true) {
	////for (int i = 0; i < LED_COUNT; i++) {
	    ////ledstring.channel[0].leds[i] = 0x00FF00;
	    ////ws2811_render(&ledstring);
	    ////sleep(5);
	////}
	//for (int i = 0; i < LED_COUNT; i++) {
	    //int r = rand() % 255;
	    //int g = rand() % 255;
	    //int b = rand() % 255;
	    //ledstring.channel[0].leds[i] = (r<<16) | (g<<8) | b; 
	//}
	//ws2811_render(&ledstring);
	//sleep(1);
    //}
	
    
    
    return 0;
}
