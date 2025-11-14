import board
import neopixel
import time
import random


numpix = 50
pixels = neopixel.NeoPixel(board.D18,50,brightness =1,auto_write = True)

index = 0

while True:
    if index == 50:
        index = 0
        
    for loop in range(numpix):
        
##        pixels[loop] = (255,0,0)

        
        r=random.randint(0,255)
        g=random.randint(0,255)
        b=random.randint(0,255)
        
##        pixels[index] = (0,0,0)
        pixels[loop] = (r,g,b)

##    index+=1
    time.sleep(5)











##while True:
##
##    r=random.randint(0,255)
##    g=random.randint(0,255)
##    b=random.randint(0,255)
##    
##    pixels.fill((r,g,b))                        
##    time.sleep(1)
## 

                                           
##pixels.fill((0,0,0))
##sleep (2)
##pixels.fill((255,0,0))
##sleep (2)
##pixels.fill((0,255,0))
##sleep (2)
##pixels.fill((0,0,255))
##pixels.show()

