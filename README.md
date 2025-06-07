# PUYA_PY32F002

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
