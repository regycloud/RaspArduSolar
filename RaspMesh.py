from __future__ import print_function
from RF24 import *
from RF24Network import *
from RF24Mesh import *
from struct import *
import time
import pymysql
import ctypes
import struct
from datetime import date, datetime

#database stuffs
db = pymysql.connect("localhost","root","jkregy","coba")
cursor = db.cursor()
today = datetime.now().strftime("%Y-%m-%d %H:%M:%S")



# radio setup for RPi B Rev2: CS0=Pin 24
radio = RF24(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ)
network = RF24Network(radio)
mesh = RF24Mesh(radio, network)

mesh.setNodeID(0)
mesh.begin(76,RF24_250KBPS)
radio.setPALevel(RF24_PA_MAX) # Power Amplifier
radio.printDetails()
hdr, g = network.read(9)

while 1:
     mesh.DHCP()
     mesh.update()

     while network.available():
          header, N = network.read(9)
          ms, number = unpack('hh',bytes(N))
          print('P=', ms/100, 'Node :', abs(mesh.getNodeID(header.from_node)), '\n')
          cursor.execute("INSERT into sensor (id,nilai) values (%s,%s)", [abs(mesh.getNodeID(header.from_node)),format(ms/100)])
          db.commit()


