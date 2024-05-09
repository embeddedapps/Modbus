#include <ModbusMaster.h>
#include <SoftwareSerial.h>

byte TX_PIN = 4, RX_PIN = 5;
byte DE_RE_PIN = 15;

// Define the ModbusMaster object
ModbusMaster node;
SoftwareSerial Soft_Serial(RX_PIN, TX_PIN);

void preTransmission() {
  digitalWrite(DE_RE_PIN, HIGH);
}

void postTransmission() {
  digitalWrite(DE_RE_PIN, LOW);
}

void setup() {
  Serial.begin(115200); // Initialize serial communication 
  Soft_Serial.begin(9600);

  pinMode(DE_RE_PIN, OUTPUT);  // DE/RE Controlling pin of RS-485

  node.begin(1, Soft_Serial); // Initialize Modbus node with slave address 1 and Serial port
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() {
  uint8_t result;
  uint16_t level, pressure, temperature; // Variables to store sensor data
  
  // Read holding register 53 for level
  result = node.readHoldingRegisters(0053, 1);
  if (result == node.ku8MBSuccess) {
    level = node.getResponseBuffer(0); // Store level value
  } else {
    Serial.println("Error reading level register!");
  }
  
  // Read holding register 37 for pressure
  result = node.readHoldingRegisters(0037, 1);
  if (result == node.ku8MBSuccess) {
    pressure = node.getResponseBuffer(0); // Store pressure value
  } else {
    Serial.println("Error reading pressure register!");
  }
  
  // Read holding register 45 for temperature
  result = node.readHoldingRegisters(0045, 1);
  if (result == node.ku8MBSuccess) {
    temperature = node.getResponseBuffer(0); // Store temperature value
  } else {
    Serial.println("Error reading temperature register!");
  }
  
  // Print the values
  Serial.print("Level: ");
  Serial.println(level);
  Serial.print("Pressure: ");
  Serial.println(pressure);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  delay(1000); // Wait for 1 second before next read
}
