import requests

# GET json data
response = requests.get("http://localhost:8080/countries")

print(response.status_code)
print(response.json())

# POST json data
json_data = {"id": 3, "name": "Egypt", "capital": "Cairo", "area": 1010408}
response = requests.post("localhost/countries", json_data)
print(response.status_code)
print(response.json())
