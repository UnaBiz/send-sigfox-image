//#include <iostream>
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

    return 0;
}