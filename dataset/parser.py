import requests
import json
from PIL import Image
import time

counter = 0

with open('./dataset/photos_test_dataset.json') as f:
    places = json.load(f)

for place in places:
    for links_list in list(json.loads(place['photos']).values()):
        for link in links_list:
            counter += 1
            try:
                img = Image.open(requests.get(link, stream=True).raw)
                img.save(f'./dataset/photos/photo{counter}.jpg')
                # time.sleep(1)
            except Exception as e:
                print("too bad\n", e)
