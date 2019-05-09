---
title: LED Matrix Software
date: 2017-05-13T21:49:00+00:00
tags:
  - c++
  - js
  - LED
  - ledmatrix
  - leds
  - matrix
  - python
  - raspberrypi
  - webdev

---

{{< img "screenshot-2.png" "" >}}

I wrote two programs that run on my LED matrix. They have different approaches and different aims. This post describes one of them. <!--more-->

The app offers a web interface where users can write simple programs that are then compiled and started instantly from the website. The concept is similar to [Shadertoy][1], where you write C-like shader code in a browser window and instantly see it run. The code of for this project is on my [github][2] and it’s in a state where you should be able to run it fairly easily, if your hardware is similar. The github page has installation instructions and some documentation on the available functions for user apps.

The backend for the webapp is written in Python, using flask. The user apps are written in C++. I first tried to use Python for this as well, but it wasn’t fast enough. Just iterating through a 256 color list already impacts the framerate. The C++ code is compiled into a shared object library file. The library is loaded into the python app using the python module ctypes. The client is written in Javascript, using codemirror to edit code and bootstrap for the UI.

There is a gif recording feature that creates live recordings of the apps you write:

| | | | |
|---|---|---|---|
| {{< img "RingTest.gif" "" >}} | {{< img "Pie.gif" "" >}} |  {{< img "Fire.gif" "" >}} | {{< img "Swirl.gif" "" >}} |
| {{< img "CloudySky.gif" "" >}} | {{< img "RingZoom.gif" "" >}} | {{< img "Beacon.gif" "" >}} | |

{{< img "DSCF1527.jpg" "" >}}

 [1]: https://shadertoy.com
 [2]: https://github.com/marian42/ledcpp
