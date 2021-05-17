import requests

csn="044C40B2616780"
url = "https://api-public.univ-lorraine.fr/annuaire/cards/check/"+str(csn)

payload={}
headers = {
  'X-Gravitee-Api-Key': 'd8cf4b89-af20-4aeb-a143-4898bdd9f4a2',
  'id': 'd8cf4b89af204aeba1434898bdd9f4a2'
}

response = requests.request("GET", url, headers=headers, data=payload)

print(response.text)
