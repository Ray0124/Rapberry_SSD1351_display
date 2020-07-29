/*************************************************** 
  This is a library for the 1.5" & 1.27" 16-bit Color OLEDs 
  with SSD1331 driver chip

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1431
  ------> http://www.adafruit.com/products/1673

  These displays use SPI to communicate, 4 or 5 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <stdio.h>
#include "Adafruit_SSD1351.h"
#include "bcm2835.h"


#ifndef _BV
    #define _BV(bit) (1<<(bit))
#endif

/********************************** low level pin interface */


void Adafruit_SSD1351::writeCommand(uint8_t c) {
    bcm2835_gpio_clr(_dc);
    bcm2835_gpio_clr(_cs);
    bcm2835_spi_transfer(c);
    bcm2835_gpio_set(_cs);

}


void Adafruit_SSD1351::writeData(uint8_t c) {
    bcm2835_gpio_set(_dc);
    bcm2835_gpio_clr(_cs);
    bcm2835_spi_transfer(c);
    bcm2835_gpio_set(_cs);
}

void Adafruit_SSD1351::fillScreen(uint16_t fillcolor) {
  rawFillRect(0, 0, SSD1351WIDTH, SSD1351HEIGHT, fillcolor);
}

// Draw a filled rectangle with no rotation.
void Adafruit_SSD1351::rawFillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t fillcolor) {
  // Bounds check
  if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT))
    return;

  // Y bounds check
  if (y+h > SSD1351HEIGHT)
  {
    h = SSD1351HEIGHT - y - 1;
  }

  // X bounds check
  if (x+w > SSD1351WIDTH)
  {
    w = SSD1351WIDTH - x - 1;
  }
  
  // set location
  writeCommand(SSD1351_CMD_SETCOLUMN);
  writeData(x);
  writeData(x+w-1);
  writeCommand(SSD1351_CMD_SETROW);
  writeData(y);
  writeData(y+h-1);
  // fill!
  writeCommand(SSD1351_CMD_WRITERAM);  

  for (uint16_t i=0; i < w*h; i++) {
    writeData(fillcolor >> 8);
    writeData(fillcolor);
  }
}

void Adafruit_SSD1351::begin(void) {
    bcm2835_gpio_set(_reset);    delayMicroseconds(1000);
    bcm2835_gpio_clr(_reset);    delayMicroseconds(1000);
    bcm2835_gpio_set(_reset);    delayMicroseconds(1000);

    // Initialization Sequence
    // Initialization Sequence
#if 0
    writeCommand(SSD1351_CMD_COMMANDLOCK);  // set command lock
    writeData(0x12);
    writeCommand(SSD1351_CMD_COMMANDLOCK);  // set command lock
    writeData(0xB1);

    writeCommand(SSD1351_CMD_DISPLAYOFF);  		// 0xAE

    writeCommand(SSD1351_CMD_CLOCKDIV);  		// 0xB3
    writeCommand(0xF1);  						// 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)

    writeCommand(SSD1351_CMD_MUXRATIO);
    writeData(127);

    writeCommand(SSD1351_CMD_SETREMAP);
    writeData(0x77);

    writeCommand(SSD1351_CMD_SETCOLUMN);
     writeData(0x00);
    writeData(0x7a);
    writeCommand(SSD1351_CMD_SETROW);
     writeData(0x00);
    writeData(0x7a);

    writeCommand(SSD1351_CMD_STARTLINE); 		// 0xA1
    if (SSD1351HEIGHT == 96) {
      writeData(96);
    } else {
      writeData(0);
    }


    writeCommand(SSD1351_CMD_DISPLAYOFFSET); 	// 0xA2
    writeData(0x0);

    writeCommand(SSD1351_CMD_SETGPIO);
    writeData(0x00);

    writeCommand(SSD1351_CMD_FUNCTIONSELECT);
    writeData(0x01); // internal (diode drop)
    //writeData(0x01); // external bias

//    writeCommand(SSSD1351_CMD_SETPHASELENGTH);
//    writeData(0x32);

    writeCommand(SSD1351_CMD_PRECHARGE);  		// 0xB1
    writeCommand(0x32);

    writeCommand(SSD1351_CMD_VCOMH);  			// 0xBE
    writeCommand(0x05);

    writeCommand(SSD1351_CMD_NORMALDISPLAY);  	// 0xA6

    writeCommand(SSD1351_CMD_CONTRASTABC);
        writeData(0x36);
		 writeData(0x7f);
		 writeData(0x69);

    writeCommand(SSD1351_CMD_CONTRASTMASTER);
    writeData(0x0F);

    writeCommand(SSD1351_CMD_SETVSL );
    writeData(0xA0);
    writeData(0xB5);
    writeData(0x55);

    writeCommand(SSD1351_CMD_PRECHARGE2);
    writeData(0x01);

    writeCommand(SSD1351_CMD_DISPLAYON);		//--turn on oled panel
    
    
    
    
    
#endif 
    writeCommand(SSD1351_CMD_COMMANDLOCK);  // set command lock
    writeData(0x12);
    writeCommand(SSD1351_CMD_COMMANDLOCK);  // set command lock
    writeData(0xB1);

    writeCommand(SSD1351_CMD_DISPLAYOFF);  		// 0xAE

    writeCommand(SSD1351_CMD_CLOCKDIV);  		// 0xB3
    writeCommand(0xF1);  						// 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)

    writeCommand(SSD1351_CMD_MUXRATIO);
    writeData(127);

    writeCommand(SSD1351_CMD_SETREMAP);
    if(_panel_direction==0)
       writeData(0x74);  //74 //66  //77
    else if(_panel_direction==1)
        writeData(0x77);  //66  //74  //65
	else if(_panel_direction==2)
        writeData(0x77);  //66  //74  //65
	else
		writeData(0x40); 
    writeCommand(SSD1351_CMD_SETCOLUMN);
    writeData(0x00);
    writeData(0x7a);
    writeCommand(SSD1351_CMD_SETROW);
    writeData(0x00);
    writeData(0x7a);

    writeCommand(SSD1351_CMD_STARTLINE); 		// 0xA1
    if (SSD1351HEIGHT == 96) {
      writeData(96);
    } else {
      writeData(0);
    }


    writeCommand(SSD1351_CMD_DISPLAYOFFSET); 	// 0xA2
    writeData(0x0);

    writeCommand(SSD1351_CMD_SETGPIO);
    writeData(0x00);

    writeCommand(SSD1351_CMD_FUNCTIONSELECT);
    writeData(0x01); // internal (diode drop)
    //writeData(0x01); // external bias

//    writeCommand(SSSD1351_CMD_SETPHASELENGTH);
//    writeData(0x32);

    writeCommand(SSD1351_CMD_PRECHARGE);  		// 0xB1
    writeCommand(0x00);

    writeCommand(SSD1351_CMD_VCOMH);  			// 0xBE
    writeCommand(0x05);

    writeCommand(SSD1351_CMD_NORMALDISPLAY);  	// 0xA6

    writeCommand(SSD1351_CMD_CONTRASTABC);
     if(_panel_direction==0)
	 {
		  writeData(0x3e);
    writeData(0xff);
		 writeData(0xC8);
	 }
	  else if(_panel_direction==1)
     {
		 writeData(0x1b);
		 writeData(0x7f);
		 writeData(0x54);
	 }
	 else if(_panel_direction==2)
     {
		 writeData(0x3e);
     writeData(0xff);
		 writeData(0xC8);
	 }
	 else 
     {
		 writeData(0x36);
		 writeData(0x7f);
		 writeData(0x54);
	 }
		
    writeCommand(SSD1351_CMD_CONTRASTMASTER);
    writeData(0x0F);

    writeCommand(SSD1351_CMD_SETVSL );
    writeData(0xA0);
    writeData(0xB5);
    writeData(0x55);

    writeCommand(SSD1351_CMD_PRECHARGE2);
    writeData(0x01);

    writeCommand(SSD1351_CMD_DISPLAYON);
    
    
    
}







