/*
* Oscilloscope
 * Gives a visual rendering of analog pin in realtime.
 *
 * ---------------- IMPROVEMENTS ------------------
 * Updates by John Porter, 2/7/2014
 * Added ability to move waveform left or right.
 * Added gridlines (bounds and minor).
 * Added ability to pause/resume.
 * Added ability to measure time.
 * General usability improvements.
 *
 * --------------- ORIGINAL PROJECT ---------------
 * This project is part of Accrochages
 * See http://accrochages.drone.ws
 * (c) 2008 Sofian Audry (info@sofianaudry.com)
 * ------------------------------------------------
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// * ------------------ HOT KEYS ------------------
final char T_UP       = 'w'; // Translate waveform up
final char T_DOWN     = 's'; //                    down
final char T_LEFT     = 'a'; //                    left
final char T_RIGHT    = 'd'; //                    right
final char Z_IN       = 'c'; // Horizontal zoom in
final char Z_OUT      = 'z'; //                 out
final char S_IN       = 'e'; // Vertical scale in
final char S_OUT      = 'q'; //                out
final char MGL_UP     = 'r'; // Minor grid lines increase
final char MGL_DOWN   = 'f'; //                  decrease
final char TOG_PAUSE  = 'p'; // Toggle pause (unpause resets waveform)
final char RESET_AXIS = ' '; // Reset axis settings
final char MEAS_TIME  = 'x'; // Adds and/or highlights vertical bars (time measurement)
final char BAR_LEFT   = ','; // Move highlighted vertical bar left (can also mouse click)
final char BAR_RIGHT  = '.'; //                               right
// * ----------------------------------------------

// * --------------- STARTING STATE ---------------
float zoom    = 1.0;
float scale   = 1/((float)(2*2*2*2*2*2*2*2));
//float scale   = 0.5;
//float scale   = 0.015625;
//float scale   = 0.03125;
//int centerV   = -167400;
int centerV   = 0;
int centerH   = 0;
int gridLines = 0;
int com_port  = 0;   // Index number in Serial.list
//int com_port  = 33;   // Index number in Serial.list
//int com_port  = 32;   // Index number in Serial.list
// * ----------------------------------------------

// Global vars
import processing.serial.*;
Serial port;                    // Create object from Serial class
int val;                        // Data received from the serial port
long valTime;                   // Time data was received
int[] values;
long[] times;
float voltage;
float measTime = 0;
int   timeMode = 0;
int[] timeBars = {0, 0};
PFont f;
boolean pause;

byte[] inBuffer1 = new byte[1];
//byte[] inBuffer = new byte[16];
byte[] inBuffer = new byte[4];


/*uint8_t aui8_6b[6] = {0,1,2,3,4,5};
uint8_t aui8_7b[7] = {0,1,2,3,4,5,6};
uint8_t aui8_8b[8] = {0,1,2,3,4,5,6,7};
uint8_t aui8_8b_[8] = {1,2,3,4,5,6,7,8};

uint8_t crc8da_(uint8_t *data, uint8_t data_size)
{
//  Serial.println("");   
//  for(int16_t byte_in_data = data_size - 1; byte_in_data >= 0; byte_in_data--) 
//  {
//    print_binary(data[byte_in_data],8);    Serial.print(";");
//  }
//  Serial.println("");   
  for(int16_t bit_in_data = data_size * 8 - 1; bit_in_data >= 7; bit_in_data--) 
//  for(int16_t bit_in_data = data_size * 8 - 1; bit_in_data >= 8; bit_in_data--) 
  {
//    uint16_t bit_in_leftmost_byte_in_data = bit_in_data / 8;
//    uint16_t leftmost_byte_in_data = bit_in_data / 8;
    if(data[bit_in_data / 8] & (1 << (bit_in_data % 8)))
    {
//      if(bit_in_data == 8)
      if(bit_in_data == 7)
      {
        if(data[0]<0x83)
        {
          return data[0];
        }
      }
      data[bit_in_data / 8] = data[bit_in_data / 8] ^ (1 << (bit_in_data % 8));
      data[(bit_in_data - 6) / 8] = data[(bit_in_data - 6) / 8] ^ (1 << ((bit_in_data - 6) % 8));
      data[(bit_in_data - 7) / 8] = data[(bit_in_data - 7) / 8] ^ (1 << ((bit_in_data - 7) % 8));
//      data[(bit_in_data - 8) / 8] = data[(bit_in_data - 8) / 8] ^ (1 << ((bit_in_data - 8) % 8));
    }
//    for(int16_t byte_in_data = data_size - 1; byte_in_data >= 0; byte_in_data--) 
//    {
//      print_binary(data[byte_in_data],8);    Serial.print(";");
//    }
//    Serial.println("");   
  }
  return data[0];
}

uint8_t crc8da(uint8_t *data, uint8_t data_size)
{
//  Serial.println("");   
//  for(int16_t byte_in_data = 0; byte_in_data < data_size; byte_in_data++) 
//  {
//    print_binary(data[byte_in_data],8);    Serial.print(";");
//  }
//  Serial.println("");   
//  data[0] = data[0] ^ 0xff;
//  for(int16_t byte_in_data = 0; byte_in_data < data_size; byte_in_data++) 
//  {
//    print_binary(data[byte_in_data],8);    Serial.print(";");
//  }
//  Serial.println("");   
  for(int16_t bit_in_data = (data_size * 8 - 1); bit_in_data >= (9 - 1); bit_in_data--) 
  {
//    uint16_t bit_in_leftmost_byte_in_data = bit_in_data / 8;
//    uint16_t leftmost_byte_in_data = bit_in_data / 8;
    if(data[((data_size * 8 - 1) - bit_in_data) / 8] & (1 << (bit_in_data % 8)))
    {
      if(bit_in_data == (9 - 1))
      {
        if(data[(data_size - 1)] < 0x07)
        {
          return data[(data_size - 1)];
        }
      }
      data[(((data_size * 8 - 1) - (bit_in_data - 0))) / 8] =
       data[(((data_size * 8 - 1) - (bit_in_data - 0))) / 8] ^ (1 << ((bit_in_data - 0) % 8));
      data[(((data_size * 8 - 1) - (bit_in_data - 6))) / 8] = 
       data[(((data_size * 8 - 1) - (bit_in_data - 6))) / 8] ^ (1 << ((bit_in_data - 6) % 8));
      data[(((data_size * 8 - 1) - (bit_in_data - 7))) / 8] = 
       data[(((data_size * 8 - 1) - (bit_in_data - 7))) / 8] ^ (1 << ((bit_in_data - 7) % 8));
      data[(((data_size * 8 - 1) - (bit_in_data - 8))) / 8] = 
       data[(((data_size * 8 - 1) - (bit_in_data - 8))) / 8] ^ (1 << ((bit_in_data - 8) % 8));
    }
//    for(int16_t byte_in_data = 0; byte_in_data < data_size; byte_in_data++) 
//    {
//      print_binary(data[byte_in_data],8);    Serial.print(";");
//    }
//    Serial.println("");   
  }
  return data[(data_size - 1)];
}

uint8_t crc8da_7(const uint8_t *addr)
{

  aui8_8b_[0]=((addr[0] & 0xf0)) | ((addr[1] & 0xf0) >> 4);
  aui8_8b_[0] = aui8_8b_[0] ^ 0xff;
  aui8_8b_[1]=((addr[1] & 0x0f) << 4) | ((addr[2] & 0xf0) >> 4);
  aui8_8b_[2]=((addr[2] & 0x0f) << 4) | ((addr[3] & 0xf0) >> 4);
  aui8_8b_[3]=((addr[3] & 0x0f) << 4) | ((addr[4] & 0xf0) >> 4);
  aui8_8b_[4]=addr[5];
  aui8_8b_[5]=addr[6];
  aui8_8b_[6]=addr[7];
  aui8_8b_[7]=0x00;
  return crc8da(aui8_8b_,8);
//  return crc8ccitt(aui8_8b_,8);
  

//  aui8_8b[7]=addr[7];
}

uint8_t crc8_01;
uint8_t crc8_23;
uint8_t crc8_45;
uint8_t crc8_67;
*/


