/**
 *
 * kaboom library for Arduino
 * URL...
 *
 * MIT License
 * (c) 2023 Aunders Hallsten
 *
**/
#include <Arduino.h>
#include "HX711.h"

kaboom::kaboom() {
}

kaboom::~kaboom() {
}

bool kaboom::Touch_getXY(void)
{
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT); // restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH); // because TFT control pins
  digitalWrite(XM, HIGH);
  bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
  if (pressed)
  {
    pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
    pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
  }
  return pressed;
}

void kaboom::buttonInitialization() // create buttons with location, color, text, and text size
{
  one_btn.initButton(&tft, 60, 120, 80, 80, YELLOW, MAGENTA, CYAN, "1", 3);
  two_btn.initButton(&tft, 160, 120, 80, 80, YELLOW, MAGENTA, CYAN, "2", 3);
  three_btn.initButton(&tft, 260, 120, 80, 80, YELLOW, MAGENTA, CYAN, "3", 3);
  four_btn.initButton(&tft, 60, 220, 80, 80, YELLOW, MAGENTA, CYAN, "4", 3);
  five_btn.initButton(&tft, 160, 220, 80, 80, YELLOW, MAGENTA, CYAN, "5", 3);
  six_btn.initButton(&tft, 260, 220, 80, 80, YELLOW, MAGENTA, CYAN, "6", 3);
  seven_btn.initButton(&tft, 60, 320, 80, 80, YELLOW, MAGENTA, CYAN, "7", 3);
  eight_btn.initButton(&tft, 160, 320, 80, 80, YELLOW, MAGENTA, CYAN, "8", 3);
  nine_btn.initButton(&tft, 260, 320, 80, 80, YELLOW, MAGENTA, CYAN, "9", 3);
  zero_btn.initButton(&tft, 160, 420, 80, 80, YELLOW, MAGENTA, CYAN, "0", 3);
  back_btn.initButton(&tft, 60, 420, 80, 80, YELLOW, MAGENTA, CYAN, "<-", 3);
  fwd_btn.initButton(&tft, 260, 420, 80, 80, YELLOW, MAGENTA, CYAN, "->", 3);
}

void kaboom::drawNumberButtons()
{
  one_btn.drawButton(false);
  two_btn.drawButton(false);
  three_btn.drawButton(false);
  four_btn.drawButton(false);
  five_btn.drawButton(false);
  six_btn.drawButton(false);
  seven_btn.drawButton(false);
  eight_btn.drawButton(false);
  nine_btn.drawButton(false);
  zero_btn.drawButton(false);
  back_btn.drawButton(false);
  fwd_btn.drawButton(false);
}

void kaboom::tftSetup()
{
  uint16_t ID = tft.readID();
  // Serial.print("TFT ID = 0x");  // show tft ID via serial port
  // Serial.println(ID, HEX);
  // Serial.println("Calibrate for your Touch Panel");
  if (ID == 0xD3D3)
    ID = 0x9486; // write-only shield
  tft.begin(ID);
  tft.setRotation(0); // PORTRAIT
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(3);
  tft.setCursor(260, y0);
  sprintf(buf, "%-10s", "gns");
  tft.print(buf);
}

