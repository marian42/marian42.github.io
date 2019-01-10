---
title: 'Connecting my fish tank to the Internet of Things – Part 1: Hacking an automatic fish feeder'
date: 2014-06-30T19:57:37+00:00
tags:
  - arduino
  - fishtank
  - hardware
  - internet of things

---

{{< img "DSC_0027_.jpg" "" >}}

I bought a used [automatic fish feeder][1] from ebay. This device is completely mechanic and very old (older than 1989). It has 27 containers for fish food and a disc that does one rotation per day. By sticking pins into that disc one can trigger one or more feedings per day. A pin will rotate an outer ring with the containers by one unit. One container always faces down, emptying its contents. So if the outer ring has made one revolution, all containers have been emptied.<!--more-->

The goals of my modification were

  * Add an Arduino that can empty a container at any time
  * Let the ring move to any container without emptying all other ones along the way
  * Let the Arduino know the absolute position of ring

The advantage of this is the ability to store differend kinds of fish food and different portion sizes. This is possible since the feeder can not only empty the very next container, but any one.

| | | |
|---|---|---|
| {{< img "IMG_20140526_201910.jpg" "" >}} | {{< img "IMG_20140526_212625.jpg" "" >}} | {{< img "IMG_20140528_201416.jpg" "" >}} |
| Taking the old fish feeder apart | Removing the old clockwork | New gear routing |

In order to hack the fish feeder, I removed the original power supply, most of the original clockwork and replaced the motor with a lower voltage, DC motor. The motor is driven using a <a href="https://www.sparkfun.com/products/9457">Sparkfun Motor Driver</a> board.

{{< img "DSC_0020_.jpg" "" >}}

I added a servo that pushes a bar in the gap that used to empty all passing containers. When the correct container is above the gap, the servo moves down, releasing the containers’s content. I use an <a href="https://www.sparkfun.com/products/11113">Arduino Pro Mini</a> as microcontroller.

To make precise movements, I added a light sensor to one cog in the clockwork. I colored part of the cog black and put an LED underneath it. When the black part moves between the LED and the sensor, it senses less light. The microcontroller can use this to count the revolutions, mimicing the functionality of a stepper motor.

<video loop autoplay muted src="/article/fishfeeder/sensor1.mp4" type="video/mp4"></video>

{{< img "DSC_0016_.jpg" "" >}}

Another LED plus light sensor detects the position of the outer ring. A white marker on the black ring indicates the position of the first container, letting the microcontroller determine the absolute position of the ring.

I drilled a hole in the case of the fish feeder and put in an RGB-LED. It can display the status of the Arduino. For later use, I also connected another light sensor, facing into the fish tank to check whether the lights are on.

{{< img "openclose.jpg" "" >}}

The Arduino Pro Mini and all the electronics fit nicely into the case of the original device. The Arduino will later be connected to a Raspberry Pi and communicate through a serial connection. The next entry will be about setting up the Raspberry Pi.

<a href="/article/fishfeeder/fishfeeder.ino">Arduino Source Code</a>

 [1]: https://www.google.com/search?q=rondomatic&safe=active&hl=de&tbm=isch&source=lnms&sa=X&ei=TLmxU-bcE4n-4QSyw4DIDA&ved=0CAgQ_AUoAw&biw=1920&bih=968
