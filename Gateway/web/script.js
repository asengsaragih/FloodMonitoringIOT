//---------firebase configuration-------------
var firebaseConfig = {
    apiKey: "AIzaSyC8UqvGD58zWI8MFs4YYtewXx4Tc4XmJDs",
    authDomain: "flood-monitoring-cba07.firebaseapp.com",
    databaseURL: "https://flood-monitoring-cba07.firebaseio.com",
    projectId: "flood-monitoring-cba07",
    storageBucket: "flood-monitoring-cba07.appspot.com",
    messagingSenderId: "361544530399",
    appId: "1:361544530399:web:0906dd4318fc449a546c6a",
    measurementId: "G-5FC6Y6LDFT"
};

firebase.initializeApp(firebaseConfig);
firebase.analytics();

const database = firebase.database();
//-----------------------------------------------

// set waktu untuk setiap pengambilan datanya. default nya 15 menit
// const TIMEOUT_TIME = 15 * MINUTES;
const MINUTES = 60000;
const TIMEOUT_TIME = 10000;

function getLog() {
    $.ajax({
        url: 'data.txt',
        dataType: 'text',
        success: function(text) {
            $("#tmpdata").text(text);
            $("#timeDisplay").text("Jeda data baru : " + Number(TIMEOUT_TIME / 60000) + " Menit");
            sendData(text);
            // setTimeout(getLog, TIMEOUT_TIME); // refresh every 30 seconds
        }
    })
}

function sendData(textValue) {
    var splitText = textValue.split("|");

    var rawTime = splitText[0];
    var rawLat = splitText[1];
    var rawLon = splitText[2];
    var rawAlt = splitText[3];
    var rawData = splitText[4];
    var rawId = splitText[5];

    //pemecahan variable bercanbang
    var replaceDateTime = rawTime.replace(" Time: ", "");
    var replaceWaterData = rawData.replace(" Data: ", "");
    var splitDataTime = replaceDateTime.split(" ");
    var splitWaterData = replaceWaterData.split(",");

    //untuk marker
    var idMarker = rawId.replace(" Id: ", "");
    var latitude = rawLat.replace(" Lat: ", "");
    var longitude = rawLon.replace(" Lon: ", "");
    var altitude = rawAlt.replace(" Alt: ", "");

    //untuk child marker
    var debit = splitWaterData[0];
    var level = splitWaterData[1];
    var category = splitWaterData[2];
    var miliestime = "-" + Math.round((new Date()).getTime() / 1000);
    var date = correctionDate(splitDataTime[0]);
    var time = splitDataTime[1];

    // addingRecentData(idMarker, category, date, debit, level, miliestime, time);

    database.ref("Marker/" + idMarker).on("value", function (snapshot) {
        var val = snapshot.val();

        if (latitude != val.latitude || longitude != val.longitude || altitude != val.alt) {
            updateMarker(idMarker, latitude, longitude, altitude);
        }
    });

    var push = database.ref("Marker/" + idMarker + "/recent/").push();
    var waterData = {
        category: parseInt(category),
        date: date,
        debit: debit + " L/m",
        level: level + " cm",
        miliestime: miliestime,
        status: 1,
        time: time,
    };
    push.set(waterData);
}

function correctionDate(rawData) {
    var splitdata = rawData.split("/");
    var rawMonth = splitdata[1];
    var month = "";

    if (rawMonth == "01") {
        month = "Januari"
    } else if (rawMonth == "02") {
        month = "Februari"
    } else if (rawMonth == "03") {
        month = "Maret"
    } else if (rawMonth == "04") {
        month = "April"
    } else if (rawMonth == "05") {
        month = "Mei"
    } else if (rawMonth == "06") {
        month = "Juni"
    } else if (rawMonth == "07") {
        month = "Juli"
    } else if (rawMonth == "08") {
        month = "Agustus"
    } else if (rawMonth == "09") {
        month = "September"
    } else if (rawMonth == "10") {
        month = "Oktober"
    } else if (rawMonth == "11") {
        month = "November"
    } else {
        month = "Desember";
    }

    var date = splitdata[0] + " " + month + " " + "20" + splitdata[2];
    return date;
}

function updateMarker(key, latitude, longitude, altitude) {
    var update = {
        latitude : Number(latitude),
        longitude : Number(longitude),
        alt : Number(altitude),
    };
    database.ref('Marker/' + key).update(update);
}

function addingRecentData(idMarker, category, date, debit, level, miliestime, time) {
    var push = database.ref("Marker/" + idMarker + "/recent/").push();
    var waterData = {
        category: parseInt(category),
        date: date,
        debit: debit + " L/m",
        level: level + " cm",
        miliestime: miliestime,
        status: 1,
        time: time,
    };
    push.set(waterData);
}