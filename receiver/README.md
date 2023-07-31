# receiver
Receive data from UART.   
There is no transmission.   

This project has the following patterns:

|Model|Interface|EOL|
|:-:|:-:|:-:|
|SC16IS750|IC2|(*1)|
|SC16IS750|IC2|(*2)|
|SC16IS750|SPI|(*1)|
|SC16IS750|SPI|(*2)|
|SC16IS752|IC2|(*1)|
|SC16IS752|IC2|(*2)|
|SC16IS752|SPI|(*1)|
|SC16IS752|SPI|(*2)|


(*1)
Input is completed with the terminating character.   
Terminating character is LF.   
You can change this using menuconfig.   

(*2)
Input is completed with the timeout.   
Timeout is 500 mill sec.   
You can change this using menuconfig.   

# Configuration   
![config-top](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/b1a0a8b2-fb63-4247-b648-60f403fbfcfe)
![config-receiver-character](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/b5b2f3f1-bccb-49c2-ad78-a4dc69b5e05e)
![config-receiver-timeout](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/c6b8111e-fd7f-47bf-a8ac-567e33fa6853)

# Wireing for SC16IS750  
Connect RX and other computer TX at any baud rate.   
Connect Gnd of ESP32 and Gnd of other computer.   

# Wireing for SC16IS752  
Connect RX of ChannelA and other computer TX at any baud rate.   
Connect RX of ChannelB and other computer TX at any baud rate.   
Connect Gnd of ESP32 and Gnd of other computer.   

# Sketch of the other side   
I used UNO.   
```
#define baudrate 115200L

void setup() {
  Serial.begin(baudrate);
}

void loop() {
  char buf[64];
  sprintf(buf,"Hello Wold %ld, Baudrate is %ld", millis(), baudrate);
  Serial.println(buf);
  delay(1000);
}
```

