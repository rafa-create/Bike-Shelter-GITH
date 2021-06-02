import requests
import serial, sys
from xbee import XBee
SERIALPORT = "/dev/ttyUSB0"
BAUDRATE=57600
ser  = serial.Serial(SERIALPORT, BAUDRATE)

def UL_Card(CSN):#en str
    try:
        CSN = ''.join(CSN.split())
        url = "https://api-public.univ-lorraine.fr/annuaire/cards/check/"+CSN
        payload={}
        headers = {
  'X-Gravitee-Api-Key': 'd8cf4b89-af20-4aeb-a143-4898bdd9f4a2',
  'id': 'd8cf4b89af204aeba1434898bdd9f4a2'
}
        response = requests.request("GET", url, headers=headers, data=payload)
        return response.status_code==200
    except requests.exceptions.RequestException as e :
        print("Pas de check de CSN effectu�")
        return True
def update_fichier_et_online(Ap):
    try :
        f = open("/home/pi/Desktop/App.txt","w")
        f.write(str(Ap))
        f.close()
        url = url = 'http://172.20.10.3/api.php?Aplaces='+str(Ap)
        payload={}
        headers = {
  'Authorization': 'Bearer jadorelevelo'
}
        response = requests.request("GET", url, headers=headers, data=payload)
        #print(response.status_code)
        print(response.text)
    except requests.exceptions.RequestException as e :
        #ConnectionError
        print("Mise en ligne non effectu�e")
def recup_App():
    global Ap
    f = open('/home/pi/Desktop/App.txt','r')
    Ap = f.read()
    Ap=int(str(Ap))
    f.close()
    

def check_csn_liste(CSN):
    CSN=str(CSN)
    with open('/home/pi/Desktop/cartes.txt', "r") as f:
        lines = f.readlines()
        f.close()
    for line in lines:
        if line.strip("\n") == CSN:
            f.close()
            return True
    return False

def sup_csn_liste(CSN):
    CSN=str(CSN)
    with open('/home/pi/Desktop/cartes.txt', "r") as f:
        lines = f.readlines()
        f.close()
    with open('/home/pi/Desktop/cartes.txt', "w") as f:
        for line in lines:
            if line=='\n':
                None
            else:
                if line.strip("\n") != CSN:
                    f.write(line)
                    break
            #else:
                #return("CSN supprim�")
        #return ("Pas le CSN")#arrive pas l� normalement
        f.close()
def ajouter_csn(CSN):
    f = open('/home/pi/Desktop/cartes.txt',"a+")
    f.write("\n")
    f.write(str(CSN))
    f.close()

def garer(CSN):
    global Ap
    if True :
        recup_App()
        Ap-=1
        if Ap<0:
            Ap=0
        update_fichier_et_online(Ap)
        ajouter_csn(CSN)
        print ("Place prise")
    else:
        print("Peut pas garer")

def prendre(CSN):
    global Ap
    if True:
        recup_App()
        Ap+=1
        if Ap>4:
            Ap=4
        update_fichier_et_online(Ap)
        sup_csn_liste(CSN)
        print ("Place lib�r�e")
    else:
        print ("pas de v�lo gar�")

def conv(CSN):
    #surement prendre les 20 premier caract�res pour le CSN et reste pour le msg 
    CSN=str(CSN,'utf-8')
    CSN=CSN.rstrip()
    return CSN

while True:
    msg=ser.readline()
    print(msg)
    if msg==b'Velo gare !\r\n':
        CSN=conv(ser.readline())
        garer(CSN)
    if msg==b'Velo pris !\r\n':
        CSN=conv(ser.readline())
        prendre(CSN)
        

