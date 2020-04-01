# NODE / Transmiter

**Requirement**
- arduino
- RadioHead

**How To Run**
- jalankan program arduino
- buat file grabserial dan jalankan file grabserial "sudo python grabserial"
- download radiohead dan edit file "RadioHead/example/raspi/rf95/rf95_client.cpp" lalu "sudo make" dan "sudo ./rf95_client"

# GATEWAY

**Requirement**
- RadioHead

**How To Run**
- download radiohead dan edit file "RadioHead/example/raspi/rf95/rf95_server.cpp" lalu "sudo make" dan "sudo ./rf95_server"


ISSUE

----------------------------------------------------------
GATEWAY ISSUE (frezzing if run rf95_server)

Thinking about this issue some more, there is a workaround you could consider which is sacrificing all GPIO-generated interrupts. Depending on your use cases this may not be a viable option - it would break the gpio-key and gpio-shutdown overlays, for a start.

If you think this could be useful I have an overlay you to try: https://drive.google.com/open?id=1dM7FQeHod-vVR_JgwMeeitIWaqHC03wA

Copy it to /boot/overlays/gpio-no-irq.dtbo, add dtoverlay=gpio-no-irq to config.txt and reboot. You should then be able to the rpio and change the pulls to your heart's content.

----------------------------------------------------------