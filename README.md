# SSD1351_display
For SSD1351,the max size is 128x128,and the color depth is 16bit(RGB565).  
This is a C-programe to let raspbeery control SSD1351-base size 128X128 display.  
The size of RGB565 Bmp pictures under 128X128 can display on SSD1351-base size 128X128 display.  
Use bcm2835 library to control raspberry's gpio.  
It uses pixels way and bmp structure to fill the frame of the IC.  
You can replace the sample bmp in code, but it needs RGB565 and size under 128*128 bmp, and you need to change positions by the function of IC.



For Raspberry Pi 3 Model B:  
4wire-spi  
pin40: cs  
pin38: dc  
pin36: rst  
pin19: mosi  
pin23: sclk  
pin2: 5v  
pin6: GND  




1.Use "make" to compile the project,and run "sudo ./spi".  
2.Use "make clean" to clear spi and .o file

128:  
![image](https://github.com/Ray0124/Rapberry_SSD1351_display/blob/master/128.jpg)  
64:  
![image](https://github.com/Ray0124/Rapberry_SSD1351_display/blob/master/64.jpg)  
120x100:  
![image](https://github.com/Ray0124/Rapberry_SSD1351_display/blob/master/120x100.jpg)  
