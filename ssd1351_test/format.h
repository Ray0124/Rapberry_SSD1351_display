//#include <pshpack2.h>

#pragma pack(2)

typedef struct tagBITMAPFILEHEADER {
unsigned short int bfType;
 unsigned long int bfSize;
 unsigned short int bfReserved1;
 unsigned short int bfReserved2;
 unsigned long int bfOffBits;
  
}BITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER {
 unsigned long int  biSize;
 unsigned long int  biWidth;
 unsigned long int  biHeight;
 unsigned short int biPlanes;
 unsigned short int biBitCount;
 unsigned long int  biCompression;
 unsigned long int  biSizeImage;
 unsigned long int  biXPelsPerMeter;
 unsigned long int  biYPelsPerMeter;
 unsigned long int  biClrUsed;
 unsigned long int  biClrImportant;

}BITMAPINFOHEADER;


/*typedef struct _PixelInfo {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} PixelInfo;*/ 



//#include <poppack.h>
