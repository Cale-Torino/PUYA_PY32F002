# PUYA_PY32F002










PUYA PlatformIO

install package in terminal in PlatformIO

pio pkg install -g -p https://github.com/positron96/platform-py32f0.git

https://github.com/positron96/framework-py32f0sdk

https://github.com/IOsetting/py32f0-template

https://github.com/blackmagic-debug

https://github.com/positron96/framework-py32f0sdk


https://www.youtube.com/watch?v=QkO6dk8cdEs




C:\Users\User501\.platformio\packages\framework-py32f0sdk\PY32F0xx_HAL_Driver\Src
C:\Users\User501\.platformio\boards


https://community.platformio.org/t/how-to-define-custom-board-within-project/39424/2


https://docs.platformio.org/en/stable/platforms/creating_board.html

BOARDS

C:\Users\User501\.platformio\packages\framework-py32f0sdk\ldscripts


jlink not supported nowIn file included from C:\Users\User501\.platformio\packages\framework-py32f0sdk\PY32F002B_HAL_Driver\Src\py32f002b_hal.c:39:
C:\Users\User501\.platformio\packages\framework-py32f0sdk\PY32F002B_HAL_Driver\Inc/py32f002b_hal.h:33:10: fatal error: py32f002b_hal_conf.h: No such file or directory



{
    "build": {
      "core": "py32",
      "cpu": "cortex-m0plus",
      "mcu": "py32f002bf15p",
      "extra_flags": "-DPY32F002BF15P",
      "ldscript": "py32f002bx5.ld"
    },
    "debug": {
      "jlink_device": "PY32F002BF15P",
      "svd_path": "py32f002bf15p.svd"
    },
    "frameworks": [
      "py32f0sdk"
    ],
    "name": "Generic PY32F002BF15P",
    "upload": {
      "maximum_ram_size": 3072,
      "maximum_size": 24576,
      "protocol": "jlink",
      "protocols": [
        "jlink",
        "blackmagic"
      ]
    },
    "url": "https://www.puyasemi.com/en/py32_series.html",
    "vendor": "Generic"
  }


C:\Users\User501\.platformio\packages\framework-py32f0sdk\PY32F002B_HAL_Driver\Inc/py32f002b_hal.h:33:10: fatal error: py32f002b_hal_conf.h: No such file or directory

C:\Users\User501\.platformio\packages\framework-py32f0sdk\PY32F002B_HAL_Driver\Inc

C:\Users\User501\.platformio\packages\framework-py32f0sdk\PY32F002B_HAL_Driver\Inc


C:\Users\User501\.platformio\packages\framework-py32f0sdk\CMSIS\Device\PY32F0xx\Include

 #define PY32F002Bx5 */  /*!< PY32F002Bx5 Devices (PY32F002Bx5 microcontrollers where the Flash memory is 24  Kbytes)

https://github.com/IOsetting/py32f0-template/tree/main

      //"jlink_device": "PY32F002BF15P",



C:\Users\User501\.platformio\packages\framework-py32f0sdk\CMSIS\Device\PY32F0xx\Include/py32f0xx.h:269:10: fatal error: py32f0xx_hal.h: No such file or directory



py32f002b_hal.h


https://www.pishop.co.za/store/raspberry-pi-debug-probe?keyword=Debug%20Probe&category_id=0


C:\Users\User501\.platformio\packages\framework-py32f0sdk\PY32F0xx_HAL_Driver\Inc


https://github.com/paulscalise1/puya-32-environment-setup

https://git.unl.edu/pscalise2/unl-ece-keychain



https://github.com/IOsetting/py32f0-template/issues/6

https://www.aliexpress.com/item/1005004518845326.html


https://github.com/IOsetting/py32f0-template/issues/34






https://hackaday.io/project/193025-py32f002a-f15p-development-board

https://arduino.luatos.com/

https://github.com/Air-duino/Arduino-AirMCU





https://docs.platformio.org/en/latest/projectconf/sections/platformio/index.html


https://community.platformio.org/t/how-to-write-build-flags-in-platformio-ini/38700/2

py32f002bx5







https://community.platformio.org/t/arduino-due-or-other-sam3-4-upload-fails-with-atmel-ice-jtag-on-vscode-with-platformio/22258/8


https://docs.platformio.org/en/latest/platforms/creating_board.html



