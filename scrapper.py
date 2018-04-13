"""
Regularly poll ETA data until 4pm
"""

import threading
import urllib.request
from time import gmtime, strftime
import json
import datetime
import sched, time

interval = 60 * 3 # 3 minutes
queryUrl = "https://nextbus.comfortdelgro.com.sg/eventservice.svc/Shuttleservice?busstopname="

A1_stops = ['LT13', 'COM2', 'KR-MRT', 'LT29', 'UHALL', 'PGP12-OPP', 'CENLIB', 'STAFFCLUB-OPP', 
            'AS7', 'YIH', 'BIZ2', 'PGP7', 'PGPT']

def queryAndWriteToRow(busstop):
    currTime = datetime.datetime.now()
    time = currTime.strftime("%Y-%m-%d %H:%M:%S")
    data = {}
    try:
        data = urllib.request.urlopen(queryUrl+busstop).read()
        data = json.loads(data)
    except Exception:
        print("[-] Network error")
        pass
    columns = ['time','busstop','nextArrivalTime','nextPassengers','passengers']
    dataColumns = ['nextArrivalTime','nextPassengers','passengers']
    row = {}
    row['time'] = time
    row['busstop'] = busstop
    try:
        data = data['ShuttleServiceResult']['shuttles']
        data = [item for item in data if item['name']=='A1'][0]
        for name in dataColumns:
            row[name] = data[name]
    except (IndexError, KeyError) as e:
        for name in dataColumns:
            row[name] = 'null'
    result = ','.join([row[c] for c in columns])
    return result

# timestr = strftime("%Y-%m-%d %H:%M:%S", gmtime())
# row = queryAndWriteToRow(timestr, 'LT13')
# print(row)

startTime = datetime.datetime(2018, 4, 9, 7, 30, 00)
endTime = datetime.datetime(2018, 4, 9, 17, 30, 00)

file = open("eta.csv", "a")
s = sched.scheduler(time.time, time.sleep)

def run():
    for stop in A1_stops:
        row = queryAndWriteToRow(stop)
        # not sure if need to add new line
        file.write(row+'\n')
    currTime = datetime.datetime.now()
    print("[+] Completed write cycle at", currTime.strftime("%Y-%m-%d %H:%M:%S"))
    if currTime < endTime:
        s.enter(interval, 1, run)
        s.run()
run()
print("[+] Done")
