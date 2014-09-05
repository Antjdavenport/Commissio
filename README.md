Commissio,
==========

Commissio is an interactive art installation, which takes advantage of an Xbox Kinect Sensor to track visitors within the space. <br/>
The tracking data collected from the Kinect is sent from Processing through an MQTT service to wireless Arduino's. <br/>
The Arduino's interpret the tracking data to control a set of LED matrices. 

Processing
==========
Libraries:<br/>
1.SimpleOpenNi<br/>
2.MQTT4Processing (https://github.com/agoransson/mqtt4processing)<br/>

Arduino
=======
Libraries:<br/>
1.PubSubClient (https://github.com/knolleary/pubsubclient)<br/>
2. WiFly (https://github.com/sparkfun/WiFly-Shield)

IBM MQTT APP
============
The IBM MQTT app is a self made application using Applescript to automatically open the IBM MQTT files, saving <br/>
the user from inputting the commands manually
