# Telemetry-Mark-II

**Telemetry Mark II** is a rudimentary telemetry system I made for the [Solar Car Challenge](https://www.solarcarchallenge.org/challenge/). This system collects and displays the temperature, voltage, and speed of the vehicle.

## Hardware:

This project is built Arduino hardwares and Adafruit. Please see the [Schematics](Schematics) folder for how to set them up.

In this section, we will label the hardwares used.

### Main Telemetry:

- 1 x [Arduino Mega 2560](https://store.arduino.cc/products/arduino-mega-2560-rev3)
- 2 x [DS18B20 Waterproof Temperature Sensor Cable](https://www.adafruit.com/product/381)
- 1 x [ILI9341 2.8 Inch TFT LCD with Touchscreen](https://www.adafruit.com/product/1770)
- Breadboards when needed. We used [ElectroCookie Prototype PCB Solderable Breadboard](https://www.amazon.com/ElectroCookie-Solderable-Breadboard-Electronics-Gold-Plated/dp/B07ZYNWJ1S/).
- Wires and resistors when needed.

The main telemetry also has a voltage sensor that measures the voltage of a battery source with a [Voltage Divider](https://en.wikipedia.org/wiki/Voltage_divider). Please scale the resistors appropriately to the battery source you want to measure.

### Speedometer:
- 1 x [Arduino Uno Rev3](https://store.arduino.cc/products/arduino-uno-rev3)
- 1 x [Adafruit Ultimate GPS FeatherWing](https://www.adafruit.com/product/3133)
- 1 x [ILI9341 2.8 Inch TFT LCD with Touchscreen](https://www.adafruit.com/product/1770)
- Breadboards when needed. We used [ElectroCookie Prototype PCB Solderable Breadboard](https://www.amazon.com/ElectroCookie-Solderable-Breadboard-Electronics-Gold-Plated/dp/B07ZYNWJ1S/).
- Wires and resistors when needed.

## Note:

1. Both [main_telemetry.ino](Code/main_telemetry/main_telemetry.ino) and [speedometer.ino](Code/speedometer/speedometer.ino) used [Kris Kasprzak](https://www.youtube.com/user/timetotravel)'s graphing functions from [here](https://www.youtube.com/watch?v=U5hOU-xxQgk). Relevant sections used in the code are commented too.

2. The schematics have been modified from their original pdf. Both schematics were made by the author. However, there was an error on [main_telemetry_schematic.pdf](Schematics/main_telemetry_schematic.pdf) on the authorship. In addition, the author's name has changed from the time they were made to now. That's why the authorship of both documents have been modified.

3. [speedometer.ino](Code/speedometer/speedometer.ino) used standard tests from the [Adafruit GPS library](https://github.com/adafruit/Adafruit_GPS) in the setup function:

```
This is the Adafruit GPS library - the ultimate GPS library
for the ultimate GPS module!

Tested and works great with the Adafruit Ultimate GPS module
using MTK33x9 chipset
------> http://www.adafruit.com/products/746

These modules use TTL serial to communicate, 2 pins are required to  
interface.

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above must be included in any redistribution
```