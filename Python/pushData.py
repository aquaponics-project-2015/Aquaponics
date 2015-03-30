import serial
import sys

ser = serial.Serial('COM4', 9600, timeout = 0)

def main():
    while True:
        while(ser.inWaiting() == 0):
            pass
        
        val = getValue()
        print val

def getValue():
    val = ''
    this = True
    while this:
        byte = ser.read()
        if byte == '\r':
            this = False
        if (byte != '\r') and (byte != '\n'):
            val+=(byte)
    return val

main()
