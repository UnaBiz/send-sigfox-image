//  File SerialCamera_DemoCode_CJ-OV528.ino
//  8/8/2013 Jack Shao
//  Demo code for using seeeduino or Arduino board to cature jpg format
//  picture from seeed serial camera and save it into sd card. Push the
//  button to take the a picture .

//  For more details about the product please check http://www.seeedstudio.com/depot/

////  See docs at:
////  http://www.fut-electronics.com/wp-content/plugins/fe_downloads/Uploads/RSV5-C328%20serial%20camera%20protocol%20&%20user%20manual.pdf
////  http://www.fut-electronics.com/wp-content/plugins/fe_downloads/Uploads/Serial%20Camera%20Module%20Programming%20Instructions%20and%20Tutorial.pdf

#include <arduino.h>
////#include <SD.h>
#include <SoftwareSerial.h>
#include <SPI.h>

#define PIC_PKT_LEN    128        //data length of each read, dont set this too big because ram is limited
#define PIC_FMT_VGA    7  ////  640x480
#define PIC_FMT_CIF    5  ////  320x240
#define PIC_FMT_QCIF   3  ////  160x128
#define PIC_FMT_QQCIF  1  ////  80x64
#define CAM_ADDR       0

#define CAM_SERIAL     softSerial
////#define CAM_SERIAL     Serial

////#define PIC_FMT        PIC_FMT_VGA
#define PIC_FMT        PIC_FMT_QCIF

#define COLOR_SETTING_2BIT_GRAYSCALE 0x01
#define COLOR_SETTING_4BIT_GRAYSCALE 0x02
#define COLOR_SETTING_8BIT_GRAYSCALE 0x03
#define COLOR_SETTING_2BIT_COLOR 0x05
#define COLOR_SETTING_16BIT_COLOR 0x06
#define COLOR_SETTING_JPEG 0x07

////#define COLOR_SETTING COLOR_SETTING_JPEG
#define COLOR_SETTING COLOR_SETTING_8BIT_GRAYSCALE

#define SNAPSHOT_SETTING_COMPRESSED 0  //  Compress the snapshot.
#define SNAPSHOT_SETTING_UNCOMPRESSED 1  //  Don't compress the snapshot.

////#define SNAPSHOT_SETTING SNAPSHOT_SETTING_COMPRESSED
#define SNAPSHOT_SETTING SNAPSHOT_SETTING_UNCOMPRESSED

////File myFile;
SoftwareSerial softSerial(2, 3);  //rx,tx (11-13 is used by sd shield)
////SoftwareSerial softSerial(0, 1); ////  (rx, tx): Seeeduino v4.2 UART Grove connector is connected to D0,D1 for RX,TX

const byte cameraAddr = (CAM_ADDR << 5);  // addr
const int buttonPin = A5;                 // the number of the pushbutton pin
unsigned long picTotalLen = 0;            // picture length
int picNameNum = 0;

