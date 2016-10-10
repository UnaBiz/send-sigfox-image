//  Sketch for Arduino to import a small image from Grove Serial Camera and send to SIGFOX cloud for processing.
//  Based on "LCF OV528 Protocol.pdf" and code from http://store.fut-electronics.com/products/ttl-serial-jpeg-camera-for-arduino-video-motion-detection-infrared-lenses
#include <arduino.h>
#include <SoftwareSerial.h>
#include "CameraC328R.h"
#include "CameraReader.h"
#include "JPEGDecoder.h"

#define PAGE_SIZE 64  //  Size of packets to be sent by camera.
#define USB_BAUD 9600
#define CAMERA_BAUD 9600  //  Doesn't work when using a higher baud.

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
  Serial.println("]]]");  //  render_image watches for this marker to save the JPEG image.
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
   
  //  Init camera for colour capture at 320x420 resolution.  Only colour not grayscale supported on Grove Serial Camera.
  if( !camera.initial( CameraC328R::CT_JPEG, CameraC328R::PR_160x120, 
    CameraC328R::JR_160x128 )) { Serial.println( "Initial failed." ); return false; }
    
  //  Tell camera to send images in packets of 64 bytes.
  if( !camera.setPackageSize( PAGE_SIZE )) { Serial.println( "Package size failed." ); return false; }
  
  //  Set the camera to 50 Hz instead of 60 Hz to reduce flicker.  Not sure if this is actually supported on Grove Serial Camera.
  if( !camera.setLightFrequency( CameraC328R::FT_50Hz )) { Serial.println( "Light frequency failed." ); return false; }
  
  //  Take a snaphot and keep in camera memory. Uncompressed mode not supported on Grove Serial Camera.
  if( !camera.snapshot( CameraC328R::ST_COMPRESSED, 0 )) { Serial.println( "Snapshot failed." ); return false; }

  //  Tell render_image we are sending a JPEG.
  Serial.println("[[[ BEGIN JPEG ]]]");
  pictureSizeCount = 0;
  
  //  Read in the JPEG compressed image, packet by packet.  Only JPEG preview picture mode supported on Grove Serial Camnera.
  if( !camera.getJPEGPicture( CameraC328R::PT_JPEG, PROCESS_DELAY, 
    &getJPEGPicture_callback )) { Serial.println( "Get JPEG failed." ); return false; }

  //  Tell render_image we have finished sending a JPEG.
  Serial.println("[[[ END JPEG ]]]");
  Serial.print("pictureSizeCount="); Serial.println(pictureSizeCount);  
  CameraReader::fileSize = pictureSizeCount;

  return true;
}

void processImage(int size) {
#if NOTUSED
    char str[100]; char filename[] = "camera";
    uint8 *pImg; int x,y,bx,by;
        
    //  Decode the JPEG image.
    JpegDec.decode(filename,0);

    //  Show image Information.
    Serial.print("Width     :"); Serial.println(JpegDec.width);
    Serial.print("Height    :"); Serial.println(JpegDec.height);
    Serial.print("Components:"); Serial.println(JpegDec.comps);
    Serial.print("MCU / row :"); Serial.println(JpegDec.MCUSPerRow);
    Serial.print("MCU / col :"); Serial.println(JpegDec.MCUSPerCol);
    Serial.print("Scan type :"); Serial.println(JpegDec.scanType);
    Serial.print("MCU width :"); Serial.println(JpegDec.MCUWidth);
    Serial.print("MCU height:"); Serial.println(JpegDec.MCUHeight); Serial.println("");
    sprintf(str,"#SIZE,%d,%d",JpegDec.width,JpegDec.height); Serial.println(str);
    
    //  Process each MCU.
    while(JpegDec.read()){
        pImg = (uint8 *) JpegDec.pImage ;
        if (pImg == 0) break;

        for(by=0; by<JpegDec.MCUHeight; by++){        
            for(bx=0; bx<JpegDec.MCUWidth; bx++){            
                x = JpegDec.MCUx * JpegDec.MCUWidth + bx;
                y = JpegDec.MCUy * JpegDec.MCUHeight + by;                
                if(x<JpegDec.width && y<JpegDec.height){
                    if(JpegDec.comps == 1){ // Grayscale                    
                        //sprintf(str,"#RGB,%d,%d,%u", x, y, pImg[0]);
                        //Serial.println(str);
                    }else{ // RGB
                        //sprintf(str,"#RGB,%d,%d,%u,%u,%u", x, y, pImg[0], pImg[1], pImg[2]);
                        //Serial.println(str);
                    }
                }
                pImg += JpegDec.comps ;
            }
        }
    }
#endif  //  NOTUSED
}

void loop() {
  //  Capture the image.
  if (!captureImage()) { Serial.println("captureImage failed"); delay(10 * 1000); return; }
  
  //  Process the image.
  processImage(pictureSizeCount); ////
  
  //  Wait for a key press from console or render_image before capturing next image.
  //while(Serial.read() != -1);
  for(;;) {}  //  Stop here.
}

