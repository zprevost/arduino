# Flatbot
This is a planar robot arm with two degrees of motion. It has limit switches that prevents it from moving too far.  
   
### Hardware
* [Arduino](https://www.amazon.com/ELEGOO-Board-ATmega328P-ATMEGA16U2-Compliant/dp/B01EWOE0UU)
* [2 Elegoo stepper motors and driver boards](https://www.amazon.com/ELEGOO-28BYJ-48-ULN2003-Stepper-Arduino/dp/B01CP18J4A/ref=sr_1_1_sspa?dchild=1&keywords=elegoo+stepper+motor&qid=1595258380&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzNldLMlFQVDZJMjBCJmVuY3J5cHRlZElkPUEwOTU5MzEwMjFMM0tTUlQ0N01ZJmVuY3J5cHRlZEFkSWQ9QTAyNDcwOTYxOEZXUEFWRU9ORkdKJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)
* 8 male-to-male Dupont wires
* 12 male-to-female Dupont wires
* 2 10k ohm resistors
* Meccano pieces (I used meccano pieces but something else could be used.)
* Plastic Arduino case
* Adhesive
* Mini breadboard
* Board (I used the back of a clipboard but anything would work.)
  
## The Robot
### Hardware
* Arduino
* 2 Elegoo stepper motors and driver boards
* 2 male-to-male Dupont wires
* 12 male-to-female Dupont wires
* Meccano pieces (or something similar)
* Plastic Arduino case
* Adhesive
* Mini breadboard
* Board 
  
The motors are attached with the meccano pieces. The motor in the bottom right corner is directly attached to the board, but none of the other robot pieces are.  

It looks like this:  
<img src="https://github.com/zprevost/arduino/blob/master/sketch/flatbot/flatbot.JPG" width="400" />
### Electrical
Wiring diagram of the robot:  
<img src="https://github.com/zprevost/arduino/blob/master/sketch/flatbot/flatbot_arm_wiring_diagram.png" width="400" />
  
## The Limit Switches  
Limit switches stop the robot from going too far. When pressed, the switches send the Arduino an input and the Arduino stops the motion.
  
### Hardware 
* Arduino
* 6 male-to-male Dupont wires
* 2 10k ohm resistors
* Mini breadboard 

The limit switches are circled in orange:  
<img src="https://github.com/zprevost/arduino/blob/master/sketch/flatbot/limit_switches_circled.jpg" width="400" /> 
### Electrical:  
Wiring diagram of the limit switches:  
<img src="https://github.com/zprevost/arduino/blob/master/sketch/flatbot/limit_switches_wiring.png" width="400" />
