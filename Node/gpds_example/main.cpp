/********************************************
 *  Gpsd client example
 *  created by s.farmbauer@red-beard-code.de
 ********************************************/

#include <libgpsmm.h>
#include <iostream>
#include <thread>
#include "GpsPosition.h"

//library yang ditambah
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "rs232.h"

using namespace std;

char* no = new char ();
string test;
#define BUF_SIZE 128



//Controlling the thread flow
bool gReadGps = true;



/// Thread which reads all position form the gpsd
/// server
void read_gpsd_data() {
    gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);

    if (gps_rec.stream(WATCH_ENABLE|WATCH_JSON) == NULL) {
        std::cerr << "No GPSD running.\n";
        return;
    }

    while (gReadGps) {
        struct gps_data_t *newdata;

        if (!gps_rec.waiting(50000000))
            continue;

        if ((newdata = gps_rec.read()) == NULL) {
            std::cerr << "Read error.\n";
            return;
        } else {
            GPSPosition dummy(newdata);

        }
    }
        
}

///Starts the thread which reads the position and stores
///it in a Contaier
int main(void)
{
	ifstream sensorData;
	string sensorDataTmp;
	string sensorDataLine;
	sensorData.open("/home/pi/sensor.txt");
	
	std::thread gps_thread(read_gpsd_data);
                  
	while (getline(sensorData, sensorDataTmp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		GPSPosition last_pos = GPSPosition::get_last_3d_fix_value();
		
		std::cout << " Lat: " << last_pos.get_latitude()
                  << " Lon: " << last_pos.get_longitude()
                  << " Alt: " << last_pos.get_altitude()
                  << " Data: " << sensorDataTmp << endl;
		usleep(1000000);
	}
	
	sensorData.clear();
	
	gReadGps = false;
    gps_thread.join();
    return 0;
}
