import serial
ser = serial.Serial("/dev/ttyACM0", 9600)
file = open("sensorData.txt", "w")

while True:
    data = str(ser.readline())
    print(data[2:][:-5])
    file.write(data[2:][:-5] + '\n')
    file.flush()