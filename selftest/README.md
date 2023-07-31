# selftest
Loop back test only with Breakout board.   

This project has the following patterns:

|# of UART|Interface|
|:-:|:-:|
|Single|IC2|
|Single|SPI|
|Dual|IC2|
|Dual|SPI|

# Configuration for application
![config-top](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/a585a00a-8d99-4acc-8db6-ff8c5acd3b49)
![config-app](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/8bf684e6-ca0f-4e02-8bdd-c782e824427f)


# Wireing for SC16IS750  
Connect TX and RX with a short wire.   

# Wireing for SC16IS752  
Connect TX of ChannelA and RX of ChannelB with a short wire.   
Connect TX of ChannelB and RX of ChannelA with a short wire.   
