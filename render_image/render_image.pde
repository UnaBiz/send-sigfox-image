//  Sketch for Processing IDE to read serial output from send_sigfox_image and render image.
import processing.serial.*;

Serial myPort;
String filename = "photo.jpg"; 
byte[] photo = {};
String line = "";
Boolean readData = false;

void setup()
{
  println(Serial.list());
  int i = 0;  //i++; ////
  myPort = new Serial( this, Serial.list()[i], 9600 );
}

void processLine(String line)
{
  print(line);
  if (line.indexOf("[[[") < 0) return;

  if (line.indexOf("BEGIN JPEG") >= 0)
  {
    photo = new byte[0];
    readData = true;
  }
  else if (line.indexOf("END JPEG") >= 0)
  {
    saveBytes( filename, photo ); 
    readData = false;
  }
  else if( readData )
  {          
    //  line contains [[[ 2F 51 49 49 05 CF FF ... D9 ]]]
    //  Add each byte to the photo.
    String[] lineSplit = line.split(" ");
    for (String hex: lineSplit)
    {
      if (hex == "") continue;
      if (hex.indexOf("[[[") >= 0 || hex.indexOf("]]]") >= 0) continue;
      byte b = (byte) unhex(hex);
      photo = append( photo, b );
    }
  }  
}

void draw()
{
  byte[] buffer = new byte[256]; 
  while( myPort.available() > 0 )
  {
    int readBytes = myPort.readBytes( buffer ); 
    //print( "Read " ); print( readBytes ); println( " bytes ..." );
    for( int i = 0; i < readBytes; i++ )
    {
      byte b = buffer[i];
      line = line + char(b);
      if (b == 10) 
      {
        processLine(line);
        line = "";
      }
    }
  }
}

void keyPressed()
{
  if( photo.length > 0 ) { 
    readData = false;
    print( "Writing to disk " ); 
    print( photo.length );
    println( " bytes ..." ); 
    saveBytes( filename, photo ); 
    println( "DONE!" );
  }
  else {
    readData = true; 
    myPort.clear();
    println( "Waiting for data ..." );
    myPort.write("a");////
  }
}