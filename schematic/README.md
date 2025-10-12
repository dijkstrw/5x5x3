Third iteration of my 5x5;
- based on zmk, using the nicenano2 board / Supermini RF52840

Questions:
- Can the LDO keep up with 25 sk6803s?

25 * 5mA = 125mA, within range of charger and ldo on nicenano2

- Where are the specific pins for spi / i2c?

RF52840 can reconfigure its pins, so can be assigned to work well with
whatever layout we want.

Other keyboard projects of interest:

- foostan: corne / crkb: the first time I saw sk6812 in mini-e
  variant.

  https://github.com/foostan/kbd
  https://github.com/foostan/crkbd

  MIT license, parts reused:
  - Source of YS-SK6812-MINI-E schematic symbol, and 3d step model.

- Stefan Hamminga: sk6812mini model that models the underside of the
  package best.

- Spamwax: nicenano v2 step model

  https://www.printables.com/model/1181384-nicenano-mcu/files

- Supermini NRF52840 site

  https://wiki.icbbuy.com/doku.php?id=developmentboard:nrf52840
