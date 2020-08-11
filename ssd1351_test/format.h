//#include <pshpack2.h>

#pragma pack(2)

typedef struct tagBITMAPFILEHEADER {
unsigned short  bfType;
 unsigned long  bfSize;
 unsigned short bfReserved1;
 unsigned short bfReserved2;
 unsigned long  bfOffBits;
  
}BITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER {
 unsigned long   biSize;
 unsigned long   biWidth;
 unsigned long   biHeight;
 unsigned short  biPlanes;
 unsigned short  biBitCount;
 unsigned long   biCompression;
 unsigned long   biSizeImage;
 unsigned long   biXPelsPerMeter;
 unsigned long   biYPelsPerMeter;
 unsigned long   biClrUsed;
 unsigned long   biClrImportant;

}BITMAPINFOHEADER;


/*typedef struct _PixelInfo {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} PixelInfo;*/ 



//#include <poppack.h>