Resolving generic_py32 dependencies...
Already up-to-date.
Updating metadata for the vscode IDE...
UserSideException: Processing generic_py32 (platform: py32f0; board: generic_py32f002b; framework: cmsis)
--------------------------------------------------------------------------------
Verbose mode can be enabled via `-v, --verbose` option
CONFIGURATION: https://docs.platformio.org/page/boards/py32f0/generic_py32f002b.html
PLATFORM: PY32F0xx (1.0.0+sha.1b5cae9) > Generic PY32F002Bx5
HARDWARE: PY32F002BX5 3KB RAM, 24KB Flash
DEBUG: Current (blackmagic) External (blackmagic, jlink, stlink)
PACKAGES: 
 - tool-pyocd @ 2.3600.0 (36.0) 
 - toolchain-gccarmnoneeabi @ 1.100301.220327 (10.3.1)




 -I "C:/Users/User501/.platformio/packages/framework-py32f0sdk/CMSIS/Device/PY32F0xx/Include"
# -I "C:/Users/User501/.platformio/packages/framework-py32f0sdk/CMSIS/Device/PY32F0xx/Source"
 -I C:/Users/User501/.platformio/packages/framework-py32f0sdk/PY32F0xx_HAL_BSP/Inc
 -I C:/Users/User501/.platformio/packages/framework-py32f0sdk/PY32F0xx_HAL_Driver/Inc

 -I "C:/Users/User501/.platformio/packages/framework-py32f0sdk/PY32F002B_HAL_Driver/Inc"
 #-I "C:/Users/User501/.platformio/packages/framework-py32f0sdk/PY32F002B_HAL_Driver/Src"
-I "C:/Users/User501/.platformio/packages/framework-py32f0sdk/PY32F002B_HAL_BSP/Inc"
# -I "C:/Users/User501/.platformio/packages/framework-py32f0sdk/PY32F002B_HAL_BSP/Src"





https://github.com/microcai/platform-py32/blob/master/platform.json



PY32F002B

py32f002bx5


looking in 

C:\Users\User501\.platformio\packages\framework-py32f0sdk\CMSIS\Device\PY32F0xx\Include

instead of in

C:\Users\User501\.platformio\packages\framework-py32f0sdk\PY32F0xx_HAL_Driver\Inc


https://www.instructables.com/PY32Duino-Anemometer-Aka-Making-a-Wind-Speed-Meter/

https://github.com/bole2334/Arduino-PY32

https://github.com/microcai/Arduino-PY32


https://github.com/ElectronicCats/puya-projects

I'm trying to connect to the 8 pin (SOP8) PY32F002AL15S6TU via PuyaISP, but i cant really get it working, how should i enter the bootloader? I have tried pulling pin 6 (PA2/PF2-NRST) both high and low while power-cycling the MCU, but PuyaISP wont connect,

Is pulling NRST high the correct method to enter the bootloader? This package does not have a dedicated BOOT0 pin,

I have the option to try J-Link, does Puya have some tool to upload or read the mcu info via this? I have tried PuyaProgrammer but it can't find the USB device to use for SWD, For the J-link i'm using a nucleo board i have converted to J-link, but i belive Puya has its own programmer but it should be compatible ?

https://github.com/wagiminator/MCU-Flash-Tools/tree/main/pypi_packages/puyaisp

Tested so far:
- Bootloader. Pulling PB6 (BOOT0) high before power-on (Or resetting afterwards) enters the embedded bootloader, just like in STM32.
  Connect RX/TX to PA2/PA3, open Puya ISP, everything works.


https://www.eevblog.com/forum/microcontrollers/$0-11-py32f002a-m0-24mhz-320kb-actually-324kb-more-peripherals/

https://www.xinlinggo.com/col.jsp?m530pageno=11&id=111



ICP: It is used to update the entire contents of the Flash memory, using the SWD protocol or the
boot loader to load the user application into the MCU. ICP provides quick and efficient design iterations and eliminates unnecessary package handling or socketing of devices





Hi, another newbie/amateur here, hopefully you still have some patience for one of those  :D
I'd like some help writing to the flash of the PY32F002AL15S6TU (That is, the SOP-8 package).
After reading this thread and finding out that only the TSSOP-20 package supports ISP, I tried first with my PY32F002AF15P6TU (TSSOP-20) using Arduino as my IDE and writing to the PY32F002AF15P6TU directly from Arduino using a USB->TTL adapter with BOOT0 pulled high and everything worked well on the first try (yes, I was also surprised :) ) - Got some LEDs blinking and some buzzers beeping and was happy.




puyaisp
Description
With this tool, PUYA microcontrollers of the series PY32F0xx (and maybe other PY32) can be flashed via a simple USB-to-serial converter by utilizing the factory built-in embedded UART bootloader.

Preparations
If necessary, a driver for the USB-to-serial converter used must be installed.

Usage as a Script
Connect your USB-to-serial converter to your PY32F0xx MCU as follows:

USB2SERIAL            PY32F0xx
+--------+      +-------------------+
|     RXD| <--- |PA2 or PA9  or PA14|
|     TXD| ---> |PA3 or PA10 or PA15|
|     VDD| ---> |VDD                |
|     GND| ---> |GND                |
+--------+      +-------------------+

