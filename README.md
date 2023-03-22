# Esp8266-ThingsBoard-LED
Turn Led On and Off using ThingsBoard

<h3>Requirements:</h3>
1 esp8266
1 LED
Jumper wires

<h3>Procedure</h3>

1)First,connect the board with the following schema:

      esp8266 GND ----> LED Cathode

      esp8266 D1 ----> LED Anode

2)Then,download and run the LEDcontrol.ino file. In the file, change your ssid,password.


3)Then, go to https://demo.thingsboard.io/ and sign in to your account.

      Go to devices and create a new device with any name and click add.
      
      Here, you need to configure the device to your application by clicking on manage credentials and copying the access token and pasting it into the  ACCESS_TOKEN variable defined in the LEDcontrol.ino file.
      
      Go to dashboards and import light_control.json file.
      
      In the dashboard, change the alias to the device you just created.

4)Now, upload your code to esp8266 and control the LED from your ThingsBoard dashboard.

