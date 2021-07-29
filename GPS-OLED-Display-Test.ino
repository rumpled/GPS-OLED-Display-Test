#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//#define SATFONT           u8g2_font_profont12_tf       // very clean, like Times New Roman
#define SATFONT           u8g2_font_profont12_mf       // don't use transparent font for inverted text...
//#define SATFONT           u8g2_font_6x10_mn            // numbers only
//#define SATFONT         u8g2_font_ncenB08_tr           // nice and bold
//#define SATFONT         u8g2_font_u8glib_4_hr          // 4px font, not really useful here

#define SATLABEL "SAT"
#define SATCOUNTPIXELGAP 4

//#define SPEEDFONT         u8g2_font_logisoso54_tn      // nice but takes too much space for other data
//#define SPEEDFONT         u8g2_font_7Segments_26x42_mn // nice digital clock font but no period (num only)
#define SPEEDFONT         u8g2_font_fur42_tn           // original from Rick, looks great!

// global holders for data
// since in prod they will be updated outside of the display loop
char satCount[3] = "-";
char gpsSpeed[5] = "--.-";

void setup(void) {
  // visual log separator
  Serial.begin(9600);
  Serial.println("==============================");

  // init the display
  u8g2.begin();

  // now that we have the display, let's capture the height of the tiny font for later
  // so we know where to draw the info line
  u8g2.setFont(SATFONT);
  #define SATFONTHEIGHT u8g2.getMaxCharHeight()
  // and how wide the label is so we can offset the number correctly
  #define SATLABELWIDTH u8g2.getStrWidth(SATLABEL)

  // update the display to show dummy values
  updateDisplay();
  // wait 5 sec to show the dummy placeholders
  delay(5000);
}

void loop(void) {
  generateDummyData();
  updateDisplay();
  delay(1000);
}

void generateDummyData() {
  // sat count
  int randSatCount = random(1,19);
  // itoa docs
  // http://www.nongnu.org/avr-libc/user-manual/group__avr__stdlib.html#gaa571de9e773dde59b0550a5ca4bd2f00
  itoa(randSatCount, satCount, 10);
  Serial.print("Sat Count: "); Serial.println(satCount);

  // gps speed
  float randSpeed = random(10,400)/10.0;
  // here's how to shove a float into a char[] with arbitrary precision
  // https://www.hobbytronics.co.uk/arduino-float-vars
  // dtostrf(floatvar, StringLengthIncDecimalPoint, numVarsAfterDecimal, charbuf);
  dtostrf(randSpeed, 4, 1, gpsSpeed);
  Serial.print("      Raw speed: ["); Serial.print(randSpeed); Serial.println("]");
  Serial.print("Formatted speed: ["); Serial.print(gpsSpeed); Serial.println("]");
}

void updateDisplay() {
  // TODO: use updateDisplayArea so that the label doesn't have to be redrawn each time

  // clear the display buffer for new drawing
  u8g2.clearBuffer();
  
  // sat label (inverted colors)
  u8g2.setFont(SATFONT);
  u8g2.setFontMode(0);
  u8g2.setDrawColor(0);
  u8g2.drawStr(0,SATFONTHEIGHT,SATLABEL);
  u8g2.setFontMode(1);
  u8g2.setDrawColor(2);

  // sat count
  u8g2.drawStr(SATLABELWIDTH+SATCOUNTPIXELGAP,SATFONTHEIGHT,satCount);

  // gps speed
  u8g2.setFont(SPEEDFONT);
  
  // calculate right-alignment offset
  int speedAlignRightOffset = u8g2.getDisplayWidth() - u8g2.getStrWidth(gpsSpeed);

  // and draw it
  u8g2.drawStr(speedAlignRightOffset, 64, gpsSpeed);

  // render everything
  u8g2.sendBuffer();
}