// Setup
void setup() {
  size(1280, 480);
  printArray(Serial.list());
  //  port = new Serial(this, Serial.list()[com_port], 9600);    // Com port specified here
    port = new Serial(this, Serial.list()[com_port], 115200);    // Com port specified here
//  port = new Serial(this, Serial.list()[com_port], 921600);    // Com port specified here
  values = new int[width];
  times = new long[width];
  timeBars[0] = width/3;
  timeBars[1] = 2*width/3;
  pause = false;
  smooth();
  f = createFont("Arial", 16, true);
}

// Read value from serial stream
int getValue() {
  int value = -1;
  while (port.available () >= 7) {
    port.readBytes(inBuffer1);
//    print(hex(inBuffer1[0], 2));    
//    print("; ");
    if (inBuffer1[0] == (byte)0xff) {
      port.readBytes(inBuffer1);
//      print(hex(inBuffer1[0], 2));    
//      print(";  ");
      if (inBuffer1[0] == (byte)0xfe) {
        port.readBytes(inBuffer1);
//        print(hex(inBuffer1[0], 2));    
//        print(";   ");
        if (inBuffer1[0] == (byte)0xfd) {
          /*      port.readBytes(inBuffer1);
           byte b00=(byte)inBuffer1[0];
           port.readBytes(inBuffer1);
           byte b01=(byte)inBuffer1[0];
           port.readBytes(inBuffer1);
           byte b02=(byte)inBuffer1[0];
           port.readBytes(inBuffer1);
           byte b03=(byte)inBuffer1[0];*/


          port.readBytes(inBuffer);
          byte b00=(byte)inBuffer[0];
          byte b01=(byte)inBuffer[1];
          byte b02=(byte)inBuffer[2];
          byte b03=(byte)inBuffer[3];
/*          byte b04=(byte)inBuffer[4];
          byte b05=(byte)inBuffer[5];
          byte b06=(byte)inBuffer[6];
          byte b07=(byte)inBuffer[7];
          byte b08=(byte)inBuffer[8];
          byte b09=(byte)inBuffer[9];
          byte b10=(byte)inBuffer[10];
          byte b11=(byte)inBuffer[11];
          byte b12=(byte)inBuffer[12];
          byte b13=(byte)inBuffer[13];
          byte b14=(byte)inBuffer[14];
          byte b15=(byte)inBuffer[15];*/

          value = ((b01) * (1 << 16)) + ((b02 & 0xff) * (1 << 8)) + (b03 & 0xff);
//          value = ((b05) * (1 << 16)) + ((b06 & 0xff) * (1 << 8)) + (b07 & 0xff);
//          value = ((b09) * (1 << 16)) + ((b10 & 0xff) * (1 << 8)) + (b11 & 0xff);
//          value = ((b13) * (1 << 16)) + ((b14 & 0xff) * (1 << 8)) + (b15 & 0xff);

/*          print(binary(b00, 8));    
          print(";");
          print(hex(b01, 2));    
          print(";");
          print(hex(b02, 2));    
          print(";");
          print(hex(b03, 2));    
          print(";");
          println("");*/




/*          int i00=port.read();
           int i01=port.read();
           int i02=port.read();
           int i03=port.read();
           print(binary(i00,8));    print(";");
           print(hex(i01,2));    print(";");
           print(hex(i02,2));    print(";");
           print(hex(i03,2));    print(";");
           println("");*/

          /*     if(
           //    (((b00==B10000000))||((b00==B00000000)))
           (((b00==(byte)0x80))||((b00==(byte)0x00)))
           
           )*/
          {
            //      value = (b01 * (1 << 16));// + (b02 * (1 << 8)) + (b03);
//            value = (b02 & 0xff);// + (b03);

            //      value = ((byte)b03 << 16) | ((byte)b02 << 8) | ((byte)b01);
            //      value = (int)((b01 << 16) | (b02 << 8) | (b03));
            //      value = (int)((b01 << 24) | (b02 << 16) | (b03 << 8));
            //      value = ((byte)b01 << 16) | ((byte)b02 << 8) | ((byte)b03);
            //      value = ((long)b01 << 16) | ((long)b02 << 8) | ((long)b03);


/*                  port.read();
                  value = (port.read() << 16) | (port.read() << 8) | (port.read());*/


            //      value = (i01 << 16) | (i02 << 8) | (i03);
          }
        }
      }
    }
  }
  return value;
}

