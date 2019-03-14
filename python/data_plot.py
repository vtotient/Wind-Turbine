##This is the working copy that plots in real time. Fixed the delay issue

import serial
import serial.tools.list_ports
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import sys, time, math
import csv
from datetime import datetime as dt

PORT = '/dev/tty.usbmodem14101'

try:
 ser.close();
except:
 print();
try:
 ser = serial.Serial(PORT, 9600, timeout=100)
 print(ser.get_settings())
except:
 print ('Serial port %s is not available' % PORT);
 portlist=list(serial.tools.list_ports.comports())
 print('Trying with port %s' % portlist[0][0]);
 ser = serial.Serial(portlist[0][0], 9600, timeout=100)
ser.isOpen()

xsize=100
   
def data_gen():
    t = data_gen.t
 
    x = 0
    while True:
        t+=1
        strin = ser.readline()
        val   = int(strin)

        # with open('c6rpas_output_voltage.csv', mode='w') as output_voltage:
        #     voltage_writer = csv.writer(output_voltage, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

        #     voltage_writer.writerow(['%f', '%f', dt.utcnow(), val])
        
        x = x + 1
        y = 0
        while (y < 20) :
            y = y + 1

        print('Data = %d\r'%(val))
        #time.sleep(0.2) # change to 100ms
        yield t, val

def run(data):
    # update the data
    t,y = data
    if t>-1:
        xdata.append(t)
        ydata.append(y)
        if t>2000: # Scroll to the left.	#change xsize to 2000
            ax.set_xlim(t-2000, t)		
        line.set_data(xdata, ydata)

    return line,

def on_close_figure(event):
    sys.exit(0)

data_gen.t = -1
fig = plt.figure()
fig.canvas.mpl_connect('close_event', on_close_figure)
ax = fig.add_subplot(111)
line, = ax.plot([], [], lw=2)
ax.set_ylim(-5, 110)
ax.set_xlim(0, 2000)	#changed from xsize
ax.grid()
xdata, ydata = [], []

# Important: Although blit=True makes graphing faster, we need blit=False to prevent
# spurious lines to appear when resizing the stripchart.
ani = animation.FuncAnimation(fig, run, data_gen, blit=False, interval=100, repeat=False)
plt.show()
