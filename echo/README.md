# echo
Converts the entered characters from uppercase to lowercase and from lowercase to uppercase and sends them back.   
```Hello World-->hELLO wORLD```   

This project has the following patterns:

|Model|Interface|RS485|RTS Signal Inversion|
|:-:|:-:|:-:|:-:|
|SC16IS750|IC2|Disable||
|SC16IS750|SPI|Disable||
|SC16IS750|IC2|Enable|Disable|
|SC16IS750|SPI|Enable|Disable|
|SC16IS750|IC2|Enable|Enable|
|SC16IS750|SPI|Enable|Enable|
|SC16IS752|IC2|Disable||
|SC16IS752|SPI|Disable||
|SC16IS752|IC2|Enable|Disable|
|SC16IS752|SPI|Enable|Disable|
|SC16IS752|IC2|Enable|Enable|
|SC16IS752|SPI|Enable|Enable|

# Configuration for Single channel   
![config-top](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/18a5d123-7313-4c51-aec2-699979c39467)
![config-sc16is750](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/648ac135-2f07-4377-aa1e-152ff784a5bb)

# Wireing for single channel  
Connect RX and other computer TX at any baud rate.   
Connect TX and other computer RX at any baud rate.   
Connect Gnd of ESP32 and Gnd of other computer.   

# Configuration for Dual channel   
![config-top](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/18a5d123-7313-4c51-aec2-699979c39467)
![config-sc16is752](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/392629a2-55fa-4e4d-ae33-a0749ccbd31f)

# Wireing for dual channel  
Connect RX of ChannelA and other computer TX at any baud rate.   
Connect TX of ChannelA and other computer RX at any baud rate.   
Connect RX of ChannelB and other computer TX at any baud rate.   
Connect TX of ChannelB and other computer RX at any baud rate.   
Connect Gnd of ESP32 and Gnd of other computer.   

# Sketch of UART communication using atmega328   
```
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

#define baudrate 9600L

long lastMsg = 0;

void setup() {
  Serial.begin(115200);
  mySerial.begin(baudrate);
}

void loop() {
  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    char buf[64];
    sprintf(buf,"Hello World %ld, Baudrate is %ld", millis(), baudrate);
    mySerial.println(buf);
  }

  if (mySerial.available() > 0) {
    int data = mySerial.read();
    Serial.write(data);
    //Serial.println(data, HEX);
  }  

}
```

# Using RS485   

## Auto RS-485 RTS control   
When bit 4 of the EFCR register is set, the transmitter(=SC16IS75x) controls the state of the RTS pin.   
The transmitter automatically asserts the RTS pin (logic 0) once the host writes data to the transmit FIFO, and de-asserts RTS pin (logic 1) once the last bit of the data has been transmitted.

## RS-485 RTS output inversion   
EFCR bit 5 reverses the polarity of the RTS pin if the UART is in auto RS-485 RTS mode.   
When the transmitter(=SC16IS75x) has data to be sent it de-asserts the RTS pin (logic 1), and when the last bit of the data has been sent out the transmitter asserts the RTS pin (logic 0).

## API   
You can set these using ```EnableRs485``` function.   
This eliminates the need to control the RTS pin.   

## Wireing
RS485-BUS need terminator register.   
__Note__   
According to the data sheet, MAX485 is a single 5V power source, but if the BUS length is short distance, it can be used at 3.3V.   
When the length of BUS is long distance, MAX3485 is preferable.   

```
             VCC ---------------+                                   +--------------- VCC
                                |                                   |
                        +-------x-------+                   +-------x-------+
RXD of SC16IS75X <------| RO            |                   |             RO|-----> RXD of Other side
                        |              B|---+-----------+---|B              |
TXD of SC16IS75X ------>| DI  MAX485    |   >           >   |    MAX485   DI|<----- TXD of Other side
                        |               |   > RS485-BUS >   |               |
RTS of SC16IS75X --+--->| DE            |   >           >   |             DE|---+
                   |    |              A|---+-----------+---|A              |   |
                   +----| /RE           |                   |            /RE|---+-- GPIO of Other side
                        +-------x-------+                   +-------x-------+
                                |                                   |
                               ---                                 ---
```
## Sketch of RS485 communication using atmega328   
GPIO3 is used to control RTS.   
```
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

#define baudrate 9600L
#define RS485_MODE 1
#define TXDEN 3 // Connect to the DE port of the rs485 transceiver

long lastMsg = 0;

void setup() {
  Serial.begin(115200);
  mySerial.begin(baudrate);
#if (RS485_MODE)
  pinMode(TXDEN, OUTPUT);
#endif

}

void loop() {
  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    char buf[64];
    sprintf(buf,"Hello Wold %ld, Baudrate is %ld", millis(), baudrate);
#if (RS485_MODE)
    digitalWrite(TXDEN, HIGH);
#endif
    mySerial.println(buf);
    mySerial.flush();
#if (RS485_MODE)
    digitalWrite(TXDEN, LOW);
#endif
  }

  if (mySerial.available() > 0) {
    int data = mySerial.read();
    Serial.write(data);
    //Serial.println(data, HEX);
  }  

}
```

## Configuration for Single channel   
![config-rs485-1](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/6b389d02-184a-4040-b5cc-ccf56004b557)

## Configuration for Dual channel   
![config-rs485-2](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/8b296ccd-de45-4d42-bde2-5042b2cbd8c1)


# Screen Shot of other side   
![echo-1](https://user-images.githubusercontent.com/6020549/148186633-5778c802-a75c-453a-9974-1e78f87ab1dc.jpg)

