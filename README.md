# NODE / Transmiter

**Requirement**
- arduino
- RadioHead : https://github.com/hallard/RadioHead
- gpsd_example : https://github.com/RedBeardCode/gpsd_example
- gpsd gpsd-client gps-python
- library sudo apt-get install libgps-dev

**How To Install**
- jalankan program arduino
- buat file grabserial dan paste code dari folder node
- download gpsd example dan edit main.cpp lalu sudo make
- download radiohead dan edit file RadioHead/example/raspi/rf95/rf95_client.cpp lalu sudo make

**How To Run**
- Grabserial
```bash
pi@raspberrypi:~ $ sudo python grabserial
```
- GPSD
```bash
pi@raspberrypi:~/gpsd_example $ sudo gpsd /dev/ttyAMA0 -F /var/run/gpsd.sock
pi@raspberrypi:~/gpsd_example $ sudo ./gpsd_example
```
- RadioHead
```bash
pi@raspberrypi:~/RadioHead/example/raspi/rf95 $ sudo ./rf95_client
```

# GATEWAY

**Requirement**
- RadioHead

**How To Run**
- RadioHead
```bash
pi@raspberrypi:~/RadioHead/example/raspi/rf95 $ sudo ./rf95_server
```
- Python Firebase
```bash
pi@raspberrypi:~/pythonFirebase $ sudo python main.py
```


# FIX ISSUE

----------------------------------------------------------
**GATEWAY ISSUE (frezzing if run rf95_server)**

Thinking about this issue some more, there is a workaround you could consider which is sacrificing all GPIO-generated interrupts. Depending on your use cases this may not be a viable option - it would break the gpio-key and gpio-shutdown overlays, for a start.

If you think this could be useful I have an overlay you to try: https://drive.google.com/open?id=1dM7FQeHod-vVR_JgwMeeitIWaqHC03wA

Copy it to /boot/overlays/gpio-no-irq.dtbo, add dtoverlay=gpio-no-irq to config.txt and reboot. You should then be able to the rpio and change the pulls to your heart's content.


**GPSD ISSUE**

- type "sudo killall gpsd"
- type "sudo nano /etc/default/gpsd" and edit file


```
START_DAEMON="true
GPSD_OPTIONS="-F /var/run/gpsd.socket
USBAUTO=""
DEVICES="/dev/ttyAMA0
```

- type "sudo systemctl enable gpsd.socket"
- type "sudo systemctl start gpsd.socket"
- type "sudo gpsd /dev/ttyAMA0 -F /var/run/gpsd.sock"


**FIX ARDUINO SOFTWARE CANT OPEN**

- open C:\Users\{username}\AppData\Local\Arduino15
- delete any files named package_index.json, package_index.json.sig, and package_index.json.sig.tmp
- run arduino_debug.exe from cmd


----------------------------------------------------------