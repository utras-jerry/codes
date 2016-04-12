from bottle import route, request, run, get
import threading
import subprocess
import serial
import time
import sys

ard = serial.Serial('/dev/ttyACM0',9600)


CODE_FILE = './code.html'
@route('/control')
def control():
    f = open(CODE_FILE, 'r')
    code = ""
    for line in f:
        code += line
    return code

@route('/control', method='POST')
def do_control():
    keyup = request.forms.get('keyUp')
    leftspeed = request.forms.get('left')
    rightspeed = request.forms.get('right')

    if leftspeed is not None:
        ard.write('l');
        ard.write(leftspeed)
        print "left"
    if rightspeed is not None:
        ard.write('r');
        ard.write(rightspeed)
    if keyup is not None:
        print "keyup: " + chr(int(keyup))
        keyup = chr(int(keyup))
        if keyup == 'W':
            print "W"
            ard.write('f');
        elif keyup == 'A':
            ard.write('a');
            print "A"
            # TODO: MOVE LEFT
            pass
        elif keyup == 'S':
            # TODO: MOVE BACKWARD
            ard.write('b')
            pass
        elif keyup == 'D':
            # TODO: MOVE RIGHT
            print "D"
            ard.write('d');
            pass
        elif keyup == "F":
            # TODO Full stop both
            print "F"
            ard.write('f');

def serialRead():
    while True:
        # print ard.readline()
        # TODO: Print this value to the web browser, Prabhat
        val = 69

def pingGoogle():
    while True:
        process = subprocess.Popen("ping -c 2 -q www.google.com > /dev/null && echo $?", stdout=subprocess.PIPE, \
                                    stderr=subprocess.STDOUT, shell=True)
        (out, err) = process.communicate()
        if out != "0\n":
            print "WHOA THERE IS NO INTERNET BRO"
        time.sleep(2)

def LOSThread():
    thread = threading.Thread(target=pingGoogle, args=())
    thread.daemon = True
    thread.start()
def AnalogInputThread():
    thread = threading.Thread(target=serialRead, args=())
    thread.daemon = True
    thread.start()

def main():
    #startWebsiteThread()
    LOSThread()
    AnalogInputThread()

    # Instead of printing read the line into a variable and display the read in line(a distance measurement) as a text box.
    run(host='localhost', port=8000)

if __name__=="__main__":
    main()
