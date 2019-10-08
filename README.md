# LoRaWAN&reg; Weather Station example using SAM R34 Xplained Pro

### Introduction
LoRa stands for Long Range. LoRaWAN stands for Long Range Wide Area Networks. LoRaWAN is the network on which LoRa operates. LoRaWAN is a media access control (MAC) layer protocol but mainly is a network layer protocol for managing communication between LPWAN gateways and end-node devices as a routing protocol, maintained by the LoRa Alliance. Some of the applications that can be accomplished using LoRa are Smart parking and vehicle management, Facilities and infrastructure management, Fire detection and management, Waste management, Home automation for IoT enables smart appliances, Smart farming and livestock management, Temperature and moisture monitoring, Water level sensors and irrigation control.

### Advantages of using LoRaWAN
- Long battery life due to low power consumption
- Low cost implementation due to low cost hardware and unlicensed spectrum
- Long range coverage and in-building penetration
- Secure Network
- Scalable network to support future upgrades
- Ease of access and connectivity to the cloud applications
- Remote management and control access

### Features of demo example

- Capture Weather Station sensor data (Humidity, Temperature, Rain, Wind, Luminosity  etc.,) 
- Send the captured data using wireless protocol LoRaWAN
- Low Power Sleep after Sensor Data is sent
- Integration to LoRaWAN Application Server like [Cayenne](https://mydevices.com/ "Cayenne")
- Monitor and Analyze days of sensor data on a dashboard
- Low Power Modes - Standby and Backup, Experience the powerful, yet low power wireless SIP - [SAMR34](https://www.microchip.com/design-centers/wireless-connectivity/low-power-wide-area-networks/lora-technology/sam-r34-r35 "SAMR34") 

### Hardware 

- [SAM R34 Xplained Pro ](https://www.microchip.com/DevelopmentTools/ProductDetails/dm320111 "SAM R34 Xplained Pro ")(Qty: 1)
- MISOL Weather Station  (Amazon - [Link](https://www.amazon.com/MISOL-weather-station-interface-length/dp/B0722KB1KB "Link")) (Ebay - [Link](https://www.ebay.com/itm/weather-station-with-RS485-interface-with-cable-length-3-2-meter-/272647276759 "Link"))
- [Sparkfun Transceiver Breakout Board](https://www.sparkfun.com/products/10124 "Sparkfun Transceiver Breakout Board")
- Micro USB
- US902 - LoRaWAN Gateway (that connects to The Things Network Server)  - [link](https://www.thethingsnetwork.org/docs/gateways/ "link")
- Internet Connectivity
- M to M Jumper Wires and M to F Jumper Wires

### Hardware Setup (Important !!!)
1. Remove the USB adapter from RS485 to USB adapter that comes with the weather station
2.  Solder A and B signals coming from Weather Station to A and B plated holes on the RS485 connector
3.  Short 3-5 V signal on RS485 break out board to B on RS485 break out board and connect 3-5 V signal to VCC of the SAM R34 Xplained Pro
4.  Connect "RTS" of the RS485 break out board to GND signal of SAM R34 Xplained Pro
5. Connect "TX-O" of the RS485 break out board to PA05 of SAM R34 Xplained Pro
For refernce picture of the RS485 board denoting signals 
![](https://i.imgur.com/Yh4pGJb.png)
6. Connect the SAM R34 Xplained Pro to PC via EDBG USB port
7. Power On the Weather Station using 3 AA batteries 

### Software
- OS - Windows 7 and above
- Atmel Studio 7 and above

### LoRaWAN Gateway, End Device Registration and Application Integration 

- Sign up for a [free account ](https://account.thethingsnetwork.org/users/login "free account ")
- Steps to [register](https://www.thethingsnetwork.org/docs/gateways/ "register") your Gateway to The Things Network 
- Create an [Application](https://www.thethingsnetwork.org/docs/applications/add.html "Application") in The Things Network Console
- [Register](https://www.thethingsnetwork.org/docs/devices/registration.html "Register") (Device Registration) your End Device to the Application Created
- Add Cayenne "mydevices" as application integrations on The Things Network Console with Access key as "default key"
![](https://i.imgur.com/0lBF9xO.png)
- [Set up](https://www.thethingsnetwork.org/docs/applications/cayenne/ "Set up") your myDevices Account
- sign up for a cayenne my devices account 
 - upon signup, go to Add New --> Device/Widget
![](https://i.imgur.com/RWZTjUs.png)
- Click on LoRa and select "The Things Network" Server 
 ![](https://i.imgur.com/gFt9FFa.png)
- Search for Cayenne LPP in the search bar
![](https://i.imgur.com/teGlo9r.png)
- select cayenne LPP and enter the devEUI, phyical address of the device and click on "Add device" option
![](https://i.imgur.com/JGrRolo.png)

### Steps
- Clone the repositiry on local machine
- Open the project on Atmel Studio 7
- Edit the conf_app.h file for changing the LoRaWAN Application settings like devEUI, appEUI, appKey, joinType, subBand, sleepTime etc.  The network settings like devEUI, appEUI etc., are available during device registration
- Connect the SAM R34 Xplained Pro using EDBG USB to PC as mentioned in Hardware Setup Section
- Program the APPS_ENDDEVICE_DEMO firmware on to SAM R34 Xplained Pro - For first time Atmel Studio instructions [here](http://ww1.microchip.com/downloads/en/DeviceDoc/Getting-Started-with-Atmel-Studio7.pdf "here")
- After programming the firmware, open Terminal Emulator Application like Teraterm
- Open the COM port on TeraTerm with settings - Baudrate - 9600, Data - 8 bit, Parity - None, Stop - 1 bit, Flow control - none
- Reset the board, logs of the demo application will be displayed on terminal window. 
- Demo Application starts with the end device trying to join the LoRaWAN Network server.
- Once joined, end device waits for incoming serial data from weather station
- Upon successful reception of the sensor data from the Network server, data is wrapped into a Cayenne LPP format and sent to the LoRaWAN Application Server (Cayenne for display)
- Upon successful reception of sensor data Cayenne dashboard will display all the received sensor values from the LoRaWAN End Device (Users are free to change icons of the received sensor value and other settings)
![](https://i.imgur.com/XgDAk4Y.png)
**Live Sensor Data**
![](https://i.imgur.com/khK4XQk.png)

#### Weather Station Details
![](https://i.imgur.com/YQyVE3z.png)
More details on protocol implementation for implementing the serial data etc can be requested to the manufacturer of the weather station
**Data received explanation:** Total 34 data (hex)： (example of received hex data as：24 0D 14 62 A4 38 22 05 00 1C 00 03 00 15 18 FF F9
- 1st、2nd： 24 (identify tx type)
- 3rd、4th： 0D (security code)
- 5th、6th、7th： 146 (wind direction) (explanation: 146(HEX) =0001, 0100,0110 (Binary) (Bit8=0, Bit 7=0, Bit 6=0, Bit 5=0, Bit 4=1, Bit 3=0, Bit 2=1, Bit 1=0, Bit 0=0,) Wind direction is:B0 0001, 0100 = 20 (decimal) So, wind direction is: 20°
- 8th,9th,10th： 2A4 (Temperature) (explanation:2A4 (HEX)= B0010 1010 0100 =676(Decimal) calculation： (676-400)/10=27.6 so temperature is: 27.6℃ 11th、12th：38 (Humidity) （Explanation:38(HEX)=56(D), so it is 56%）
- 13th、14 th：22 (wind speed) (explanation: 22 (HEX) = B 0010 0010 (Bit8=0, Bit 7=0, Bit 6=0, Bit 5=1, Bit 4=0, Bit 3=0, Bit 2=0, Bit 1=1, Bit 0=0,) So, the data is: B0 0010 0010 = 34 (D) calculation：34/8*1.12=4.76 So, wind speed is: 4.75 m/s.
- 15th、16th：05 (gust speed) (explanation: gust speed: 5 *1.12= 5.6 m/s )
- 17th-20 th： 001c (accumulation rainfall) (explanation: accumulation rainfall: 28 mm ) - 21th-24th： 0003 (UV) (explanation: UV: uW/cm2)
- 25th-30th： 001518 (LIGHT) (explanation: UV:5400/10=540 LUX)
- 31th、32th：FF CRC (crc8, Polynomial_hex：31)
- 33th、34 th：F9 checksum value (sum of the previous 16 bytes)

**Snapshot of Hardware setup**
![](https://i.imgur.com/eVEGzBp.png)
