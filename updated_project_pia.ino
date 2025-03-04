#include <BluetoothSerial.h>


const int ledPinPWM1 = 18;        
const int ledPinPWM2 = 19;        
const int ledPinDigital = 23;     
const int ledPinDigital2 = 21;    

BluetoothSerial SerialBT;         // Bluetooth Serial object

//PWM LED dimming (Fade in and out)
void handlePWM1() {
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    analogWrite(ledPinPWM1, dutyCycle);
    delay(15); 
  }

  // Fade LED out
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    analogWrite(ledPinPWM1, dutyCycle);
    delay(15); 
  }
}

//  Set brightness of PWM LED 2
void setPWM2Brightness(int brightness) {
  if (brightness >= 0 && brightness <= 255) {
    analogWrite(ledPinPWM2, brightness);
  }
}

// Blink Digital LED 2
void blinkDigitalLED2() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPinDigital2, HIGH);
    delay(500); // Blink interval
    digitalWrite(ledPinDigital2, LOW);
    delay(500); // Blink interval
  }
}

void setup() {
  Serial.begin(115200);           
  SerialBT.begin("echipa_05");    

  // Set LED pins as OUTPUT
  pinMode(ledPinPWM1, OUTPUT);
  pinMode(ledPinPWM2, OUTPUT);
  pinMode(ledPinDigital, OUTPUT);
  pinMode(ledPinDigital2, OUTPUT);

  analogWrite(ledPinPWM2, 0);     // Ensure PWM LED 2 is off initially
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read(); 
    int brightness = -1; 

    switch (command) {
      case '1': //PWM fade in and out LED 1
        handlePWM1();
        break;

      case '0': // Turn off PWM LED 1
        analogWrite(ledPinPWM1, 0);
        break;

      case 'A': // Turn on Digital LED 1
        digitalWrite(ledPinDigital, HIGH);
        break;

      case 'B': // Turn off Digital LED 1
        digitalWrite(ledPinDigital, LOW);
        break;

      case 'C': // Set brightness of PWM LED 2
        brightness = SerialBT.parseInt();
        setPWM2Brightness(brightness);
        break;

      case 'D': // Blink Digital LED 2
        blinkDigitalLED2();
        break;

      default:
        break;
    }
  }
}
