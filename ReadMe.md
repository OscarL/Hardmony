# Hardmony - A Hardware Monitoring Application

I originally worked on this on and off in 2003 to 2006.

The idea was to have a central "Hardware Monitoring" app for BeOS, making it work with
all the different temp sensores that were available at the time (mostly LM75/78/80/87,
Via's VT82C686A/B, some Winbound W83781D, etc).

Ended up ever only working, for BeOS, with my [it87](https://github.com/OscarL/it87) driver
(originally on ITE IT8705 / SiS950, in 2023... works on Haiku with an ITE IT8718F)

# Build

`make` should be enough on Haiku beta4 and up.

# Usage

Assuming the mentioned it87 driver works on your system, just start Hardmony any way you like.

It will surely look aweful with font size other than 10 pt, as it doesn't uses Haiku's Layout
System yet.

Hitting the Settings button crashes the app for some reason I haven't tracked yet.

Enabling the "Deskbar" checkbox, should show the current temp on Deskbar.

# Screenshot

![Hardmony](Hardmony.png?raw=true)

# License

MIT
