# echo
Converts the entered characters from uppercase to lowercase and from lowercase to uppercase and sends them back.   
```abcdEFGH-->ABCDefgh```   

This project has the following patterns:

|# of UART|Interface|
|:-:|:-:|
|Single|IC2|
|Single|SPI|
|Dual|IC2|
|Dual|SPI|


# Configuration   
![config-top](https://user-images.githubusercontent.com/6020549/148176368-79ed4432-46ab-49b3-a86f-1872e73310d2.jpg)
![config-echo-1](https://user-images.githubusercontent.com/6020549/148176378-da936cfc-c2af-4ab9-8c20-dd2fddbbabd9.jpg)
![config-echo-2](https://user-images.githubusercontent.com/6020549/148176381-6f1e9d38-0861-432a-8c54-6e67329c5aa6.jpg)

# Wireing for single channel  
Connect RX and other computer TX at any baud rate.   
Connect TX and other computer RX at any baud rate.   
Connect Gnd of ESP32 and Gnd of other computer.   

# Wireing for dual channel  
Connect RX of ChannelA and other computer TX at any baud rate.   
Connect TX of ChannelA and other computer RX at any baud rate.   
Connect RX of ChannelB and other computer TX at any baud rate.   
Connect TX of ChannelB and other computer RX at any baud rate.   
Connect Gnd of ESP32 and Gnd of other computer.   
