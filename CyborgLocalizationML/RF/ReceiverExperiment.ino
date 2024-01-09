// NRF 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

byte addresses[][6] = {"00001", "00002"};

RF24 radio(6,7);

// Receiving package (incoming) definition
typedef struct packageRx {
  signed short int data[12] = {0,0,0,0,0,0,0,0,0,0,0,0}; // in form {x,y,z}
} packageRx;
packageRx dataRX;

void setup() {
  Serial.begin(115200);  // begin transmission to serial monitor, baudrate = 115200

  //NRF setup
  radio.begin();
  radio.setChannel(108);                   // RF (radio frequency channel)
  radio.setPALevel(RF24_PA_LOW);           // Power Amplifier level
  radio.setDataRate(RF24_250KBPS);         // set transmission data rate
  radio.openReadingPipe(1, addresses[1]);     //Setting the address at which we will send the data
  radio.startListening();
  pinMode(3, OUTPUT);                        // Set pin 3 to output
}

void loop() {
  getData();

}

// Receiving data function
void getData() {
  if (radio.available()) {
    radio.read(&dataRX, sizeof(dataRX));

    for (int i = 0; i<9; i++) {
      double num = (double)(dataRX.data[i])/1000;
      Serial.print(num);
      Serial.print(",");
    }
    // double num = (double)(dataRX.data[10]);
    Serial.print((double)(dataRX.data[9]));
    Serial.print(",");
    Serial.print((double)(dataRX.data[10]));
    Serial.print(",");
    Serial.println((double)(dataRX.data[11]));
    
  }
}