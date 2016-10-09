//  For Arduino, this class reads the image from the Grove Serial Camera.  For desktop, this class reads from filesystem.

#ifdef ARDUINO
    #include <Arduino.h>
#else  //  ARDUINO
    #include <stdio.h>
    #include <string.h>
    #include <sys/stat.h>
#endif  //  ARDUINO

#include "CameraReader.h"

#ifdef ARDUINO
unsigned int CameraReader::fileSize = 0;
bool CameraReader::requestingPos = false;
unsigned int CameraReader::requestedPos = 0;
#endif  //  ARDUINO

int CameraReader::open(char *filename0) {
    //  Return 0 if file cannot be opened.
    filename = filename0;
#ifdef ARDUINO
    Serial.print("CameraReader::open "); Serial.println(filename0);
    filePos = 0;
#else  //  ARDUINO
    printf("CameraReader::open %s\n", filename0);
    file = fopen(filename, "rb"); if (file == NULL) return 0;
#endif  //  ARDUINO
    return 1;
}

unsigned int CameraReader::size() {
#ifdef ARDUINO
    Serial.print("CameraReader::size "); Serial.print(fileSize); Serial.println(" bytes");
#else  //  ARDUINO
    struct stat st; stat(filename, &st); fileSize = (unsigned int) st.st_size;
    printf("CameraReader::size %d bytes\n", fileSize);
#endif  //  ARDUINO
    return fileSize;
}

void CameraReader::read(unsigned char *buf, unsigned int len) {
#ifdef ARDUINO
    Serial.print("CameraReader::read "); Serial.print(len); Serial.print(" bytes at pos ");  Serial.println(filePos);
    //  Sleep until the camera returns the data.
    requestedPos = filePos;
    requestingPos = true;
    for (;;) {
        delay(1000);
        Serial.print("CameraReader::read waiting for pos ");  Serial.println(filePos);
    }
    filePos = filePos + len;
#else  //  ARDUINO
    printf("CameraReader::read %d bytes\n", len);
    fread(buf, 1, len, file);
#endif  //  ARDUINO
}

void CameraReader::close() {
#ifdef ARDUINO
    Serial.println("CameraReader::close");
#else  //  ARDUINO
    puts("CameraReader::close");
    fclose(file);
    file = 0;
#endif  //  ARDUINO
}
