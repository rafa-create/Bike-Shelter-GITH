import requests

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

recup_App()
update_fichier_et_online(Ap)
