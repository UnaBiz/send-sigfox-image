//  For Arduino, this class reads the image from the Grove Serial Camera.  For desktop, this class reads from filesystem.
#ifndef CAMERAREADER_H
#define CAMERAREADER_H

class CameraReader {
public:
    int open(char *filename);
    unsigned int size();
    void read(unsigned char *buf, unsigned int len);
    void close();
    char *filename = 0;
#ifdef ARDUINO
    static unsigned int fileSize;
    static bool requestingPos;
    static unsigned int requestedPos;
    unsigned int filePos = 0;
#else  //  ARDUINO
    FILE *file = 0;
#endif  //  ARDUINO
};

#endif //  CAMERAREADER_H
