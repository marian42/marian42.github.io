---
title: BTduino documentation
date: 2013-07-27T13:49:48+00:00
tags:
  - android
  - app
  - arduino
  - bluetooth
---

The [BTduino app][1] sends data using the serial interface of a microcontroller and a bluetooth connection. The concept of the protocol is to send all data in text form. Each set of data consists of the name and the value, seperated by a colon. This way of communication is not the most efficient one, but it is easy to use and human readable. <!--more-->Example:

    name:value

## Special commands

### Setup

    requestsetup

The BTduino app will send this command if you open a new project or if you click Menu > Request setup. At this point the microcontroller program should request all events that it will be using. The [example sketch][2] for Arduino provides a method that is called when requestsetup is received.

### Ping

    ping

If the BTduino app receives this line, it will send exactly the same back to the microcontroller. This can be used to check if there is a working connection.

### Remove event

    remove:myevent

If the BTduino app receives this line, it will remove the specified event.

### Parse

In your project in the BTduino app, click Menu > Parse and enter a command. This will have the exact same effect as if the app received this command via Bluetooth.

## Events

BTduino features several event types that can be used in a project:

### **Value receiver**

This event displays values that are sent from the microcontroller to the Android device. Send the name, a colon and the value as one line. The event is discovered by the app automatically. Example:

    mysensor:42

The app provides a gauge, a plot and datalogging.

### **String receiver**

This event displays text that is sent from the microcontroller to the Android device. Send the name, a colon and your text as one line. The event is discovered by the app automatically. Example:

    log:ready

The app provides a datalogging feature.

### **Value sender**

This event provides an interface to send numbers from the Android device to the microcontroller.

Send a value by typing it in the input field and hitting the send button or by using the slider. Touching the slider will automatically send a value to the microcontroller. The data will look like this:

    myvaluesender:42

You can change the value of the input field and the position of the slider via Bluetooth. This is done again by sending the name and the value as in the example above.

The event can be added manually in the Android app or by sending this command via bluetooth:

    requestint:myvaluesender

This command will as well make the Android app send the current value.

Set the min and max value of the slider by entering a value in the input field and then clicking the min or max value or by sending one of these commands via Bluetooth:

    setminmyvaluesender:0
    setmaxmyvaluesender:100

### **String sender**

This event provides an interface to send text from the Android device to the microcontroller. Send text by typing it in the input field and hitting the send button. The data will look like this:

    mystringsender:Hello World!

The event can be added manually in the Android app or by sending this command via bluetooth:

    requeststring:mystringsender

This command will as well make the Android app send the current value.

### **Boolean sender**

This event provides a switch that will send a boolean value to the microcontroller. Example:

    mybooleansender:true;
    mybooleansender:false;

You can change the state of the switch via Bluetooth. This is done again by sending the name and the value as in the example above. The app will recognize “true”/”false”, “1”/”0″ and “HIGH”/”LOW”. The event can be added manually in the Android app or by sending this command via bluetooth:

    requestboolean:mybooleansender
    requestbool:mybooleansender

This command will as well make the Android app send the current value.

### **Event sender**

This event provides a button that will send a specific text to the microcontroller when clicked. It will send the word “event” and the name of the event:

    event:myevent

Add it manually from the app or by sending this code:

    registerevent:myevent

### **Color receiver**

This event displays colors that are sent from the microcontroller to the Android device. Send the name, a colon and the value as one line. You can use the HTML format or send the color as an integer value. The event is discovered by the app automatically if you use the HTML color format. Example:

    mycolorreceiver:#FF00FF
    mycolorreceiver:16711935

Both lines represent the same color, because 16711935 equals 0xFF00FF. The color receiver provides a datalogging feature.

### Color sender

This event provides an interface to send colors from the Android device to the microcontroller.

Click on the color area to choose a color and click the send button to send it. You can select between four color formats: Integer, Hex, HTML and RGB. Example:

    mycolorsender:16711935
    mycolorsender:FF00FF
    mycolorsender:#FF00FF
    mycolorsender:255,0,255

You can change the value of the color field via Bluetooth. This is done again by sending the name and the value as in the example above, using the HTML or integer format.

The event can be added manually in the Android app or by sending this command via bluetooth:

    requestcolor:mycolorsender

This command will as well make the Android app send the current color.

### **Joystick**

This event provides a virtual joystick on the Android device that will continuously send the position via bluetooth. It will send X and Y coordinates between -1.0 and 1.0 like this:

    myjostick:0|0

The [example sketch for Arduino][2] shows how to use the data. The event can be added manually in the Android app or by sending this command via bluetooth:

    requestjoystick:myjoystick

You can lock or invert an axis in the BTduino app. The app allow you use the accelerometer to control the joystick. Click the record button to record a path. It can be performed using the play button. After you have recorded a path, long-click the joystick and select “Save path” to add a path event. This allows you to record multiple paths.

The logfiles for value receiver, string receiver and color receiver are stored on the SD card int he folder `/Bluetooth/<project name>/<eventname>.txt`. The textfile contains one dataset per line, consisting of the timestamp in milliseconds and the value.

 [1]: http://marian42.de/?p=179
 [2]: /article/btduino-doc/BTduino_example.txt
