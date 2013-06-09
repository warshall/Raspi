#!/bin/bash
#
# gpiotest.sh:
#	Test the Pi's GPIO port
#################################################################################
# This file is part of wiringPi:
#	Wiring Compatable library for the Raspberry Pi
#
#    wiringPi is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    wiringPi is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
#################################################################################

testPins()
{
  start=$1
    end=$2

  for i in `seq $start $end`; do
    gpio mode $i in
  done

  for i in `seq $start $end`; do
    gpio mode $i up
    if [ `gpio read $i` = 0 ]; then
      echo "Pin $i failure - expected 1, got 0"
    fi
  done

  for i in `seq $start $end`; do
    gpio mode $i down
    if [ `gpio read $i` = 1 ]; then
      echo "Pin $i failure - expected 0, got 1"
    fi
  done

  for i in `seq $start $end`; do
    gpio mode $i up
    if [ `gpio read $i` = 0 ]; then
      echo "Pin $i failure - expected 0, got 1"
    fi
  done

  for i in `seq $start $end`; do
    gpio mode $i tri
  done

}

# Rev 1 or Rev 2:

testPins 0 7

# SPI

testPins 10 14

# Serial

testPins 15 16

# I2C - Needs somewhat different testing

gpio mode 8 in
gpio mode 9 in

if [ `gpio read 8` = 0 ]; then
  echo "Pin 8 failure - expected 1, got 0"
fi

if [ `gpio read 9` = 0 ]; then
  echo "Pin 9 failure - expected 1, got 0"
fi

gpio readall
