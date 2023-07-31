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

# Configuration for SC16IS750  
![config-top](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/b1a0a8b2-fb63-4247-b648-60f403fbfcfe)
![config-sc16is750-1](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/37750b1e-49e2-4e39-a357-fde7ca2326da)
![config-sc16is750-2](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/514e5ae7-4e6c-47c5-8de2-0498bf6e7183)

# Wireing for SC16IS750  
Connect RX and other computer TX at any baud rate.   
Connect Gnd of ESP32 and Gnd of other computer.   

# Configuration for SC16IS752  
![config-top](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/b1a0a8b2-fb63-4247-b648-60f403fbfcfe)
![config-sc16is752-1](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/54662fdc-2ea0-4cb6-95e1-273f8ecf8199)
![config-sc16is752-2](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/6b2ca3ba-76cc-4f48-a8e4-0553109c4892)

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

