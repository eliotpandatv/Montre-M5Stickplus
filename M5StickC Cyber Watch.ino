#include <M5StickC.h>
#include <EEPROM.h>

float gyroSensitivity = 1.2;
int timeFormat = 24;
bool buzzerEnabled = false;

uint16_t BG = BLACK;
uint16_t FG = GREEN;

float gestureThreshold = 40.0;
bool screenOn = false;

int menuIndex = 0;
bool inMenu = false;

#define EEPROM_SIZE 32

void drawWatch() {
  M5.Lcd.fillScreen(BG);

  RTC_TimeTypeDef time;
  M5.Rtc.GetTime(&time);

  int h = time.Hours;
  int m = time.Minutes;
  String suffix = "";

  if (timeFormat == 12) {
    suffix = (h >= 12) ? " PM" : " AM";
    h = h % 12;
    if (h == 0) h = 12;
  }

  char buf[16];
  sprintf(buf, "%02d:%02d", h, m);

  M5.Lcd.setTextColor(FG, BG);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(10, 20);
  M5.Lcd.print(buf);
  M5.Lcd.print(suffix);

  float bat = M5.Axp.GetBatVoltage();
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(5, 70);
  M5.Lcd.printf("BAT %.2fV", bat);
}

void drawMenu() {
  M5.Lcd.fillScreen(BG);
  M5.Lcd.setTextColor(FG, BG);
  M5.Lcd.setTextSize(1);

  M5.Lcd.setCursor(5, 10);
  M5.Lcd.println(menuIndex == 0 ? "> Sensibilite" : "  Sensibilite");

  M5.Lcd.setCursor(5, 25);
  M5.Lcd.println(menuIndex == 1 ? "> Format heure" : "  Format heure");

  M5.Lcd.setCursor(5, 40);
  M5.Lcd.println(menuIndex == 2 ? "> Sauvegarder" : "  Sauvegarder");
}

void saveSettings() {
  EEPROM.put(0, gyroSensitivity);
  EEPROM.put(8, timeFormat);
  EEPROM.commit();
}

void loadSettings() {
  EEPROM.get(0, gyroSensitivity);
  EEPROM.get(8, timeFormat);
  if (gyroSensitivity <= 0 || gyroSensitivity > 5) gyroSensitivity = 1.2;
  if (timeFormat != 12 && timeFormat != 24) timeFormat = 24;
}

void setup() {
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.setRotation(1);
  M5.Axp.ScreenBreath(8);

  EEPROM.begin(EEPROM_SIZE);
  loadSettings();

  Serial.begin(115200);
}

void loop() {
  M5.update();

  if (Serial.available()) {
    String cmd = Serial.readStringUntil('
');
    cmd.trim();

    if (cmd.startsWith("sens=")) {
      gyroSensitivity = cmd.substring(5).toFloat();
    }
    if (cmd == "12h") timeFormat = 12;
    if (cmd == "24h") timeFormat = 24;
  }

  float ax, ay, az;
  M5.IMU.getAccelData(&ax, &ay, &az);

  if (abs(ax) * 100 > gestureThreshold * gyroSensitivity && !screenOn) {
    screenOn = true;
    drawWatch();
  }

  if (M5.BtnA.wasPressed()) {
    inMenu = !inMenu;
    if (inMenu) drawMenu();
    else drawWatch();
  }

  if (inMenu && M5.BtnB.wasPressed()) {
    menuIndex = (menuIndex + 1) % 3;
    drawMenu();
  }

  if (inMenu && M5.BtnA.pressedFor(800)) {
    if (menuIndex == 0) gyroSensitivity += 0.1;
    if (menuIndex == 1) timeFormat = (timeFormat == 24) ? 12 : 24;
    if (menuIndex == 2) saveSettings();
    drawMenu();
  }

  delay(50);
}
