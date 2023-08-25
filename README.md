# Features

* Track workplace incidents of your choice, such as bad puns or industrial maimings
* High-fidelity audio mimicking a groaning human voice, if the human voice is a square wave
* Exceeds the GPIO pins' absolute maximum voltage ratings
* Big chonky button 👌

# Required components

* An [Adafruit METRO 328](https://www.adafruit.com/product/2488).
* A 9V DC barrel jack power supply. See the Adafruit METRO documentation for which ones will fit.
* 2 big 7-segment displays. I'm not sure which ones I used, but they're probably the [SA23-11SURKWA](https://www.digikey.com/en/products/detail/kingbright/SA23-11SURKWA/16602188) or something equivalent.
* An 8Ω speaker.
* 100Ω and 220Ω resistors.
* Some kind of enclosure to hold it together. Mine is a 3D-printed frankenstein that isn't easily reproducible—sorry!
* Solid-core wire recommended for stabbing into the METRO's GPIO headers and wiring point-to-point. 

# Wireup

See [include/pins.h](include/pins.hpp).

# Development

This project uses [PlatformIO](https://platformio.org/).

1. Install PlatformIO according to their instructions and your editor or IDE preferences.
2. Program the board with `pio run -t upload`, or however your IDE does it.
