# esp-idf-sc16is750
sc16is750/750 driver for esp-idf.

## SC16IS750 Breakout
SC16IS750 has a single channel UART and eight GPIOs.   
14.7456MHz crystal is used for SC16IS750.   
__The maximum transfer speed of SC16IS750 is 14745600/16 = 921,600bps.__   
__However, when communicating with Arduino UNO, the maximum communication speed of UNO is 115200bps.__   


![SC16IS750](https://user-images.githubusercontent.com/6020549/71384102-bd022780-2622-11ea-8f5a-25f2fd733f19.JPG)

__There is a bug at the PCB routing:__   
__On all boards, the wire between the SC16IS750 IRQ pin and the board's IRQ connector is missing.__   
__Therefore, interrupt notification by IRQ does not work.__   


```
      Breakout
      +--------------------------
      |
      |       +---------------+
      |       |SC16IS750      |
      |       |               |
      |       |               |
      |       |               |
      |       |               |
      |       |               |
      |       |               |
      |       |               |
     IRQ  +--IRQ              |
      |   |   |               |
      |   |   |               |
      |   |   |               |
      |   |   +---------------+
      |   |
      |   +--1Kohm--N/C
      |
      +--------------------------
```

## SC16IS752 Breakout
SC16IS752 has a 2-channel UART and 8 GPIOs.   
1.8432Mhz crystal is used for SC16IS752.   
__The maximum transfer speed of SC16IS752 is 1843200/16 = 115,200bps.__

![SC16IS752-1](https://user-images.githubusercontent.com/6020549/71384120-e327c780-2622-11ea-8b85-b35da2f9deaa.JPG)

__There is a bug at the PCB routing:__   
__On all boards, the SC16IS752 IRQ pin and the board's IRQ connector are directly connected. pull-up register doesn't work.__   
__Therefore, when using IRQ, an external pull-up resistor is required.__   


```
      Breakout
      +--------------------------
      |
      |       +---------------+
      |       |SC16IS752      |
      |       |               |
      |       |               |
      |       |               |
      |       |               |
      |       |               |
      |       |               |
      |       |               |
     IRQ--+--IRQ              |
      |   |   |               |
      |   |   |               |
      |   |   |               |
      |   |   +---------------+
      |   |
      |   +--1Kohm--N/C
      |
      +--------------------------
```


# Software requirements
esp-idf v4.4 or later.   
This is because this version supports ESP32-C3.   

# Installation for ESP32
```
git clone https://github.com/nopnop2002/esp-idf-sc16is750
cd esp-idf-sc16is750/selftest
idf.py set-target esp32
idf.py menuconfig
idf.py flash
```

# Installation for ESP32-S2
```
git clone https://github.com/nopnop2002/esp-idf-sc16is750
cd esp-idf-sc16is750/selftest
idf.py set-target esp32s2
idf.py menuconfig
idf.py flash
```

# Installation for ESP32-C3
git clone https://github.com/nopnop2002/esp-idf-sc16is750
cd esp-idf-sc16is750/selftest
idf.py set-target esp32c3
idf.py menuconfig
idf.py flash
```

__Note__   
For some reason GPIO06, GPIO08, GPIO09, GPIO19 cannot be used for SPI clock pins on my board.   
I looked at the ESP32-C3 datasheet, but I don't understand why.   
This may be a problem only for my board.   

