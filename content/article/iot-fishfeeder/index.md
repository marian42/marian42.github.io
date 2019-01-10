---
title: Raspberry Pi powered fishtank
date: 2015-04-03T18:20:17+00:00
tags:
  - arduino
  - bootstrap
  - fishtank
  - flask
  - python
  - raspberrypi
  - webdev

---
<video autoplay loop muted src="/article/iot-fishfeeder/feed.ogv" type="video/ogg" /></video>

My fishtank is now internet-connected. It is run by a Raspberry Pi that can do three things: Feed the fish, switch the lights and take pictures.

To feed the fish, the Raspberry Pi sends commands to an automatic fishfeeder that I modified. It can empty any container in any order. This is achieved by an Arduino Pro Mini, two servos and a motor ([more][1]). The plate prevents hot air from flowing into the feeder. In an early iteration of the project, this made the food sticky and kept it from falling into the tank. Switching the lights is done using a remote light switch and 433Mhz transmitter. Finally, there is a webcam that is connected directly to the Raspberry Pi to take pictures.<!--more-->

The setup sits on top of my aquarium:

{{< img "setup.jpg" "" >}}

The Raspberry Pi runs a python / flask server that provides a web interface. If everything works, the web interface of my fishtank is available here:

[http://fishtank.marian42.de/][2]

The food stored in each container is remembered by the python script. This allows rules like “Feed the oldest food first” or “Prefer flake food”. The script will also try to minimize the rotation time.

{{< img "feeder.png" "" >}}

The Raspberry Pi performs planned events that can be set up and monitored through the web interface.

{{< img "schedule.png" "" >}}

To prevent overfeeding, the server remembers a “saturation value” for the fish. Whenever the fishfeeder adds food, the saturation value is increased (eg. by one for a typical one day portion). The saturation is gradually decreased by one per day, but doesn’t go below zero. A value below 1 means that the fish are hungy. Planned feed events are only automatically performed by the Raspberry Pi when the saturation is below 1. This mechanism makes sure that on average the fish get about one portion unit of food per day.

{{< img "webcam.jpg" "" >}}

The web interface allows guests to feed the fish. This feature is only available if the fish are hungry and the lights are on. Guests can choose what kind of food to feed. Once the process is complete, a picture is taken and displayed on the website.

{{< img "img65.jpg" "" >}}

The pictures taken with the webcam can be used to verify that everything worked.

{{< img "pushbullet.png" "" >}}

Whenever the fish are fed or a picture is taken, the picture is sent to my phone using the pushbullet API.

The server keeps a log of all events and errors that can also be viewed on the web interface.

All the source code for this project can be found on [github][3].

 [1]: http://marian42.de/?p=508
 [2]: http://fishtank.marian42.de/ "http://fishtank.marian42.de/"
 [3]: https://github.com/marian42/fishtank
