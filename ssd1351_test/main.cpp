#include <bcm2835.h>
#include "Adafruit_SSD1351.h"
#include "format.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>




union pixel{
    struct {
        unsigned char high;
        unsigned char low;
    } byte;
    unsigned short p;
};

unsigned short int frame_buffer_ori[128*128];
unsigned short int frame_buffer[128*128];
unsigned short int dummy[128*128];
unsigned short int frames[2][128*128];
unsigned char buf[200000];

BITMAPFILEHEADER FileHeader;    
BITMAPINFOHEADER InfoHeader;    
FILE *fp;                                           
int ImageX, ImageY;            
unsigned short int x;



int main(int argc, char **argv)
{
	short int i,j;

    int count=0,ret,cnt=0;
		
		if (!bcm2835_init())
		{
		  printf("bcm2835_init failed. Are you running as root??\n");
		  return 1;
		}

		if (!bcm2835_spi_begin())
		{
		  printf("bcm2835_spi_begin failed. Are you running as root??\n");
		  return 1;
		}else
        printf("bcm2835_spi_begin\n");
   
   
   
   
		bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
		bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
		bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16);    // The default
		bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);                  // The default
		bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

		Adafruit_SSD1351 tft1 = Adafruit_SSD1351(RPI_BPLUS_GPIO_J8_40,RPI_BPLUS_GPIO_J8_38,RPI_BPLUS_GPIO_J8_36,0);
		tft1.begin();
		tft1.fillRect(0, 0, 128, 128, 0x0000); 
		delay(2000);
	
	

	
while(1){
           fp=fopen("bridge_120x100.bmp","rb");
           
           fread(&FileHeader, sizeof(BITMAPFILEHEADER), 1, fp);    
           fread(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
			     ImageX = InfoHeader.biWidth;        
           ImageY = InfoHeader.biHeight;
           //printf("ImageX is %d\n",ImageX);
           //printf("ImageY is %d\n",ImageY);
           fread(&buf, ImageX*ImageY*2, 1, fp);
            count=0;
          for (int h=0;h<128;h++)                     
					   {
						   for(int w=0;w<128;w++)
						   {
		   
							   union pixel pix;
							   pix.byte.low  =buf[count++];
							   pix.byte.high =buf[count++];
							   frame_buffer_ori[h*128+w]=pix.p;
					         	
						   }
					   }
					   
	                	
			  	   
					   cnt=0;                                      
					   for(int h=0;h<128;h++)
					   { 
               cnt+=6;
						   memcpy(&frames[0][h*128],&frame_buffer_ori[cnt],256);cnt+=122;
        
					   }
			         tft1.fillFrame(0,0,ImageX,ImageY,frames[0]);
					     delay(5000);
               memset(frame_buffer,0x0000,256*256);    tft1.fillFrame(0,0,128,128,frame_buffer);
               fclose(fp);

                       
   
}   
  printf("\nDone, bye !\n");
		bcm2835_spi_end();
		bcm2835_close();
	return 0;  
   
 }  

   
   

   
		

