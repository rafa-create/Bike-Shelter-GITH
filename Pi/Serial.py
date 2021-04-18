import serial, sys
from xbee import XBee
import requests

Ap=0

SERIALPORT = "/dev/ttyUSB0"
BAUDRATE=57600

ser  = serial.Serial(SERIALPORT, BAUDRATE)

while True:
    data=ser.readline()
    print (data)
    if Ap<= 0:
        Ap=0
    if data==b'Student card:  Yes, so registred a this lock\r\n':
        if Ap!= 0:
            Ap-=1
        url = 'http://172.20.10.3/api.php?Aplaces='+str(Ap)
        auth_token='jadorelevelo'
        payload={}
        headers = {'Authorization': 'Bearer ' + auth_token}
        response = requests.request('GET', url, headers=headers, data=payload)
        print(response.status_code)
    if data==b'Do you have a bike locked ? Yes, so lock ejected\r\n':
        if Ap<= 0:
            Ap=0
        Ap+=1
        url = 'http://172.20.10.3/api.php?Aplaces='+str(Ap)
        auth_token='jadorelevelo'
        payload={}
        headers = {'Authorization': 'Bearer ' + auth_token}
        response = requests.request('GET', url, headers=headers, data=payload)
        print(response.status_code)

