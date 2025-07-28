# gpio
GPIO INPUT/OUTPUT.   

This project has the following patterns:

|Model|Interface|Direction|
|:-:|:-:|:-:|
|SC16IS75x|IC2|OUTPUT|
|SC16IS75x|IC2|INPUT using polling|
|SC16IS752|IC2|INPUT using interrupt|
|SC16IS75x|SPI|OUTPUT|
|SC16IS75x|SPI|INPUT using polling|
|SC16IS752|SPI|INPUT using interrupt|

__The number of UART channels is irrelevant for GPIO operations.__   


# Configuration   
![config-top](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/ffe3187e-f691-4e51-a734-62bce9a74e1c)
![config-output](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/423dd5d7-3f92-448c-a842-5cceddb9391e)
![config-input](https://github.com/nopnop2002/esp-idf-sc16is750/assets/6020549/4c83558f-c9dc-4fd9-acf2-b706d8917b5b)
![Image](https://github.com/user-attachments/assets/d19a9f63-3300-4110-b3e9-735fd99410d9)

# Wireing for OUTPUT  
Connect GPIO0 and LED.   
```
ESP32                     Breakout
                         +------------------------
                         |
                         |       +---------------+
                         |       |SC16IS752      |
                         |       |               |
GND---220ohm---LED-----GPIO0----GPIO0            |
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
5V-------------+         |
               |         |       +---------------+
             10Kohm      |       |SC16IS75x      |
               |         |       |               |
               +-------GPIO0----GPIO0            |
               |         |       |               |
              /  Switch  |       |               |
               |         |       |               |
GND------------+         |       |               |
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
ESP-IDF does not require a pull-up resistor.   
__SC16IS750 has a problem with the PCB and cannot use interrupts.__   
```
ESP32                     Breakout
                         +------------------------
5V-------------+         |
               |         |       +---------------+
             10Kohm      |       |SC16IS752      |
               |         |       |               |
               +-------GPIO0----GPIO0            |
               |         |       |               |
              /  Switch  |       |               |
               |         |       |               |
GND------------+         |       |               |
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
