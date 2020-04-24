"""
Syarat Penginstalan

$ sudo pip install requests==1.2
$ sudo pip install python-firebase
$ sudo pip install requests --upgrade

"""

from firebase import firebase
import time

# konfigurasi firebase
firebase = firebase.FirebaseApplication('https://flood-monitoring-cba07.firebaseio.com/', None)

MINUTES = 60
TIMEOUT_TIME = MINUTES * 30

def SPLIT_RAW_DATA(val):
    return val.read().split("|")

def CORRECTION_DATE(val):
    splitdata = val.split("/")
    rawMonth = splitdata[1]
    month = ""

    if rawMonth == "01":
        month = "Januari"
    elif rawMonth == "02":
        month = "Februari"
    elif rawMonth == "03":
        month = "Maret"
    elif rawMonth == "04":
        month = "April"
    elif rawMonth == "05":
        month = "Mei"
    elif rawMonth == "06":
        month = "Juni"
    elif rawMonth == "07":
        month = "Juli"
    elif rawMonth == "08":
        month = "Agustus"
    elif rawMonth == "09":
        month = "September"
    elif rawMonth == "10":
        month = "Oktober"
    elif rawMonth == "11":
        month = "November"
    else:
        month = "Desember"

    return splitdata[0] + " " + month + " " + "20" + splitdata[2]

def GET_MILIESTIME():
    return "-" + str(int(round(time.time() * 1000)))

while True:
    rawTime = SPLIT_RAW_DATA(open("/home/pi/data.txt", "r"))[0]
    rawLat = SPLIT_RAW_DATA(open("/home/pi/data.txt", "r"))[1]
    rawLon = SPLIT_RAW_DATA(open("/home/pi/data.txt", "r"))[2]
    rawAlt = SPLIT_RAW_DATA(open("/home/pi/data.txt", "r"))[3]
    rawData = SPLIT_RAW_DATA(open("/home/pi/data.txt", "r"))[4]
    rawId = SPLIT_RAW_DATA(open("/home/pi/data.txt", "r"))[5]

    # pemecahan variable bercabang
    replaceDateTime = rawTime.replace(" Time: ", "")
    replaceWaterData = rawData.replace(" Data: ", "")
    splitDataTime = replaceDateTime.split(" ")
    splitWaterData = replaceWaterData.split(",")

    # untuk marker
    idMarkerRaw = rawId.replace(" Id: ", "")
    idMarker = idMarkerRaw.rstrip('\n')
    latitude = rawLat.replace(" Lat: ", "")
    longitude = rawLon.replace(" Lon: ", "")
    altitude = rawAlt.replace(" Alt: ", "")

    # untuk child marker
    debit = splitWaterData[0]
    level = splitWaterData[1]
    category = splitWaterData[2]
    miliestime = GET_MILIESTIME()
    date = CORRECTION_DATE(splitDataTime[0])
    timee = splitDataTime[1]

    try:
        firebaseResult = firebase.get('/Marker/' + idMarker, '')

        databaseLatitude = firebaseResult['latitude']
        databaseLongitude = firebaseResult['longitude']

        if str(latitude) != str(databaseLatitude):
            firebase.put('/Marker/' + idMarker, 'latitude', float(latitude))
            firebase.put('/Marker/' + idMarker, 'longitude', float(longitude))
            print("Lokasi marker diperbaruhi")

        pushRecent = {
            'category': int(category),
            'date': date,
            'debit': debit + " L/m",
            'level': level + " cm",
            'miliestime': miliestime,
            'status': 1,
            'time': timee
        }

        try:
            firebase.post('/Marker/' + idMarker + '/recent/', pushRecent)
            print("Data baru ditambahkan")
            print("Tanggal : " + str(date) + " " + str(timee))
            print("Debit : " + str(debit))
            print("Level : " + str(level))
            print("Kategori : " + str(category))
            print("")
        except:
            print("Error insert new data")
    except:
        print("Error getting database")

    time.sleep(TIMEOUT_TIME)
