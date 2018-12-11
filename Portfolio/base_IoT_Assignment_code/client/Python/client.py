#Base Python client for MEng in IoT Assignment
#consumes data from IoT Gateway
import urllib.request
import xml.etree.ElementTree as ET
import numpy as np
import matplotlib.pyplot as plt

response = urllib.request.urlopen('http://localhost:8080/')
resp = response.read()
root = ET.fromstring(resp)
timelist = []
templist = []
for reading in root.findall('reading'):
    time = reading.find('time').text
    timelist.append(time[time.find(' '):])
    templist.append(int(reading.find('temperature').text))
print(templist)
t1 = np.arange(0.0, 5.0, 1)
t2 = [11,17,24,10,19]
plt.figure('Temperature Graph')
plt.xlabel("time")
plt.ylabel("temperature")
plt.plot(timelist, templist,'bo',timelist, templist,'k')
plt.show()
