/*
   Copyright (c) 2016 Evan Kale
   Email: EvanKale91@gmail.com
   Website: www.ISeeDeadPixel.com
            www.evankale.blogspot.ca

   This file is part of ArduinoMidiPS2.

   ArduinoMidiPS2 is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MagicMusicKeyboard.h"
#include <Encoder.h>

//MIDI baud rate
#define SERIAL_RATE 19200



//PS2 pins
#define KBD1_CLOCK 5
#define KBD1_DATA 4

//First note offsets
#define KBD1_OFFSET 0

MagicMusicKeyboard magicMusicKeyboard1(KBD1_CLOCK, KBD1_DATA, KBD1_OFFSET);

Encoder Enc1(9, 8);
Encoder Enc2(7, 6);

long oldPosEnc1 = -999;
long oldPosEnc2 = -999;

void setup()
{
  Serial.begin(SERIAL_RATE);
  magicMusicKeyboard1.init();


}

void loop()
{
  magicMusicKeyboard1.update();



  long newPosEnc1 = Enc1.read();
  long newPosEnc2 = Enc2.read();

  if (newPosEnc1 > oldPosEnc1) {
    usbMIDI.sendNoteOn(120, 127, 2);
    oldPosEnc1 = newPosEnc1;
  }
  if (newPosEnc1 < oldPosEnc1) {
    usbMIDI.sendNoteOn(121, 127, 2);
    oldPosEnc1 = newPosEnc1;
  }

  if (newPosEnc2 > oldPosEnc2) {
    usbMIDI.sendNoteOn(122, 127, 2);
    oldPosEnc2 = newPosEnc2;
  }
  if (newPosEnc2 < oldPosEnc2) {
    usbMIDI.sendNoteOn(123, 127, 2);
    oldPosEnc2 = newPosEnc2;
  }
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}



