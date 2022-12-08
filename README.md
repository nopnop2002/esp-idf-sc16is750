# esp-idf-sc16is750
sc16is750/752 driver for esp-idf.   
ESP32 has up to 3 hardware UARTs.   
This allows you to add two more hardware UARTs.   

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
__On all boards, the SC16IS752 IRQ pin and the board's IRQ connector are directly connected.__    
__It has a pull-up register, but it doesn't work.__   
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

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-sc16is750
cd esp-idf-sc16is750/selftest
idf.py set-target {esp32/esp32s2/esp32s3/esp32c2/esp32c3}
idf.py menuconfig
idf.py flash
```

__Note for ESP32C3__   
For some reason, there are development boards that cannot use GPIO06, GPIO08, GPIO09, GPIO19 for SPI clock pins.   
According to the ESP32C3 specifications, these pins can also be used as SPI clocks.   
I used a raw ESP-C3-13 to verify that these pins could be used as SPI clocks.   


# Wireing for i2c

|SC16IS750/752||ESP32|ESP32-S2/S3|ESP32-C3||
|:-:|:-:|:-:|:-:|:-:|:-:|
|VCC|--|5V|5V|5V|(*1)|
|GND|--|GND|GND|GND||
|RESET|--|N/C|N/C|N/C||
|A0/CS|--|5V|5V|5V|(*2)|
|A1/SI|--|5V|5V|5V|(*2)|
|NC/SO|--|N/C|N/C|N/C||
|IRQ|--|N/C|N/C|N/C||
|I2C/SPI|--|5V|5V|5V||
|SCL/SCLK|--|GPIO22|GPIO12|GPIO6|(*3)|
|SDA/VSS|--|GPIO21|GPIO11|GPIO5|(*3)|

(*1)
The SC16IS750 breakout board is equipped with a MIC5219 LG33 voltage regulator, which provides 3.3V to the chip.   
The SC16IS752 breakout board is equipped with a AMS1117-3.3 voltage regulator, which provides 3.3V to the chip.   
Therefore, the level of i2c is 3.3V.   
All pins are 5V tolerant.   

(*2)
i2c address selection.   
|A0|A1|Address|
|:-:|:-:|:-:|
|5V|5V|0x48|
|5V|GND|0x49|
|GND|5V|0x4C|
|GND|GND|0x4D|

(*3)
No Requires PullUp.   
You can change any pin using menuconfig.   

# Wireing for SPI

|SC16IS750/752||ESP32|ESP32-S2/S3|ESP32-C3||
|:-:|:-:|:-:|:-:|:-:|:-:|
|VCC|--|5V|5V|5V|(*1)|
|GND|--|GND|GND|GND||
|RESET|--|N/C|N/C|N/C||
|A0/CS|--|GPIO5|GPIO34|GPIO4|(*2)|
|A1/SI|--|GPIO23|GPIO35|GPIO1|(*2)|
|NC/SO|--|GPIO19|GPIO37|GPIO3|(*2)|
|IRQ|--|N/C|N/C|N/C||
|I2C/SPI|--|GND|GND|GND||
|SCL/SCLK|--|GPIO18|GPIO36|GPIO2|(*2)|
|SDA/VSS|--|GND|GND|GND||

(*1)
The SC16IS750 breakout board is equipped with a MIC5219 LG33 voltage regulator, which provides 3.3V to the chip.   
The SC16IS752 breakout board is equipped with a AMS1117-3.3 voltage regulator, which provides 3.3V to the chip.   
Therefore, the level of SPI is 3.3V.   
All pins are 5V tolerant.   

(*2)
You can change any pin using menuconfig.   

# SPI BUS selection   
![config-spi-bus](https://user-images.githubusercontent.com/6020549/206341263-72d825c3-f35e-4047-b28e-dd077026cfdf.jpg)


The ESP32 series has three SPI BUSs.   
SPI1_HOST is used for communication with Flash memory.   
You can use SPI2_HOST and SPI3_HOST freely.   
When you use SDSPI(SD Card via SPI), SDSPI uses SPI2_HOST BUS.   
When using this module at the same time as SDSPI or other SPI device using SPI2_HOST, it needs to be changed to SPI3_HOST.   
When you don't use SDSPI, both SPI2_HOST and SPI3_HOST will work.   
Previously it was called HSPI_HOST / VSPI_HOST, but now it is called SPI2_HOST / SPI3_HOST.   


# Baudrate generator   
SC16IS750/752 has baudrate generator.   
Since the communication speed is caluculated by dividing the frequency of the crystal, an error may occur depending on the communication speed.   
How to divide is described in the data sheet.   
For example, if you use a 3.072MHz crystal and set the communication speed to 3600bps, you need to divide the crystal frequency by 53.3333.   
Since such a value cannot be set in the register, sets 54 in the register.   
As a result, the actual communication speed will be 3555bps.   
This calculation can be calculated with the following code.   
```
#include <stdio.h>
void main() {
  long crystal_freq = 3072000; // 3,072,000MHz
  long prescaler = 1;
  long baudrate = 3600;
  long divisor1 = crystal_freq/prescaler;
  long divisor2 = baudrate*16;
  double divisorf = (double)divisor1/(double)divisor2;
  long divisor = divisorf + 0.999;
  printf("divisor1=%ld divisor2=%ld divisor=%ld divisorf=%f\n",
    divisor1, divisor2, divisor, divisorf);

  long actual_baudrate = (divisor1/divisor)/16;
  printf("actual_baudrate=%ld\n", actual_baudrate);
}
```

# Troubleshooting
Such an error may occur.   
If you change to a shorter wire, it will be fixed.   
![communication_error](https://user-images.githubusercontent.com/6020549/148180652-b1456e0c-516a-4edc-a815-024121ff1b7f.jpg)
![WriteRegister_i2c](https://user-images.githubusercontent.com/6020549/148201025-cc847b6b-01a1-462f-990f-de23760408e8.jpg)

