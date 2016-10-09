//  Sketch for Arduino to import a small image from Grove Serial Camera and send to SIGFOX cloud for processing.
//  Based on "LCF OV528 Protocol.pdf" and code from http://store.fut-electronics.com/products/ttl-serial-jpeg-camera-for-arduino-video-motion-detection-infrared-lenses
#include <arduino.h>
#include <SoftwareSerial.h>
#include "CameraC328R.h"

#define PAGE_SIZE 64
#define USB_BAUD 9600
#define CAMERA_BAUD 9600

SoftwareSerial mySerial(2, 3);  //(rx, tx): Connect Grove Serial Camera to this rx/tx port (11-13 is used by sd shield)
CameraC328R camera(&mySerial);
uint16_t pictureSizeCount = 0;

static void debug(String s) {
  Serial.println(s);
}

static void outputData(byte* data, uint16_t len) {
  //  Output the byte array to console for render_image to consume.
  Serial.print("[[[ ");  //  render_image watches for this marker.
  for( uint16_t i = 0; i < len; i++ )
  {
    int b = data[i];
    if (b <= 15) Serial.print("0"); ////
    Serial.print(b, HEX); Serial.print(" "); ////
  }
  Serial.println("]]]");  //  render_image watches for this marker.
}

void getJPEGPicture_callback( uint16_t pictureSize, uint16_t packageSize,
  uint16_t packageCount, byte* package )
{
  //  This callback is called EVERY time a JPEG data packet is received.  We output the packet to render_image.
  //  packageSize is the size of the picture part of the package
  pictureSizeCount += packageSize;
  outputData(package, packageSize);
  if( pictureSizeCount >= pictureSize )
  {
    //digitalWrite( LED_PIN, LOW );
    Serial.flush();
  }
}

//const uint16_t pictureBufferSize = 800;
//byte pictureBuffer[pictureBufferSize];

void setup()
{
  Serial.begin( USB_BAUD );
  debug("Starting");
  
  mySerial.begin(CAMERA_BAUD);
  //pinMode( LED_PIN, OUTPUT );
  //digitalWrite( LED_PIN, LOW );

  //  Sync and reset the camera.
  if( !camera.sync() ) { Serial.println( "Sync failed." ); return; }    
  if( !camera.reset(true) ) { Serial.println( "reset failed." ); return; }    
  delay(1000); mySerial.begin(CAMERA_BAUD);
}

bool captureImage()
{
  //  Capture image from camera.  Keep in camera memory for later processing.
  ////digitalWrite( LED_PIN, HIGH );
  
  //  Sync the camera before sending commands.
  if( !camera.sync() ) { Serial.println( "Sync failed." ); return false; }   
   
  ////if( !camera.initial( CameraC328R::CT_GRAYSCALE_2, CameraC328R::PR_80x60, CameraC328R::JR_80x64 ) )
  //  Init camera for colour capture at 320x420 resolution.  Only colour not grayscale supported on Grove Serial Camera.
  if( !camera.initial( (CameraC328R::ColorType) 7, (CameraC328R::PreviewResolution) 3, 
    (CameraC328R::JPEGResolution) 3 )) { Serial.println( "Initial failed." ); return false; }
    
  //  Tell camera to send images in packets of 64 bytes.
  if( !camera.setPackageSize( PAGE_SIZE )) { Serial.println( "Package size failed." ); return false; }
  
  //  Set the camera to 50 Hz instead of 60 Hz to reduce flicker.  Not sure if this is actually supported on Grove Serial Camera.
  if( !camera.setLightFrequency( CameraC328R::FT_50Hz )) { Serial.println( "Light frequency failed." ); return false; }
  
  //  Take a snaphot and keep in camera memory. Uncompressed mode not supported on Grove Serial Camera.
  if( !camera.snapshot( CameraC328R::ST_COMPRESSED, 0 )) { Serial.println( "Snapshot failed." ); return false; }

  //  Tell render_image we are sending a JPEG.
  Serial.println("[[[ BEGIN JPEG ]]]");
  
  //  Read in the JPEG compressed image, packet by packet.  Only JPEG preview picture mode supported on Grove Serial Camnera.
  pictureSizeCount = 0;
  //if( !camera.getJPEGPicture( CameraC328R::PT_JPEG, PROCESS_DELAY, &getJPEGPicture_callback ) )
  if( !camera.getJPEGPicture((CameraC328R::PictureType) 5, PROCESS_DELAY, 
    &getJPEGPicture_callback )) { Serial.println( "Get JPEG failed." ); return false; }

  //  Tell render_image we have finished sending a JPEG.
  Serial.println("[[[ END JPEG ]]]");

  return true;
}

void loop() {
  captureImage();
  //  Wait for a key press from console or render_image before capturing next image.
  //while(Serial.read() != -1);
  for(;;) {}  //  Stop here.
}

