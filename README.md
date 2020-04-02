# NODE / Transmiter

**Requirement**
- arduino
- RadioHead
- gpsd gpsd-client gps-python
- library sudo apt-get install libgps-dev
- github https://github.com/RedBeardCode/gpsd_example

**How To Run**
- jalankan program arduino
- buat file grabserial dan jalankan file grabserial "sudo python grabserial"
- download radiohead dan edit file "RadioHead/example/raspi/rf95/rf95_client.cpp" lalu "sudo make" dan "sudo ./rf95_client"
- 

# GATEWAY

**Requirement**
- RadioHead

**How To Run**
- download radiohead dan edit file "RadioHead/example/raspi/rf95/rf95_server.cpp" lalu "sudo make" dan "sudo ./rf95_server"


ISSUE

----------------------------------------------------------
**GATEWAY ISSUE (frezzing if run rf95_server)**

Thinking about this issue some more, there is a workaround you could consider which is sacrificing all GPIO-generated interrupts. Depending on your use cases this may not be a viable option - it would break the gpio-key and gpio-shutdown overlays, for a start.

If you think this could be useful I have an overlay you to try: https://drive.google.com/open?id=1dM7FQeHod-vVR_JgwMeeitIWaqHC03wA

Copy it to /boot/overlays/gpio-no-irq.dtbo, add dtoverlay=gpio-no-irq to config.txt and reboot. You should then be able to the rpio and change the pulls to your heart's content.


**GPSD ISSUE**

- type "sudo killall gpsd"
- type "sudo nano /etc/default/gpsd" and edit file


> 

`START_DAEMON="true"`
`USBAUTO=""`
`DEVICES="/dev/ttyAMA0"`
`GPSD_OPTIONS="-F /var/run/gpsd.socket"`

- type "sudo systemctl enable gpsd.socket"
- type "sudo systemctl start gpsd.socket"
- type "sudo gpsd /dev/ttyAMA0 -F /var/run/gpsd.sock"


----------------------------------------------------------