void Adafruit_SSD1351::fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t fillcolor) {
  // Transform x and y based on current rotation.
    rawFillRect(x, y, w, h, fillcolor);
}
void Adafruit_SSD1351::fillFrame(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *frame_buffer)
{
    char *pimg=(char *)&frame_buffer[0];
  // Bounds check
  if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT))
    return;

  // Y bounds check
  if (y+h > SSD1351HEIGHT)
  {
    h = SSD1351HEIGHT - y - 1;
  }

  // X bounds check
  if (x+w > SSD1351WIDTH)
  {
    w = SSD1351WIDTH - x - 1;
  }

  // set location
  writeCommand(SSD1351_CMD_SETCOLUMN);
  writeData(x);
  writeData(x+w-1);
  writeCommand(SSD1351_CMD_SETROW);
  writeData(y);
  writeData(y+h-1);
  // fill!
  writeCommand(SSD1351_CMD_WRITERAM);

  bcm2835_gpio_set(_dc);
  bcm2835_gpio_clr(_cs);
  bcm2835_spi_transfern(pimg,w*h*2);
  bcm2835_gpio_set(_cs);
}

/********************************* low level pin initialization */

Adafruit_SSD1351::Adafruit_SSD1351(uint8_t cs, uint8_t dc,  uint8_t reset){
    _cs = cs;
    _dc = dc;
    _reset = reset;
    _panel_direction=0;

    bcm2835_gpio_fsel(_cs, BCM2835_GPIO_FSEL_OUTP);//RPI_BPLUS_GPIO_J8_24
    bcm2835_gpio_fsel(_dc, BCM2835_GPIO_FSEL_OUTP);//RPI_BPLUS_GPIO_J8_22
    bcm2835_gpio_fsel(_reset, BCM2835_GPIO_FSEL_OUTP);//RPI_BPLUS_GPIO_J8_18
}
Adafruit_SSD1351::Adafruit_SSD1351(uint8_t cs, uint8_t dc,  uint8_t reset, uint8_t panel_direction){
    _cs = cs;
    _dc = dc;
    _reset = reset;
    _panel_direction=panel_direction;

    bcm2835_gpio_fsel(_cs, BCM2835_GPIO_FSEL_OUTP);//RPI_BPLUS_GPIO_J8_24
    bcm2835_gpio_fsel(_dc, BCM2835_GPIO_FSEL_OUTP);//RPI_BPLUS_GPIO_J8_22
    bcm2835_gpio_fsel(_reset, BCM2835_GPIO_FSEL_OUTP);//RPI_BPLUS_GPIO_J8_18
}
