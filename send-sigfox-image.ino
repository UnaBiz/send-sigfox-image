#include <arduino.h>
#include <SoftwareSerial.h>
#include "CameraC328R.h"

#define PAGE_SIZE 64
#define USB_BAUD 9600
#define CAMERA_BAUD 9600

SoftwareSerial mySerial(2, 3);  //(rx, tx): Connect Grove Serial Camera to this rx/tx port (11-13 is used by sd shield)
CameraC328R camera(&mySerial);
uint16_t pictureSizeCount = 0;

/**
* This callback is called EVERY time a JPEG data packet is received.
*/
void getJPEGPicture_callback( uint16_t pictureSize, uint16_t packageSize,
  uint16_t packageCount, byte* package )
{
  // packageSize is the size of the picture part of the package
  pictureSizeCount += packageSize;
  Serial.write(package,packageSize);
  if( pictureSizeCount >= pictureSize )
  {
    //digitalWrite( LED_PIN, LOW );
    Serial.flush();
  }
}

void debug(String s) {
  //return; //
  Serial.println(s);
}

void setup()
{
  Serial.begin( USB_BAUD );
  debug("Starting"); ////
  mySerial.begin(CAMERA_BAUD);
  //pinMode( LED_PIN, OUTPUT );
  //digitalWrite( LED_PIN, LOW );
}

const uint16_t pictureBufferSize = 800;
byte pictureBuffer[pictureBufferSize];

void processImage()
{
  ////if( Serial.available() )
  {
    ////  Wait for a key press before capturing image.
    while(Serial.read() != -1);
    ////digitalWrite( LED_PIN, HIGH );
    debug("sync");
    if( !camera.sync() )
    {
      Serial.println( "Sync failed." );
      return;
    }    
    debug("initial");
    if( !camera.initial( CameraC328R::CT_GRAYSCALE_2, CameraC328R::PR_80x60,
      CameraC328R::JR_80x64 ) )
    {
      Serial.println( "Initial failed." );
      return;
    }
#if NOTUSED  ////
    debug("setPackageSize");
    if( !camera.setPackageSize( 64 ) )
    {
      Serial.println( "Package size failed." );
      return;
    }
#endif  ////
    debug("setLightFrequency");
    if( !camera.setLightFrequency( CameraC328R::FT_50Hz ) )
    {
      Serial.println( "Light frequency failed." );
      return;
    }
    debug("snapshot");
    ////if( !camera.snapshot( CameraC328R::ST_COMPRESSED, 0 ) )
    if( !camera.snapshot( CameraC328R::ST_UNCOMPRESSED, 0 ) )  ////
    {
      Serial.println( "Snapshot failed." );
      return;
    }
    pictureSizeCount = 0;
#if NOTUSED  ////
    debug("getJPEGPicture");
    if( !camera.getJPEGPicture( CameraC328R::PT_JPEG, PROCESS_DELAY,
      &getJPEGPicture_callback ) )
    {
      Serial.println( "Get JPEG failed." );
      return;
    }
#endif ////  NOTUSED    

    ////  Get uncompressed picture.
    uint16_t bufferSize = pictureBufferSize;
    uint16_t start = 0;
    uint16_t count = pictureBufferSize;
    memset(pictureBuffer, 0, pictureBufferSize);

    if (mySerial.overflow()) Serial.println("SoftwareSerial overflow 1!"); 
    mySerial.listen();
    byte req[] = {0xaa, 0x04, 0x01, 0x00, 0x00, 0x00};
    mySerial.write(req, sizeof(req));
    int i = 0;
    for (;;)
    {
      if (mySerial.overflow()) Serial.println("SoftwareSerial overflow 2!"); 
      int bytesRead = mySerial.readBytes(pictureBuffer, pictureBufferSize);
      if (mySerial.overflow()) Serial.println("SoftwareSerial overflow 3!"); 
      
      for (int j = 0; j < bytesRead; j++)
      {
        byte b = pictureBuffer[j];
        /*
        int b = mySerial.read();  ////
        if (b < 0) continue;  ////  Retry if not ready.
        */        
        if (b <= 15) Serial.print("0");
        Serial.print(b, HEX); Serial.print(" ");         
        i++;
        if (i % 20 == 0) {
          Serial.println("");   
          Serial.print(i);   
          Serial.print(": ");   
        }
      }
      Serial.print(".");
    }
    return;
    
    if (!camera.getPartialRawPicture(CameraC328R::PT_SNAPSHOT, (byte *) pictureBuffer, bufferSize, PROCESS_DELAY, start, count))
    {
      Serial.print( "Get raw picture failed. bufferSize: " );
      Serial.println(bufferSize);
      String s = "count="; s.concat(count); debug(s);
      Serial.write(pictureBuffer, count);     
      return;      
    }
    String s = "count="; s.concat(count); debug(s);
    Serial.write(pictureBuffer, count);     
  }  
}

void loop() {
  processImage();
  for(;;) {}  //  Stop here.
}
