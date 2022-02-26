# xs-robotic-arduino

Sources and code from Arduino projects organized by XS Robotic Club.

## How to use

### Required software

* Arduino IDE 1.x
* Visual Studio Code
* PlatformIO

### Directory structure

* `/ArduinoIDESketches/` contains projects built with Arduino IDE.
* All other folders under `/` contains projects built with PlatformIO.

### Steps to build

#### Arduino IDE projects

Start Arduino IDE, open `*.ino` files in the project directory and click `Compile` or `Upload`.

#### PlatformIO projects

Follow these instructions (assuming you are using PowerShell):

```plain
PS > C:\path\to\.platformio\penv\Scripts\Activate.ps1
(penv) PS > cd C:\path\to\project\
(penv) PS > pio run
```