// Get a y-value for the datapoint, varies based on axis settings
int getY(int val) {
  return (int)(height/2 -(val-512+centerV)*scale / 1023.0f * (height - 1));
}

// Push the values in the data array
void pushValue(int value) {
  for (int i=0; i<width-1; i++)
    values[i] = values[i+1];
  values[width-1] = value;
}

// Push the timestamps in the time array
void pushTime(long time) {
  for (int i=0; i<width-1; i++)
    times[i] = times[i+1];
  times[width-1] = time;
}

// Draw waveform
void drawLines() {
  int x0 = 0, x1 = 0, y0 = 0, y1 = 0;
  stroke(255, 255, 0);
  for (int i=0; i<width; i++) {
    x1 = round(width - ((width-i) * zoom) + centerH);
    y1 = getY(values[i]);
    if (i > 1)
      line(x0, y0, x1, y1);
    x0 = x1;
    y0 = y1;
  }
}

// Draw gridlines (bounds, minor)
void drawGrid() {
  // Get scaled values for bounds
  int pFive = getY(1023);
  int zero  = getY(0);

  // Draw voltage bounds
  stroke(255, 0, 0);
  line(0, pFive-1, width, pFive-1);
  line(0, zero+1, width, zero+1);

  // Add voltage bound text
  textFont(f, 10);
  fill(255, 0, 0);
  text("+5V", 5, pFive+12);
  text(" 0V", 5, zero-4);

  // Draw minor grid lines
  int gridVal = 0;
  stroke(75, 75, 75);
  for (int i = 0; i < gridLines; i++) {
    gridVal = getY(round((i+1.0)*(1023.0 / (gridLines+1.0))));
    line(0, gridVal, width, gridVal);
  }

  // Add minor grid line text
  if (gridLines > 0) {
    textFont(f, 16);
    fill(204, 102, 0);
    float scaleVal = truncate(5.0f / (gridLines+1), 3);
    text("Grid: " + scaleVal + "V", 1170, height-12);
  }

  // Print difference between vertical 'time' bars
  if (timeMode > 0) {
    textFont(f, 16);
    fill(204, 102, 0);

    int idx0 = round(width + (timeBars[0] - width - centerH)/zoom);
    int idx1 = round(width + (timeBars[1] - width - centerH)/zoom);

    // Ensure time bars are over a recorded portion of the waveform
    if (idx1 < 0 || idx0 < 0 || idx1 > (width-1) || idx0 > (width-1) || times[idx1] == 0 || times[idx0] == 0)
      text("Time: N/A", 30, height-12);
    else {
      float timeDiff = truncate((times[idx1] - times[idx0])/2000000.0, 2);
      text("Time: " + timeDiff + "ms", 30, height-12);
    }
  }
}

