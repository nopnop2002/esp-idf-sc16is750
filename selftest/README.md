# selftest
Operation check only with Breakout board.

This project has the following patterns:

|# of UART|Interface|
|:-:|:-:|
|Single|IC2|
|Single|SPI|
|Dual|IC2|
|Dual|SPI|

# Configuration   
![config-top](https://user-images.githubusercontent.com/6020549/148172889-67e97980-84bb-48c9-ab57-273b1379ec8c.jpg)
![config-sc16is750-1](https://user-images.githubusercontent.com/6020549/148172896-f2fbfc7a-3cb7-41de-88f5-783144e15425.jpg)
![config-sc16is750-2](https://user-images.githubusercontent.com/6020549/148172904-0678461f-efba-4577-ae3e-02799d8be4d6.jpg)


# Wireing for single channel  
Connect TX and RX with a short wire.   

# Wireing for dual channel  
Connect TX of ChannelA and RX of ChannelB with a short wire.   
Connect TX of ChannelB and RX of ChannelA with a short wire.   
