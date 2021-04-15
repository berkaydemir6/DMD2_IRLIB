#include <DMD2.h>
#include <IRremote.h>
#include <SPI.h>
#include <TimerOne.h>
#include <fonts/Arial_Black_16.h>

int RECV_PIN = 3;
int brightness = 165;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define DISPLAYS_WIDE 2
#define DISPLAYS_HIGH 1

SoftDMD dmd(DISPLAYS_WIDE, DISPLAYS_HIGH);
DMD_TextBox box(dmd, 0, 0, 64, 16); // 32,16 64,16 you can change

#define BUTTON1 16753245

void ArduinoTimerSettings()
{
  irrecv.enableIRIn();
  dmd.scanDisplay();
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  Timer1.initialize(5000);
  Timer1.attachInterrupt(ArduinoTimerSettings);
  dmd.clearScreen();
  dmd.setBrightness(brightness);
  dmd.selectFont(Arial_Black_16);
  dmd.begin();
  dmd.drawString(1, 1, F("Hello"));
}

void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.println(results.value);
    if (results.value == BUTTON1)
    {
      box.clear();
      dmd.drawString(1, 1, F("WORLD"));
    }
    irrecv.resume();
  }
}
