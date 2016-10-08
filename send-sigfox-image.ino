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
  return; //
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

void loop()
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
    if( !camera.initial( CameraC328R::CT_GRAYSCALE_4, CameraC328R::PR_160x120,
      CameraC328R::JR_160x128 ) )
    {
      Serial.println( "Initial failed." );
      return;
    }
    debug("setPackageSize");
    if( !camera.setPackageSize( 64 ) )
    {
      Serial.println( "Package size failed." );
      return;
    }
    debug("setLightFrequency");
    if( !camera.setLightFrequency( CameraC328R::FT_50Hz ) )
    {
      Serial.println( "Light frequency failed." );
      return;
    }
    debug("snapshot");
    if( !camera.snapshot( CameraC328R::ST_COMPRESSED, 0 ) )
    {
      Serial.println( "Snapshot failed." );
      return;
    }
    pictureSizeCount = 0;
    debug("getJPEGPicture");
    if( !camera.getJPEGPicture( CameraC328R::PT_JPEG, PROCESS_DELAY,
      &getJPEGPicture_callback ) )
    {
      Serial.println( "Get JPEG failed." );
      return;
    }
  }
  
  for(;;) {}  //  Stop here.
}
