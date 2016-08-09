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
float scale   = 0.5;
int centerV   = 0;
int centerH   = 0;
int gridLines = 0;
int com_port  = 0;   // Index number in Serial.list
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

// Setup
void setup() {
  size(1280, 480);
  port = new Serial(this, Serial.list()[com_port], 9600);    // Com port specified here
//  port = new Serial(this, Serial.list()[com_port], 115200);    // Com port specified here
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
  while (port.available () >= 3) {
    if (port.read() == 0xff) {
      value = (port.read() << 8) | (port.read());
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
  stroke(255,255,0);
  for (int i=0; i<width; i++) {
    x1 = round(width - ((width-i) * zoom) + centerH);
    y1 = getY(values[i]);
    if(i > 1)
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
    if(idx1 < 0 || idx0 < 0 || idx1 > (width-1) || idx0 > (width-1) || times[idx1] == 0 || times[idx0] == 0)
      text("Time: N/A", 30, height-12);
    else{
      float timeDiff = truncate((times[idx1] - times[idx0])/2000000.0,2);
      text("Time: " + timeDiff + "ms", 30, height-12);
    }
  }
}

// Draw vertical 'time bars' (seperate from above for better layering)
void drawVertLines(){
  stroke(75, 75, 75);
  if (timeMode == 1) {
    line(timeBars[1], 0, timeBars[1], height);
    stroke(100, 100, 255);
    line(timeBars[0], 0, timeBars[0], height);
  }
  else if (timeMode == 2) {
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
  case T_UP: centerV += 10/scale; break;                     // Move waveform up
  case T_DOWN: centerV -= 10/scale; break;                   // Move waveform down
  case T_RIGHT: centerH += 10/scale; break;                  // Move waveform right
  case T_LEFT: centerH -= 10/scale; break;                   // Move waveform left
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
  case S_IN: scale*=2; break;                                // Scale vertical
  case S_OUT: scale /= 2; break;                             // Scale vertical
  case RESET_AXIS:                                           // Reset all scaling
    centerV = 0; centerH = 0;
    scale = 0.5; zoom  = 1; gridLines = 0;
    break;
  case MEAS_TIME: timeMode = (timeMode + 1) % 3; break;      // Change the vertical bars (off, left bar, right bar)
  case TOG_PAUSE:                                            // Toggle waveform pausing
    if (pause) {
      centerH = 0;
      for (int i=0; i<width; i++){
        values[i] = 0;                                       // Clear data on resume
        times[i] = 0;
      }
    }
    pause = !pause;
  }
}

// Use mouse clicks to quickly move vertical bars (if highlighted)
void mousePressed() {
  if(timeMode == 1)
    timeBars[0] = mouseX;
  else if(timeMode == 2)
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