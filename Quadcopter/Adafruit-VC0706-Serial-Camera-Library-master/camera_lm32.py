	#!/usr/bin/python
# python code for interfacing to VC0706 cameras and grabbing a photo
# pretty basic stuff
# written by ladyada. MIT license
# revisions for Raspberrry Pi by Gordon Rush

import sys, os, serial 
import Image
BAUD = 38400
# this is the port on the Raspberry Pi; it will be different for serial ports on other systems.
PORT = "/dev/ttyUSB1"

TIMEOUT = 0.5    # I needed a longer timeout than ladyada's 0.2 value
SERIALNUM = 0    # start with 0, each camera should have a unique ID.


def readlm32():
   photo = s.readall()
   photo += s.readall()
   photo += s.readall()
   photo += s.readall()
   return photo

s = serial.Serial( PORT, baudrate 	=BAUD, timeout = TIMEOUT )
photo=[]
while (len(photo)<1):
   reply = readlm32()
   r = list(reply)  
   photo = r
   print len(photo);
photodata = ''.join( photo[:] )


f=open( "photolm32.txt", 'w' )

for d in photodata:
   sys.stdout.write(" "+hex(ord(d))) 
   f.write( "\n"+hex(ord(d)) )

f.close()

f = open( "photo.jpg", 'w' )

photodata = ''.join( photo )

f.write( photodata )

f.close()

#print "\n Tamano: ", len(photodata)
from PIL import Image

f = Image.open("photo.jpg")
f.show()

#im = Image.frombuffer(mode, size, data, "raw", mode, 0, 1)



