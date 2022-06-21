import RPi.GPIO as GPIO
import socket
import csv

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(33,GPIO.OUT)
GPIO.setup(11,GPIO.OUT)
GPIO.setup(13,GPIO.OUT)
GPIO.setup(15,GPIO.OUT)
GPIO.setup(29,GPIO.OUT)
GPIO.setup(31,GPIO.OUT)

GPIO.output(31,True)

UDP_IP = "0.0.0.0"
UDP_PORT = 6661

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
	data, addr = sock.recvfrom(1024)
	raw=data
	print "Received Data: ", raw
        status, action = data.split(',')
        print "Status: ", status
        print "Action: ", action

	if status=="1":
		print "LED ON"
		GPIO.output(31,True)
	else:
		print "LED OFF"
		GPIO.output(31,False)


	if action==" F":
		GPIO.output(33,True)
		GPIO.output(11,False)
		GPIO.output(13,True)
		GPIO.output(15,False)
		print "Robot Move Forward"
  
  
	elif action==" 0":
		GPIO.output(33,False)
		GPIO.output(11,False)
		GPIO.output(13,False)
		GPIO.output(15,False)
		print "Robot Stop"
 

	elif action==" B":
		GPIO.output(33,False)
		GPIO.output(11,True)
		GPIO.output(13,False)
		GPIO.output(15,True)
		print "Robot Move Backward"

	elif action==" L":
		GPIO.output(33,False)
		GPIO.output(11,True)
		GPIO.output(13,True)
		GPIO.output(15,False)
		print "Robot Move Left"

	elif action==" R":
		GPIO.output(33,True)
		GPIO.output(11,False)
		GPIO.output(13,False)
		GPIO.output(15,True)
		print "Robot Move Right"


	else:
		print "STOP"
		GPIO.output(33,False)
		GPIO.output(11,False)
		GPIO.output(13,False)
		GPIO.output(15,False)