Set your MCU to bootloader mode by using ONE of the following methods:

Disconnect your USB-to-serial converter, pull BOOT0 pin (PF4) to VCC (or press and hold the BOOT button, if your board has one), then connect the converter to your USB port. BOOT0 pin (or BOOT button) can be released now.
Connect your USB-to-serial converter to your USB port. Pull BOOT0 pin (PF4) to VCC, then pull nRST (PF2) shortly to GND (or press and hold the BOOT button, then press and release the RESET button and then release the BOOT button, if your board has them).

Usage: puyaisp.py [-h] [-u] [-l] [-e] [-o] [-G] [-R] [-f FLASH]

Optional arguments:
  -h, --help                show this help message and exit
  -u, --unlock              unlock chip (remove read protection)
  -l, --lock                lock chip (set read protection)
  -e, --erase               perform chip erase (implied with -f)
  -o, --rstoption           reset option bytes
  -G, --nrstgpio            make nRST pin a GPIO pin
  -R, --nrstreset           make nRST pin a RESET pin
  -f FLASH, --flash FLASH   write BIN file to flash and verify

Example:
python3 puyaisp.py -f firmware.bin






https://arduino.py32.org/getting_started/install.html#%E6%B7%BB%E5%8A%A0%E5%BC%80%E5%8F%91%E6%9D%BF%E5%9C%B0%E5%9D%80

https://github.com/PY32Duino/Arduino-pack-json-ci/releases/download/Nightly/package_py32_index.json



it's very likely that 002B is an equivalent of L020, I just run the Deep Stop example on a TSSOP20 PY32F002b, the current consumption is much lower than the Stop mode ( 0.6 uA vs 1.6 uA).



https://www.eevblog.com/forum/microcontrollers/$0-11-py32f002a-m0-24mhz-320kb-actually-324kb-more-peripherals/175/



I'm writing a summery of what I did to program these PY32F002A chips. Maybe it'll help some other n00b to save some time:

https://www.eevblog.com/forum/microcontrollers/$0-11-py32f002a-m0-24mhz-320kb-actually-324kb-more-peripherals/175/


https://github.com/RadioOperator/STM32F103C8T6_CMSIS-DAP_SWO works like a champ on the BluePill board.


https://github.com/RadioOperator/STM32F103C8T6_CMSIS-DAP_SWO





The bootloader is embedded into the mcu and can't be changed.

To enable it, join PB6/Boot0 and 3v3.
Then connect the uart as follows:
- Rx to PA2
- Tx to PA3

Power it on, puyaISP should work.
If not working, try reversing Tx/Rx as this is a common mistake.
Remember this device has no USB, it's only for power.






It looks like the F002B/L020 is aimed for replacing existing 8 bit low end MCUs. If you notice, GPIOs and AFs range from 0 to 7, and pinouts of various packages match the ones of other 8 bit MCUs such as STM8S, Nuvoton, FMD, etc.

I noticed there is a new PY32T020 whose doc is only in chinese. AFAIK the T means "touch button" capability. I wonder if there is any correspondence to the ones we know about at silicon level...



https://github.com/amwales-888/py32f002bf15p6


https://black-magic.org/


https://hackaday.io/project/192563-py32f002a-mcu-battery-internal-resistance-tester



Tricky? Couldn't be easier!

Mcu info doesn't clear the chip automatically, just shows it's protected.
Download code does... exactly that!
It will reset automatically on erasing/programming, if you permanently pull boot high, it'll enter bootloader again.
(So if you plan to do multiple operations, leave boot high all the time)
If you want it to execute the program automatically without releasing boot0, tick "Use GO command".


What I know about PY32L020 is that it has an extra "deep stop" mode while PY32F002B only has "stop" mode.


https://www.eevblog.com/forum/microcontrollers/$0-11-py32f002a-m0-24mhz-320kb-actually-324kb-more-peripherals/75/

Neither I. Really, try CubeiDE + devices patch and Jlink.




Puya ISP is the software itself. Connect the serial converter to Rx/Tx, set boot=1, that's all it takes.
I have no idea what to use for PyLink.







https://www.elektroda.com/rtvforum/topic3946116-60.html

PY32F002AL15S6TU 

can only use jlink



https://blog.csdn.net/zhuannnn/article/details/149096398

https://blog.csdn.net/2401_85766447/article/details/146565529

https://blog.csdn.net/zhuannnn/article/details/149093208


















