# Project Description
This is a the sketch of a bluetooth controlled path correcting rover controlled by Arduino UNO.
It uses ultrasonic sensor to calculate the distance and take corrective measures accordingly.

# Modules used
Bluetooth  module HC-05  
LCD module LCD1602  
LCD1602 I2C backpack module  
Ultrasonic sensor HC-SR04  
Motor Driver L298N

# Pin Connection
-LCD1602 I2C backpack  
  SCL - A5  
  SDA - A4  
  Vcc - 5V  
  Gnd - Gnd  
  
-Bluetooth  module HC-05  
  Tx - Rx  
  Rx - Tx (With a voltage divider circuit)  
  Vcc - 5V  
  Gnd - Gnd  
  
-Ultrasonic sensor HC-SR04  
  Echo - 6  
  Trig - 7  
  Vcc - 5V  
  Gnd - Gnd  
  
-Motor Driver L298N  
  OUT1, OUT2, OUT3 & OUT4 - To the motor  
  IN1 - 4  
  IN2 - 5  
  IN3 - 2  
  IN$ - 3  
  12V - External power source  
  Gnd - Gnd

# The Rover
  
  ![Bluetooth Controlled Path Correcting Rover](GIF/Bluetooth%20Controlled%20Path%20Correcting%20Rover.gif)