void kaboom::buttonChecks() // Check buttons if any has been pressed
{
  // while(1) // loop until fwd button is pressed
  // {
  bool down = Touch_getXY();
  one_btn.press(down && one_btn.contains(pixel_x, pixel_y));
  two_btn.press(down && two_btn.contains(pixel_x, pixel_y));
  three_btn.press(down && three_btn.contains(pixel_x, pixel_y));
  four_btn.press(down && four_btn.contains(pixel_x, pixel_y));
  five_btn.press(down && five_btn.contains(pixel_x, pixel_y));
  six_btn.press(down && six_btn.contains(pixel_x, pixel_y));
  seven_btn.press(down && seven_btn.contains(pixel_x, pixel_y));
  eight_btn.press(down && eight_btn.contains(pixel_x, pixel_y));
  nine_btn.press(down && nine_btn.contains(pixel_x, pixel_y));
  zero_btn.press(down && zero_btn.contains(pixel_x, pixel_y));
  back_btn.press(down && back_btn.contains(pixel_x, pixel_y));
  fwd_btn.press(down && fwd_btn.contains(pixel_x, pixel_y));

  if (one_btn.justReleased())
    one_btn.drawButton();
  if (two_btn.justReleased())
    two_btn.drawButton();
  if (three_btn.justReleased())
    three_btn.drawButton();
  if (four_btn.justReleased())
    four_btn.drawButton();
  if (five_btn.justReleased())
    five_btn.drawButton();
  if (six_btn.justReleased())
    six_btn.drawButton();
  if (seven_btn.justReleased())
    seven_btn.drawButton();
  if (eight_btn.justReleased())
    eight_btn.drawButton();
  if (nine_btn.justReleased())
    nine_btn.drawButton();
  if (zero_btn.justReleased())
    zero_btn.drawButton();
  if (back_btn.justReleased())
    back_btn.drawButton();
  if (fwd_btn.justReleased())
    fwd_btn.drawButton();

  if (one_btn.justPressed())
  {
    one_btn.drawButton(true);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    sprintf(buf, "%10d", 1);
    tft.setCursor(x0, y0);
    tft.print(buf);
  }
  if (two_btn.justPressed())
  {
    two_btn.drawButton(true);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    sprintf(buf, "%10d", 2);
    tft.setCursor(x0, y0);
    tft.print(buf);
  }
  if (three_btn.justPressed())
  {
    three_btn.drawButton(true);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    sprintf(buf, "%10d", 3);
    tft.setCursor(x0, y0);
    tft.print(buf);
  }
  if (four_btn.justPressed())
  {
    four_btn.drawButton(true);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    sprintf(buf, "%10d", 4);
    tft.setCursor(x0, y0);
    tft.print(buf);
  }
  if (five_btn.justPressed())
  {
    five_btn.drawButton(true);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    sprintf(buf, "%10d", 5);
    tft.setCursor(x0, y0);
    tft.print(buf);
  }
  if (six_btn.justPressed())
  {
    six_btn.drawButton(true);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    sprintf(buf, "%10d", 6);
    tft.setCursor(x0, y0);
    tft.print(buf);
  }
  if (seven_btn.justPressed())
  {
    seven_btn.drawButton(true);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    sprintf(buf, "%10d", 7);
    tft.setCursor(x0, y0);
    tft.print(buf);
  }
  if (eight_btn.justPressed())
  {
    eight_btn.drawButton(true);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    sprintf(buf, "%10d", 8);
    tft.setCursor(x0, y0);
    tft.print(buf);
  }
  if (nine_btn.justPressed())
  {
    nine_btn.drawButton(true);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    sprintf(buf, "%10d", 9);
    tft.setCursor(x0, y0);
    tft.print(buf);
  }
  if (zero_btn.justPressed())
  {
    zero_btn.drawButton(true);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    sprintf(buf, "%10d", 0);
    tft.setCursor(x0, y0);
    tft.print(buf);
  }
  if (back_btn.justPressed())
  {
    back_btn.drawButton(true);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    sprintf(buf, "%10s", "backspace");
    tft.setCursor(x0, y0);
    tft.print(buf);
  }
  if (fwd_btn.justPressed())
  {
    fwd_btn.drawButton(true);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    sprintf(buf, "%10s", "forward");
    tft.setCursor(x0, y0);
    tft.print(buf);
    //break;
  }
  //}
}

byte kaboom::read_line(char *buffer, byte buffer_length) // a way to read incoming data from serial port
{
  memset(buffer, 0, buffer_length); // Clear buffer

  byte read_length = 0;
  while (read_length < buffer_length - 1)
  {
    while (!Serial.available())
      ;
    byte c = Serial.read();

    if (c == 0x08 || c == 0x7f)
    { // Backspace characters
      if (read_length < 1)
        continue;

      --read_length;
      buffer[read_length] = '\0'; // Put a terminator on the string in case we are finished

      Serial.print((char)0x08); // Move back one space
      Serial.print(F(" "));     // Put a blank there to erase the letter from the terminal
      Serial.print((char)0x08); // Move back again

      continue;
    }

    Serial.print((char)c); // Echo the user's input

    if (c == '\r')
    {
      Serial.println();
      buffer[read_length] = '\0';
      break;
    }
    else if (c == '\n')
    {
    }
    else
    {
      buffer[read_length] = c;
      ++read_length;
    }
  }

  return read_length;
}

void kaboom::displayMenu() // call to tell user how to navigate the UI
{
  Serial.println();
  Serial.println(F("Main Menu:"));
  Serial.println(F("1) Convey Kaboom"));
  Serial.println(F("2) Tare Scale"));
  Serial.println(F("3) Calibrate Scale"));
  Serial.println(F("4) Read Scale Continuously"));
  Serial.println(F("5) Reserved"));
  Serial.println(F("x) Exit"));
}

void kaboom::readScale()
{
  while (!Serial.available())
  {
    Serial.println(scale.read_average(read_avg));
  }
  Serial.println("quiting scale reading...");
  displayMenu();
}

void kaboom::scaleInitialize()
{
  Serial.println("Initializing Scale on pins:");
  Serial.print("SDA: ");
  Serial.println(LOADCELL_DOUT_PIN);
  Serial.print("CLK: ");
  Serial.println(LOADCELL_SCK_PIN);

  // if (scale.wait_ready_retry(init_retries, delay_ms))
  // {
  //   long reading = scale.read();
  //   Serial.print("HX711 initial reading: ");
  //   Serial.println(reading);
  // }
  // else
  // {
  //   Serial.println("HX711 not found.");
  // }

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  // while (amplitude >= threshold) // test and keep testing until scale is settled and ready for tare.
  // {
  //   int old_scale_reading = 0;
  //   int new_scale_reading = scale.read();
  //   int amplitude = new_scale_reading - old_scale_reading;

  //   scale_init_count++;
  //   if (scale_init_count >= scale_init_count_threshold)
  //   {
  //     Serial.print("scale not settling count:");
  //     Serial.println(scale_init_count);
  //     break;
  //   }
  // }
}

