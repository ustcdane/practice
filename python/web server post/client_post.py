#coding=utf-8
import requests
import json
IP="10.162.41.48"
url = "http://" + IP + ":8080"

data_ = ur"Your Data ......."

dd = {'PersonalData': data_}
data_json = json.dumps(dd)
r = requests.post(url, data_json)
print (r.url)
print (r.text)
