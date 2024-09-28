#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

// Define OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define SoftwareSerial pins for Bluetooth (if using)
SoftwareSerial BTSerial(10, 11); // RX, TX for Bluetooth

void setup() {
  // Initialize serial communication
  BTSerial.begin(9600); // Bluetooth module baud rate
  Serial.begin(9600);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // I2C address: 0x3C
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
}

void loop() {
  if (BTSerial.available()) {
    String incomingData = BTSerial.readStringUntil('\n'); // Read incoming data from phone

    // Clear the display
    display.clearDisplay();

    // Display the incoming data on the OLED
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);

    // Split the incoming data based on the delimiter '|'
    String type = incomingData.substring(0, incomingData.indexOf('|'));
    String content = incomingData.substring(incomingData.indexOf('|') + 1);

    if (type == "CALL") {
      display.println("Incoming Call:");
      display.println(content); // Caller Name
    } else if (type == "TIME") {
      display.println("Current Time:");
      display.println(content); // Time
    } else if (type == "DATE") {
      display.println("Current Date:");
      display.println(content); // Date
    } else if (type == "WEATHER") {
      display.println("Weather Info:");
      display.println(content); // Weather details
    } else {
      display.println("Unknown Data");
    }

    // Update the display with the new content
    display.display();

    // Add a small delay to avoid screen flickering
    delay(500);
  }
}
