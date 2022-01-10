# gpio
GPIO INPUT/OUTPUT.   

This project has the following patterns:

|# of UART|Interface|Direction|
|:-:|:-:|:-:|
|--|IC2|OUTPUT|
|--|IC2|INPUT using polling|
|--|IC2|INPUT using interrupt|
|--|SPI|OUTPUT|
|--|SPI|INPUT using polling|
|--|SPI|INPUT using interrupt|

__The number of UART channels is irrelevant for GPIO operations.__   


# Configuration   
![config-top](https://user-images.githubusercontent.com/6020549/148174483-94403f5c-b28e-4421-9a76-4888c5138169.jpg)
![config-output](https://user-images.githubusercontent.com/6020549/148174490-dcb135e5-3bbf-48de-9c6a-72ea9fd93f65.jpg)
![config-input](https://user-images.githubusercontent.com/6020549/148174498-32f320d1-1c06-4f86-a0a5-fc94489fb84b.jpg)
![config-interrupt](https://user-images.githubusercontent.com/6020549/148174507-0e8af349-244a-4f3f-a0f2-bdd277d17206.jpg)

# Wireing for OUTPUT  
Connect GPIO0 and LED.   
```
ESP32                     Breakout
                         +------------------------
                         |
                         |       +---------------+
                         |       |SC16IS752      |
                         |       |               |
GND---220Ohm---LED-----GPIO0----GPIO0            |
                         |       |               |
                         |       |               |
                         |       |               |
                         |       |               |
                         |       |               |
                         |       |               |
                         |       |               |
                         |       |               |
                         |       |               |
                         |       +---------------+
                         |
                         +-----------------------
```

# Wireing for INPUT using polling   
```
ESP32                     Breakout
                         +------------------------
                         |
5V-------------+         |       +---------------+
               |         |       |SC16IS75x      |
             10Kohm      |       |               |
               +-------GPIO0----GPIO0            |
              /  Switch  |       |               |
               |         |       |               |
GND------------+         |       |               |
                         |       |               |
                         |       |               |
                         |       |               |
                         |       |               |
                         |       |               |
                         |       |               |
                         |       +---------------+
                         |
                         +-----------------------
```

# Wireing for INPUT using interrupt   
Interrupts are taken from GPIO16.   
No pull-up resistor is needed.   
```
ESP32                     Breakout
                         +------------------------
                         |
5V-------------+         |       +---------------+
               |         |       |SC16IS752      |
             10Kohm      |       |               |
               +-------GPIO0----GPIO0            |
              /  Switch  |       |               |
               |         |       |               |
GND------------+         |       |               |
                         |       |               |
                         |       |               |
GPIO16---------+--------IRQ--+--IRQ              |
                         |   |   |               |
                         |   |   |               |
                         |   |   |               |
                         |   |   +---------------+
                         |   |
                         |   +--1Kohm--N/C
                         |
                         +-----------------------
```
