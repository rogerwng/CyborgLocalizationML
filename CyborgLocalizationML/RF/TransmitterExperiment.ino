// NRF 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// IMU Parameters
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <cmath>
const int GY_955=0x29;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29, &Wire);

// Transmitting package (outgoing) definition
typedef struct packageTx {
  signed short int data[12] = {0,0,0,0,0,0,0,0,0,0,0,0}; // in form {x,y,z}
} packageTx;
packageTx dataTX;

int DATA_SAMPLE_RATE = 10; // MS
byte addresses[][6] = {"00001", "00002"};

RF24 radio(6,7);

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = DATA_SAMPLE_RATE;

void setup() {
  Serial.begin(115200);
  bno.begin();

  radio.begin();
  radio.setChannel(108);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(addresses[1]);

  delay(1000);
}

void loop() {
  currentMillis = millis();
  if (currentMillis - prevMillis >= txIntervalMillis) {
    send();
    prevMillis = millis();
  }
}

// Sending packages function
void send() {
  imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  imu::Vector<3> mag = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  dataTX.data[0] = (signed short int)(round(acc.x()*1000));
  dataTX.data[1] = (signed short int)(round(acc.y()*1000));
  dataTX.data[2] = (signed short int)(round(acc.z()*1000));
  dataTX.data[3] = (signed short int)(round(mag.x()*1000));
  dataTX.data[4] = (signed short int)(round(mag.y()*1000));
  dataTX.data[5] = (signed short int)(round(mag.z()*1000));
  dataTX.data[6] = (signed short int)(round(gyro.x()*1000));
  dataTX.data[7] = (signed short int)(round(gyro.y()*1000));
  dataTX.data[8] = (signed short int)(round(gyro.z()*1000));
  dataTX.data[9] = (signed short int)(round(euler.x()));
  dataTX.data[10] = (signed short int)(round(euler.y()));
  dataTX.data[11] = (signed short int)(round(euler.z()));
  radio.write(&dataTX, sizeof(dataTX));
}
