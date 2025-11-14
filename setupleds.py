import board
import neopixel
import time
import random
import numpy as np
import cv2
import subprocess

#use for first process through only

numPix = 5

##
##pixels = neopixel.NeoPixel(board.D18,numPix,brightness = 1,auto_write = True)
##
##def cameraRun():
##        
##    for loop in range(1,numPix+1):
##        pixels[loop-1] = (255,0,0)
##        subprocess.run(["fswebcam","-r","640x480","--no-banner","pixel"+str(loop)+".jpeg"])
##        time.sleep(3)
##        pixels[loop-1] = (0,0,0)
##
##cameraRun()

##later

pixelPoints = {}

def loadImages():
    for loop2 in range(1,numPix+1):
        
        tempImg2 = cv2.imread("pixel"+str(loop2)+".jpeg",cv2.IMREAD_COLOR)
        tempImg = cv2.imread("pixel"+str(loop2)+".jpeg",cv2.IMREAD_GRAYSCALE)
    
        _, threshold = cv2.threshold(tempImg, 200, 255, cv2.THRESH_BINARY)

        _, contours, _ = cv2.findContours(threshold, cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

        #js use first and most contouring contour for the pixel

        contl = max(contours, key=cv2.contourArea)

        approx = cv2.approxPolyDP(contl, 0.009*cv2.arcLength(contl, True), True)

##        cv2.drawContours(tempImg2, [approx], 0, (0,0,255),1)


        points = approx.reshape(-1, 2)

        sumX = 0
        sumY = 0
        for (x,y) in points:
            sumX+=x
            sumY+=y
            
        #ITS CLOSE ENOUGH OKAY
            
        avgX = int(sumX/len(points))
        avgY = int(sumY/len(points))

##        cv2.circle(testimg2,(avgX,avgY), 1,(0,0,255),-1)
##
##        print("avgs:",avgX,avgY)
##
##        cv2.imshow('Contour Chart',tempImg2)


        pixelPoints["pixel"+str(loop2)+".jpeg"]=(avgX,avgY)

        
            
##    if cv2.waitKey(0) & 0xFF == ord('q'):
##            
##        cv2.destroyAllWindows()

loadImages()


savePath = "/home/pi/ledproject/pixelPoints.txt"

with open(savePath, 'w') as file:
    for loop4 in pixelPoints:
        entry = loop4+","+"["+str(pixelPoints[loop4][0])+","+str(pixelPoints[loop4][1])+"]\n"
        file.write(entry)
    file.close()
        

##numpix = 50
##pixels = neopixel.NeoPixel(board.D18,50,brightness =1,auto_write = True)
##
##index = 0
##
##while True:
##    if index == 50:
##        index = 0
##        
##    for loop in range(numpix):
##        
####        pixels[loop] = (255,0,0)
##
##        
##        r=random.randint(0,255)
##        g=random.randint(0,255)
##        b=random.randint(0,255)
##        
####        pixels[index] = (0,0,0)
##        pixels[loop] = (r,g,b)
##
####    index+=1
##    time.sleep(5)











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

