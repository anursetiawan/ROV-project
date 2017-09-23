# ROV-project

## Information
`NanoReceiverSerial` is the sketch for on-board Arduino Nano, `UnoSenderSerial` is for the remote which is running on Arduino Uno.

## Current problems:
* ~~Vague baud-rate value. 9600 is too slow, 2000000 is too fast and causing clog-up~~
* Hacked-together basic serial communication, not a proper one

## Finished problems:
* Basic function separately
* Rudimentary communication
* Settle baud-rate at 115200, since it is pretty standard and also fast enough
 
## Tutorial:
**Ubuntu**
1. Install Arduino IDE from repository
   `sudo apt install arduino`
2. Clone or download these files
   `git clone https://github.com/noersetiawan/ROV-project`
3. Open the .ino file
   `xdg-open path/to/ino/file/filename.ino`
4. Choose your board on *Tools > Board*
5. Upload the sketch with the *right arrow* button on menu bar, or `Ctrl-U`
6. Open *Tools > Serial Monitor*, or `Ctrl-Shift-M`