void kaboom::tareScale()
{
  Serial.print(F("\n\rGetting Tare point: "));
  scale.tare();                                // Reset the scale to 0
  setting_tare_point = scale.read_average(10); // Get 10 readings from the HX711 and average them
  Serial.println(setting_tare_point);

  Serial.println("tareing scale...");
  if (scale.wait_ready_retry(10))
  {
    scale.tare(); // reset the scale to 0

    Serial.print("raw reading: \t\t");
    Serial.println(scale.read()); // print a raw reading from the ADC

    Serial.print("Average Reading: \t\t");
    Serial.println(scale.read_average(read_avg)); // print the average of 20 readings from the ADC

    Serial.print("get value: \t\t");
    Serial.println(scale.get_value(5)); // print the average of 5 readings from the ADC minus the tare weight, set with tare()

    Serial.print("get units: \t\t");
    Serial.println(scale.get_units(5), 1); // print the average of 5 readings from the ADC minus tare weight, divided
    Serial.println("done tareing");
    displayMenu();
  }
  else
  {
    Serial.println("HX711 not found.");
  }
}

void kaboom::calibrateScale()
{
  Serial.println("Put the 50g weight on the scale and enter serial");
  Serial.println("calibrating...");
  while (!Serial.available())
  {
    scale.set_scale(50.f);
  }
  Serial.println("done calibrating, offset: ");
  Serial.println(scale.get_offset());
  Serial.println("units:");
  Serial.println(scale.get_units());
}

void kaboom::calibrate_scale(void)
{
  Serial.println();
  Serial.println();
  Serial.println(F("Scale calibration"));
  Serial.println(F("Place known weight on scale. Press a key when weight is in place and stable."));

  while (Serial.available() == false)
    ; // Wait for user to press key

  Serial.print(F("Tare: "));
  Serial.println(setting_tare_point);

  long rawReading = scale.read_average(setting_average_amount); // Take average reading over a given number of times
  Serial.print(F("Raw: "));
  Serial.println(rawReading);

  Serial.print(F("Current Reading: "));
  Serial.print(scale.get_units(setting_average_amount), 4); // Show 4 decimals during calibration
  if (setting_units == UNITS_G)
    Serial.print(F("lbs"));
  if (setting_units == UNITS_GN)
    Serial.print(F("kg"));
  Serial.println();

  Serial.print(F("Calibration Factor: "));
  Serial.print(setting_calibration_factor);
  Serial.println();

  while (Serial.available())
    Serial.read(); // Clear anything in RX buffer

  Serial.print(F("Please enter the weight currently sitting on the scale: "));

  // Read user input
  char newSetting[15]; // Max 15 characters: "12.5765" = 8 characters (includes trailing /0)
  read_line(newSetting, sizeof(newSetting));

  float weightOnScale = atof(newSetting); // Convert this string to a float
  Serial.println();

  Serial.print(F("User entered: "));
  Serial.println(weightOnScale, 4);

  // Convert this weight to a calibration factor

  // tare: 210193
  // raw: 246177
  // User Input: 0.5276 kg
  // avg: 4 times

  // get_units = (raw-OFFSET) / calibration_factor
  // 0.5276 = (246177-210193) / cal_factor
  // 114185 / .45 = 256744

  setting_calibration_factor = (rawReading - setting_tare_point) / weightOnScale;

  Serial.print(F("New Calibration Factor: "));
  Serial.print(setting_calibration_factor);
  Serial.println();

  scale.set_scale(setting_calibration_factor); // Go to this new cal factor

  // Record this new value to EEPROM
  // record_system_settings();

  Serial.print(F("New Scale Reading: "));
  Serial.print(scale.get_units(setting_average_amount), 4); // Show 4 decimals during calibration
  Serial.print(F(" "));
  if (setting_units == UNITS_G)
    Serial.print(F("lbs"));
  if (setting_units == UNITS_GN)
    Serial.print(F("kg"));
  Serial.println();
}

void kaboom::stepperInitialize()
{
  stepper.setMaxSpeed(max_speed);
  stepper.setSpeed(speed);
  stepper.setAcceleration(accel);
}

void kaboom::conveyKaboom()
{

  while (powder_current <= powder_to_deliver)
  {
    if (Serial.available())
    {
      // Read command
      inString = Serial.read();
      Serial.print("recieved: ");
      Serial.println(inString);
      Serial.print("exiting kaboom conveyance");
    }
    step = 1;
    stepper.move(step);
    stepper.run();
    powder_current = scale.read();
  }
}
