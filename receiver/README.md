# receiver
Receive data from UART.   
There is no transmission.   

This project has the following patterns:

|# of UART|Interface|EOL|
|:-:|:-:|:-:|
|Single|IC2|(*1)|
|Single|IC2|(*2)|
|Single|SPI|(*1)|
|Single|SPI|(*2)|
|Dual|IC2|(*1)|
|Dual|IC2|(*2)|
|Dual|SPI|(*1)|
|Dual|SPI|(*2)|


(*1)
Input is completed with the terminating character.   
Terminating character is LF.   
You can change this using menuconfig.   

(*2)
Input is completed with the timeout.   
Timeout is 500 mill sec.   
You can change this using menuconfig.   

# Configuration   
![config-top](https://user-images.githubusercontent.com/6020549/148177110-b951cd60-dea7-4d8d-b627-38477a29ae58.jpg)
![config-receiver-character](https://user-images.githubusercontent.com/6020549/148177129-5512c565-86e7-4425-9ad4-0a4642b49117.jpg)
![config-receiver-timeout](https://user-images.githubusercontent.com/6020549/148177140-280ab07b-cc58-40e7-8491-047d0c046137.jpg)

# Wireing for single channel  
Connect RX and other computer TX at any baud rate.   
Connect Gnd of ESP32 and Gnd of other computer.   

# Wireing for dual channel  
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
  Serial.print(buf);
  delay(1000);
}
```