// Draw vertical 'time bars' (seperate from above for better layering)
void drawVertLines() {
  stroke(75, 75, 75);
  if (timeMode == 1) {
    line(timeBars[1], 0, timeBars[1], height);
    stroke(100, 100, 255);
    line(timeBars[0], 0, timeBars[0], height);
  } else if (timeMode == 2) {
    line(timeBars[0], 0, timeBars[0], height);
    stroke(100, 255, 100);
    line(timeBars[1], 0, timeBars[1], height);
  }
}

// Truncate a floating point number
float truncate(float x, int digits) {
  float temp = pow(10.0, digits);
  return round( x * temp ) / temp;
}

// When a key is pressed down or held...
void keyPressed() {
  switch (key) {
  case T_UP: 
    centerV += 10/scale; 
    break;                     // Move waveform up
  case T_DOWN: 
    centerV -= 10/scale; 
    break;                   // Move waveform down
  case T_RIGHT: 
    centerH += 10/scale; 
    break;                  // Move waveform right
  case T_LEFT: 
    centerH -= 10/scale; 
    break;                   // Move waveform left
  case MGL_UP:                                               // Increase minor grid lines
    if (gridLines < 49)
      gridLines += 1;
    break;
  case MGL_DOWN:                                             // Decrease minor grid lines
    if (gridLines > 0)
      gridLines -= 1;
    break;
  case BAR_LEFT:                                             // Move the time bar left (also mouse click)
    if (timeMode == 1 && timeBars[0] > 0)
      timeBars[0] -= 1;
    else if (timeMode == 2 && timeBars[1] > 0)
      timeBars[1] -= 1; 
    break;
  case BAR_RIGHT:                                            // Move the time bar right (also mouse click)
    if (timeMode == 1 && timeBars[0] < width-1)
      timeBars[0] += 1;
    else if (timeMode == 2 && timeBars[1] < width-1)
      timeBars[1] += 1; 
    break;
  }
}

