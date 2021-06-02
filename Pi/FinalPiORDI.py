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
        print("Pas de check de CSN effectué")
        return True
def update_fichier_et_online(Ap):
    try :
        f = open("C:/Users/Rafael/Documents/Cours/UE proj+com+manag/Projet 1A 60%/Bike-Shelter-GITH/Pi/App.txt","w")
        f.write(str(Ap))
        f.close()
        url = 'http://localhost/api.php?Aplaces='+str(Ap)
        payload={}
        headers = {
  'Authorization': 'Bearer jadorelevelo'
}
        response = requests.request("GET", url, headers=headers, data=payload)
        #print(response.status_code)
        print(response.text)
    except requests.exceptions.RequestException as e :
        #ConnectionError
        print("Mise en ligne non effectuée")
def recup_App():
    global Ap
    f = open('C:/Users/Rafael/Documents/Cours/UE proj+com+manag/Projet 1A 60%/Bike-Shelter-GITH/Pi/App.txt','r')
    Ap = f.read()
    Ap=int(str(Ap))
    f.close()
    if Ap<0:
        Ap=0

def check_csn_liste(CSN):
    global cartes
    cartes='C:/Users/Rafael/Documents/Cours/UE proj+com+manag/Projet 1A 60%/Bike-Shelter-GITH/Pi/cartes.txt'
    CSN=str(CSN)
    with open(cartes, "r") as f:
        lines = f.readlines()
        f.close()
    for line in lines:
        if line.strip("\n") == CSN:
            f.close()
            return True
    return False

def sup_csn_liste(CSN):

    CSN=str(CSN)
    with open(cartes, "r") as f:
        lines = f.readlines()
        f.close()
    with open(cartes, "w") as f:
        for line in lines:
            if line=='\n':
                None
            else:
                if line.strip("\n") != CSN:
                    f.write(line)
            #else:
                #return("CSN supprimé")
        #return ("Pas le CSN")#arrive pas là normalement
        f.close()
def ajouter_csn(CSN):
    f = open(cartes,"a+")
    f.write("\n")
    f.write(str(CSN))
    f.close()

def garer(CSN):
    global Ap
    if UL_Card(CSN) and not check_csn_liste(CSN):
        recup_App()
        Ap-=1
        update_fichier_et_online(Ap)
        ajouter_csn(CSN)
        print ("Place prise")
    else:
        print("Peut pas garer")

def prendre(CSN):
    global Ap
    if check_csn_liste(CSN):
        recup_App()
        Ap+=1
        update_fichier_et_online(Ap)
        sup_csn_liste(CSN)
        print ("Place libérée")
    else:
        print ("pas de vélo garé")

def conv(data):
    #surement prendre les 20 premier caractéres pour le CSN et reste pour le msg
    CSN="04 4C 40 B2 61 67 80"
    return CSN,data,place

"04 43 59 B2 61 67 80"
"04 4C 40 B2 61 67 80"
"04 33 5B B2 7A 57 80"

while True:
    msg=ser.readline()
    print(CSN)
    if msg==b'Carte UL et pas CSN courant ?\r\n':
        CSN=ser.readline()
        check_csn_liste(CSN) and UL_Card(CSN)#ser.write?
    if data==b'Velo gare !\r\n':
        CSN=ser.readline()
        garer(CSN)
    if msg==b'CSN courant ?\r\n':
        check_csn_liste(CSN)
    if msg==b'Velo pris !\r\n':
        CSN=ser.readline()
        prendre(CSN)