/*********************************************************************/
void setup()
{
  Serial.begin(9600);
  CAM_SERIAL.begin(9600);       //cant be faster than 9600, maybe difference with diff board.

#if NOTUSED  ////
  pinMode(buttonPin, INPUT);    // initialize the pushbutton pin as an input
  Serial.println("//Initializing SD card....");
  pinMode(4,OUTPUT);          // CS pin of SD Card Shield
  
  if (!SD.begin(4)) {
    Serial.print("//sd init failed");
    return;
  }
  Serial.println("//sd init done.");
#endif ////  NOTUSED

  initialize();
}
/*********************************************************************/
void loop()
{
  delay(2000);
  Serial.println("//Precapture...");
  preCapture();
  Serial.println("//Capture...");
  Capture();
  Serial.println("//GetData...");
  GetData();
  Serial.println("//Done");
  for (;;) {}  //  Stop here.

#if NOTUSED ////
  int n = 0;
  while(1){
    //Serial.println("\r\nPress the button to take a picture");
    while (digitalRead(buttonPin) == LOW);      //wait for buttonPin status to HIGH
    //Serial.println("taking");
    if(digitalRead(buttonPin) == HIGH){
      delay(20);                               //Debounce
      if (digitalRead(buttonPin) == HIGH)
      {
        delay(200);
        if (n == 0) preCapture();
        Capture();
        //Serial.print("Saving picture...");
        GetData();
      }
      //Serial.print("\r\nDone ,number : ");
      //Serial.println(n);
      n++ ;
      }
    }
#endif ////  NOTUSED    
}
/*********************************************************************/
void clearRxBuf()
{
  while (CAM_SERIAL.available()) 
  {
    CAM_SERIAL.read(); 
  }
}
/*********************************************************************/
void sendCmd(char cmd[], int cmd_len)
{
  for (char i = 0; i < cmd_len; i++) CAM_SERIAL.write(cmd[i]); 
}
/*********************************************************************/
int readBytes(char *dest, int len, unsigned int timeout)
{
  int read_len = 0;
  unsigned long t = millis();
  while (read_len < len)
  {
    while (CAM_SERIAL.available()<1)
    {
      if ((millis() - t) > timeout)
      {
        return read_len;
      }
    }
    *(dest+read_len) = CAM_SERIAL.read();
    ////Serial.write(*(dest+read_len));
    read_len++;
  }
  return read_len;
}
/*********************************************************************/
void initialize()
{   
  char cmd[] = {(char) 0xaa,0x0d|cameraAddr,0x00,0x00,0x00,0x00};  ////  Send SYNC command.
  unsigned char resp[6];

  Serial.print("//Initializing camera...");
  
  while (1) 
  {
    sendCmd(cmd,6);
    if (readBytes((char *)resp, 6,1000) != 6)
    {
      Serial.print(".");
      continue;
    }
    if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x0d && resp[4] == 0 && resp[5] == 0) 
    {
      if (readBytes((char *)resp, 6, 500) != 6) continue; 
      if (resp[0] == 0xaa && resp[1] == (0x0d | cameraAddr) && resp[2] == 0 && resp[3] == 0 && resp[4] == 0 && resp[5] == 0) break; 
    }
  }  
  cmd[1] = 0x0e | cameraAddr;  ////  Send ACK for SYNC.
  cmd[2] = 0x0d;
  delay(1000); 
  sendCmd(cmd, 6);
  Serial.println("\n//Camera initialization done.");
}
/*********************************************************************/
void preCapture()
{
  ////  Send "Initial" command, color setting and resolution.
  char cmd[] = { (char) 0xaa, 0x01 | cameraAddr, 0x00, COLOR_SETTING, 0x00, PIC_FMT };  
  unsigned char resp[6]; 
  
  while (1)
  {
    clearRxBuf();
    delay(1000);
    sendCmd(cmd, 6);
    if (readBytes((char *)resp, 6, 100) != 6) continue; 
    if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x01 && resp[4] == 0 && resp[5] == 0) break; 
  }
}
void Capture()
{
  ////  Send "Set Package Size" command, package length.
  char cmd[] = { (char) 0xaa, 0x06 | cameraAddr, 0x08, PIC_PKT_LEN & 0xff, (PIC_PKT_LEN>>8) & 0xff ,0}; 
  unsigned char resp[6];

  while (1)
  {
    clearRxBuf();
    delay(1000);
    sendCmd(cmd, 6);
    if (readBytes((char *)resp, 6, 100) != 6) continue;
    if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x06 && resp[4] == 0 && resp[5] == 0) break; 
  }
  ////  Send "Snapshot" command.
  cmd[1] = 0x05 | cameraAddr;
  cmd[2] = SNAPSHOT_SETTING;
  cmd[3] = 0;
  cmd[4] = 0;
  cmd[5] = 0; 
  while (1)
  {
    clearRxBuf();
    delay(1000);
    sendCmd(cmd, 6);
    if (readBytes((char *)resp, 6, 100) != 6) continue;
    if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x05 && resp[4] == 0 && resp[5] == 0) break;
  }
  ////  Send "Get Picture" command, snapshot.
  cmd[1] = 0x04 | cameraAddr;
  cmd[2] = 0x1;
  while (1) 
  {
    clearRxBuf();
    delay(1000);
    sendCmd(cmd, 6);
    if (readBytes((char *)resp, 6, 100) != 6) continue;
    if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x04 && resp[4] == 0 && resp[5] == 0)
    {
      if (readBytes((char *)resp, 6, 1000) != 6)
      {
        continue;
      }
      if (resp[0] == 0xaa && resp[1] == (0x0a | cameraAddr) && resp[2] == 0x01)
      {
        picTotalLen = (resp[3]) | (resp[4] << 8) | (resp[5] << 16); 
        Serial.print("//picTotalLen:");
        Serial.println(picTotalLen);
        break;
      }
    }
  }
  
}
/*********************************************************************/
void GetData()
{
  unsigned int pktCnt = (picTotalLen) / (PIC_PKT_LEN - 6); 
  if ((picTotalLen % (PIC_PKT_LEN-6)) != 0) pktCnt += 1;
  
  ////  Send "ACK" command, package ID.
  char cmd[] = { (char) 0xaa, 0x0e | cameraAddr, 0x00, 0x00, 0x00, 0x00 };  
  unsigned char pkt[PIC_PKT_LEN];
  
  char picName[] = "pic00.jpg";
  picName[3] = picNameNum/10 + '0';
  picName[4] = picNameNum%10 + '0';

  #if NOTUSED ////
  if (SD.exists(picName))
  {
    SD.remove(picName);
  }
  
  myFile = SD.open(picName, FILE_WRITE); 
  #endif  //// NOTUSED
  
  ////if(!myFile){
  if (0) { ////
    Serial.println("myFile open fail...");
  }
  else{
    unsigned int i = 0; ////
    for (i = 0; i < pktCnt; i++) ////
    {
      cmd[4] = i & 0xff;
      cmd[5] = (i >> 8) & 0xff;
      
      int retry_cnt = 0;
    retry:
      delay(1000);
      clearRxBuf(); 
      sendCmd(cmd, 6); 
      uint16_t cnt = readBytes((char *)pkt, PIC_PKT_LEN, 200);
      
      unsigned char sum = 0; 
      for (int y = 0; y < cnt - 2; y++)
      {
        sum += pkt[y];
      }
      if (sum != pkt[cnt-2])
      {
        if (++retry_cnt < 100) goto retry;
        else break;
      }
      
      ////myFile.write((const uint8_t *)&pkt[4], cnt-6); 
      //if (cnt != PIC_PKT_LEN) break;

      const byte *data = (const byte *)&pkt[4];
      const int datalen = cnt - 6;
      String bytes = "";
      for (int j = 0; j < datalen; j++)
      {
        if (data[j] <= 0xF) // single char
        {
          bytes.concat("0"); // add a "0" to make sure every byte is read correctly
        }
        bytes.concat(String(data[j], 16));
        bytes.concat(" ");
      }
      Serial.print('"');
      Serial.print(bytes);
      Serial.println("\",");
    }
    Serial.print("//Read "); Serial.print(i); Serial.print(" of "); Serial.println(pktCnt); ////      
    cmd[4] = 0xf0;
    cmd[5] = 0xf0; 
    sendCmd(cmd, 6); 
  }
      
  ////myFile.close();
  picNameNum ++;
}




