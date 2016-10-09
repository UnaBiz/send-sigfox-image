//  Test program for JPEGDecoder, to be run on desktop.
#ifndef ARDUINO
//#include <iostream>
#include <stdio.h>
#include "../JPEGDecoder.h"

int main() {
    //std::cout << "Hello, World!" << std::endl;
    const char filename[] = "photo.jpg";

    // Decoding start
    int result = JpegDec.decode((char *) filename,0);
    printf("result=%d\n", result);

    // Image Information
    printf("Width     :");
    printf("%d\n", JpegDec.width);
    printf("Height    :");
    printf("%d\n", JpegDec.height);
    printf("Components:");
    printf("%d\n", JpegDec.comps);
    printf("MCU / row :");
    printf("%d\n", JpegDec.MCUSPerRow);
    printf("MCU / col :");
    printf("%d\n", JpegDec.MCUSPerCol);
    printf("Scan type :");
    printf("%d\n", JpegDec.scanType);
    printf("MCU width :");
    printf("%d\n", JpegDec.MCUWidth);
    printf("MCU height:");
    printf("%d\n", JpegDec.MCUHeight);
    printf("\n");

    // Output CSV
    char str[100];
    sprintf(str,"#SIZE,%d,%d",JpegDec.width,JpegDec.height);
    puts(str);

    while(JpegDec.read()){
        uint8 *pImg = (uint8 *) JpegDec.pImage ;
        if (pImg == 0) break;

        for(int by=0; by<JpegDec.MCUHeight; by++){

            for(int bx=0; bx<JpegDec.MCUWidth; bx++){

                int x = JpegDec.MCUx * JpegDec.MCUWidth + bx;
                int y = JpegDec.MCUy * JpegDec.MCUHeight + by;
                //printf("MCU x=%d, y=%d, width=%d, height=%d\n", JpegDec.MCUx, JpegDec.MCUy, JpegDec.MCUWidth, JpegDec.MCUHeight);

                if(x<JpegDec.width && y<JpegDec.height){

                    if(JpegDec.comps == 1){ // Grayscale

                        sprintf(str,"#RGB,%d,%d,%u", x, y, pImg[0]);
                        //puts(str);

                    }else{ // RGB

                        sprintf(str,"#RGB,%d,%d,%u,%u,%u", x, y, pImg[0], pImg[1], pImg[2]);
                        puts(str);
                    }
                }
                pImg += JpegDec.comps ;
            }
        }
    }

    return 0;
}
#endif  ////  ARDUINO
