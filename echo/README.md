# echo
Converts the entered characters from uppercase to lowercase and from lowercase to uppercase and sends them back.   
```Hello World-->hELLO wORLD```   

This project has the following patterns:

|# of UART|Interface|RS485|RTS Signal Inversion|
|:-:|:-:|:-:|:-:|
|Single|IC2|Disable||
|Single|SPI|Disable||
|Single|IC2|Enable|Disable|
|Single|SPI|Enable|Disable|
|Single|IC2|Enable|Enable|
|Single|SPI|Enable|Enable|
|Dual|IC2|Disable||
|Dual|SPI|Disable||
|Dual|IC2|Enable|Disable|
|Dual|SPI|Enable|Disable|
|Dual|IC2|Enable|Enable|
|Dual|SPI|Enable|Enable|

# Configuration for Single channel   
![config-top](https://user-images.githubusercontent.com/6020549/148176368-79ed4432-46ab-49b3-a86f-1872e73310d2.jpg)
![config-echo-10](https://user-images.githubusercontent.com/6020549/149246477-b3941ccd-809a-4428-8aac-c57da41a4edf.jpg)

# Wireing for single channel  
Connect RX and other computer TX at any baud rate.   
Connect TX and other computer RX at any baud rate.   
Connect Gnd of ESP32 and Gnd of other computer.   

# Configuration for Dual channel   
![config-top](https://user-images.githubusercontent.com/6020549/148176368-79ed4432-46ab-49b3-a86f-1872e73310d2.jpg)
![config-echo-20](https://user-images.githubusercontent.com/6020549/149246600-ca0a5522-706a-49ae-9356-550a6fb24d88.jpg)

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
![config-echo-11](https://user-images.githubusercontent.com/6020549/149248222-6bbb843e-09c7-4c40-9354-106a0bec81b9.jpg)
![config-echo-12](https://user-images.githubusercontent.com/6020549/149247631-2c33f1ee-036a-40ca-8517-aa567072e3c7.jpg)

## Configuration for Dual channel   
![config-echo-21](https://user-images.githubusercontent.com/6020549/149248227-b7dafd1e-d7b2-45c4-8116-9da894dbefc1.jpg)
![config-echo-22](https://user-images.githubusercontent.com/6020549/149247647-9ff9c291-5763-4be7-ac56-755c927724e7.jpg)


# Screen Shot of other side   
![echo-1](https://user-images.githubusercontent.com/6020549/148186633-5778c802-a75c-453a-9974-1e78f87ab1dc.jpg)

