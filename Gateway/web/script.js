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


function testLog() {
    $.ajax({
        url: 'data.txt',
        dataType: 'text',
        success: function(text) {
            $("#tmpdata").text(text);
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

    console.log(miliestime);
}

testLog();


// function getLog() {
//     $.ajax({
//         url: 'data.txt',
//         dataType: 'text',
//         success: function(text) {
//             $("#tmpdata").text(text);
//             console.log(text);
//             setTimeout(getLog, TIMEOUT_TIME); // refresh every 30 seconds
//         }
//     })
// }

// getLog();