```
                    +-----+
            +--------------------+
            |J3     |     |    J2|
        VDD-|1      +-----+     1|-GND
        GND-|2                  2|-GND
       +3.3-|3                  3|-+3.3
[RESET] PF2-|4                  4|-PF4 [BOOT0_PRE]
[SWCLK]PA14-|5                  5|-GND
[SWDIO]PA13-|6                  6|-GND
        GND-|7       RST        7|-GND
        PF3-|8       +-+        8|-GND
        PA0-|9       |O|        9|-GND
        PA1-|10      +-+       10|-PB7
        PA2-|11                11|-PB6
        PA3-|12                12|-PB5
        PA4-|13                13|-PB4
        PA6-|14                14|-PB3
        PA6-|15   UPB          15|-PA15
        PA7-|16   +-+          16|-PA12 [USER LED - GREEN]
        PB0-|17   |O|          17|-PA11 [USER PUSHBUTTON]
        PB1-|18   +-+          18|-PA8
            |                    |
            +--------------------+
```

download Keil uVision MDK-Community

https://developer.arm.com/Tools%20and%20Software/Keil%20MDK

https://www.keil.arm.com/mdk-community/

https://developer.arm.com/Tools%20and%20Software/Keil%20MDK


PUYA_PY32F002


https://www.eevblog.com/forum/microcontrollers/$0-11-py32f002a-m0-24mhz-320kb-actually-324kb-more-peripherals/msg5464000/#msg5464000


https://arduino.py32.org/getting_started/install.html#%E6%B7%BB%E5%8A%A0%E5%BC%80%E5%8F%91%E6%9D%BF%E5%9C%B0%E5%9D%80



https://www.blaatschaap.be/32f103-comparison-part-1/

https://www.elektroda.com/rtvforum/topic3946116.html

https://silicognition.com/Electronics/PuyaCharge/py32f003-undervoltage-run-mode/


https://github.com/flaviut/fan-controller


https://github.com/IOsetting/py32f0-template





Someone has been working on it. 

https://github.com/Air-duino/Arduino-AirMCU (air001 is py32f002a relabeled).





The bootloader is embedded into the mcu and can't be changed.

To enable it, join PB6/Boot0 and 3v3.
Then connect the uart as follows:
- Rx to PA2
- Tx to PA3

Power it on, puyaISP should work.
If not working, try reversing Tx/Rx as this is a common mistake.
Remember this device has no USB, it's only for power.




It looks like the F002B/L020 is aimed for replacing existing 8 bit low end MCUs. 

If you notice, GPIOs and AFs range from 0 to 7, and pinouts of various packages match the ones of other 8 bit MCUs such as STM8S, Nuvoton, FMD, etc.




Personally, I use a ton of these and other 10c Chinese chips, but mainly just for trivial applications. 
For anything much more complicated, I lean towards STM32F0/G0. 
They're almost as cheap, especially when you factor in shipping costs. 
And they eliminate a whole slew of potential unknowns to troubleshoot when things need work.
 And as a plus, its relatively easy to port known working code over to one of these Chinese MCUs.








try use GCC / SDCC for the puya ICs as well

Regular editor with syntax highlighting and multiple tabs. It goes with everything.
I was tired of so many different scales that I got used to it.
In addition, GCC / SDCC / or whatever it is for a given system.




Project examples:
https://github.com/ElectronicCats/puya-projects
https://github.com/TDLOGY/PY32F002A-Dev-Resource
https://www.youtube.com/watch?v=qWRowOsYSLY
https://github.com/SimenZhor/PuyaNeoPixelExample
https://www.youtube.com/watch?v=Y-n7vXHAqm8
https://github.com/decaday/PY32_Docs
https://www.elektroda.com/rtvforum/topic3946116.html
https://www.eevblog.com/forum/microcontrollers/$0-11-py32f002a-m0-24mhz-320kb-actually-324kb-more-peripherals/50/
- []()
- []()
- []()
- []()
- []()
- []()



Links:
- [PY32 Development Resource](https://github.com/TDLOGY/PY32F002A-Dev-Resource)
- [py32f0-template](https://github.com/IOsetting/py32f0-template)
- [OpenPuya PY32F002A Series](https://py32.org/en/mcu/PY32F002Axx.html)
- [Puya's 10-cent PY32 series](https://jaycarlson.net/2023/02/04/the-cheapest-flash-microcontroller-you-can-buy-is-actually-an-arm-cortex-m0/)
- [lcsc Puya](https://www.lcsc.com/products/Microcontroller-Units-MCUs-MPUs-SOCs_11329.html?keyword=py32f0)
- [puyasemi.com](https://www.puyasemi.com/)
- [lcsc PY32F002](https://www.lcsc.com/search?q=%20PY32F002)
- []()
- https://www.eevblog.com/forum/microcontrollers/$0-11-py32f002a-m0-24mhz-320kb-actually-324kb-more-peripherals/150/
- https://www.puyasemi.com/en/mcu.html
- https://www.elektroda.com/rtvforum/topic3946116-30.html
- https://www.elektroda.pl/rtvforum/topic3951956.html
- https://py32.org/en/mcu/PY32F003xx.html#datasheet
- 
- 
- 