// When a key is released...
void keyReleased() {
  println(key+": "+(int)key);
  switch (key) {
  case Z_IN:                                                 // Zoom horizontal
    zoom *= 2.0f;
    if ( (int) (width / zoom) <= 1 )
      zoom /= 2.0f;
    break;
  case Z_OUT:                                                // Zoom horizontal
    zoom /= 2.0f;
    if (zoom < 1.0f)
      zoom *= 2.0f;
    break;
  case S_IN: 
    scale*=2; 
    break;                                // Scale vertical
  case S_OUT: 
    scale /= 2; 
    break;                             // Scale vertical
  case RESET_AXIS:                                           // Reset all scaling
    centerV = 0; 
    centerH = 0;
    scale = 0.5; 
    zoom  = 1; 
    gridLines = 0;
    break;
  case MEAS_TIME: 
    timeMode = (timeMode + 1) % 3; 
    break;      // Change the vertical bars (off, left bar, right bar)
  case TOG_PAUSE:                                            // Toggle waveform pausing
    if (pause) {
      centerH = 0;
      for (int i=0; i<width; i++) {
        values[i] = 0;                                       // Clear data on resume
        times[i] = 0;
      }
    }
    pause = !pause;
  }
}

// Use mouse clicks to quickly move vertical bars (if highlighted)
void mousePressed() {
  if (timeMode == 1)
    timeBars[0] = mouseX;
  else if (timeMode == 2)
    timeBars[1] = mouseX;
}

// Primary drawing function
void draw()
{
  background(0);
  drawGrid();
  // Get current voltage, time of reading
  val = getValue();
  valTime = System.nanoTime();

  // If not paused
  if (!pause && val != -1) {
    // Push value/time onto array
    pushValue(val);
    pushTime(valTime);

    // Print current voltage reading
    textFont(f, 16);
    fill(204, 102, 0);
    voltage = truncate(5.0*val / 1023, 1);
    text("Voltage: " + voltage + "V", 1170, 30);
  }
  drawLines();
  drawVertLines();
}