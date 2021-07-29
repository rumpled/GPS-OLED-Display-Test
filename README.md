# GPS OLED Display Test

Goal: display a count of satellites for a gps fix and the current speed on a small OLED display

Libraries:

- u8g2 - https://github.com/olikraus/u8g2



References:

- RobotZero - https://robotzero.one/arduino-neo-gps-oled/



Things learned:

- How finicky it is to manually draw everything on an OLED screen
- How to stuff a float into a char[] - https://www.hobbytronics.co.uk/arduino-float-vars
- How to stuff an int into a char[] - http://www.nongnu.org/avr-libc/user-manual/group__avr__stdlib.html#gaa571de9e773dde59b0550a5ca4bd2f00
- All about tiny fonts
- Right-aligning variable-width text - https://github.com/olikraus/u8g2/issues/983#issuecomment-527340372