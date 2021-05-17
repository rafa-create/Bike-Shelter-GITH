import requests
CSN="04 43 59 B2 61 67 80"
CSN = ''.join(CSN.split())
#Carte UL active 200 :04 4C 40 B2 61 67 80
#Carte non trouvée 404 :044C40B26167801
#Paramètre erroné 400: 044C40B26167801q
url = "https://api-public.univ-lorraine.fr/annuaire/cards/check/"+str(CSN)
payload={}
headers = {
  'X-Gravitee-Api-Key': 'd8cf4b89-af20-4aeb-a143-4898bdd9f4a2',
  'id': 'd8cf4b89af204aeba1434898bdd9f4a2'
}
response = requests.request("GET", url, headers=headers, data=payload)
print(response.status_code)
#print(response.text)