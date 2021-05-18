import requests

Ap=10
url = 'http://localhost/api.php?Aplaces='+str(Ap)
payload={}
headers = {
  'Authorization': 'Bearer jadorelevelo'
}

response = requests.request("GET", url, headers=headers, data=payload)

#print(response.status_code)
print(response.text)