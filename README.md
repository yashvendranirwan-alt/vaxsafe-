Vaxsafe:AI and Blockchain-Powered Vaccine cold chain
Vaxsafe is end to end IOT solution design and monitor the safety and potency of vaccine during transport. it use esp32 edge Device for real time sensing.
A Python backend AI to calculate shelf life decay,and a SHA-256 blockchain link to pervent data tempering.

    HOW IT WORK :
                 Sensing:- The esp32 monitor via DTH22 sensor.
                 EDGE ALERT:- IF the temprature leave safe range,local led and buzzer trigger immediately.
                 AI ANALYSIS:- DATA is sent to a FLASK SERVER Where AI logic calculate % potency of vaccine potency on base of thermal stress.
                 BLOCKCHAIN LOGGING :- Every succefull updated hashed with pervious record hash, creating an immutable chain of custody.

   HARDWARE SETUP :
                MICROCONTROLLER:- ESP32
                SENSOR:- DHT22
                INDICTORS:- 1* RED LED,1*ACTIVE BUZZER,1*GREEN LED
                PLATFORM:- BLYNK IOT CLOUD

      PIN MAPPING :-
                         Component                             ESP32 Pin        Function
                         DHT22 Data                            GPIO 15     Temp/Humidity Sensing
                         Red LED                               GPIO 12     Critical Alert
                         Green LED                             GPIO 14     System Secure
                         Buzzer                                GPIO 13     Audible Alarm                                  

          SOFTWARE ARCHITECTURE :-
                                   AI POTENCY MODEL (LOGIC) :
                                                              The backend uses a perdictive decay model:
                                                               HEAT IMPACT :For every 1 c and above 8 c potency drop 1%
                                                               FREEZ IMPACT : ANY DIP LESS THAN 2 C CAUSES POTENCY DROP 0.5%



                                    BLOCKCHAIN INTEGRETY :-
                                                            To pervent log tampering the system use SHA-256 Chaining.
                                                            Hash (new)-SHA256(TEMPRATURE+HEALTH+TIMESTAMP+HASH(PERVIOUS) )

Installation & Deployment :

                             Install dependeny
                                               pip install flask
 
                             Run the server
                                            python server.py

                              (NOTE: TAKE NOTE OF YOUR LAPTOP IP ADDRESS FOR CONNECTION)
                              
FIRMWARE SETUP : 
                         Open vaxsafe_esp32.ino in AURDINO IDE.
                         IMPORTANT: Replace placeholder for BLYNK_AUTH_TOKEN,WIFI SSID,SERVER URL( Use Your Laptop IP ).
                         Uplod to ESP32.


  PROJECT STRUCTURE :
                        /backend/server.py - Flask server,AI decay logic and blockchain hashing.
                        /firmware/vaxsafe_esp32.ino - ESP32 C++ CODE FOR SENSOR DATA AND BLYNK INTEGRATION.
                        requirment.txt - python dependency.
FUTURE IMPROVMENT :
Smart Contracts: Moving the hashing logic from a local Python script to an on-chain Solidity contract (Ethereum/Polygon).
Deep Learning: Using a LSTMs (Long Short-Term Memory) network to predict when a vaccine will spoil *before* it actually does.
GPS Integration:** Tracking the exact location of the shipment during a temperature breach.

AUTHOR:
       [YASHVENDRA SINGH] 1ST YEAR BTECH STUDENT PROJECT : internet of thing and cold chain security.
















                                                            





                         
