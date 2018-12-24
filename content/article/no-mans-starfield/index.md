---
title: No Man’s Starfield
date: 2016-09-18T20:56:03+00:00
tags:
  - c++
  - gamedev
  - glsl
  - graphics
  - raytracing

---
<video autoplay loop><source src="/article/no-mans-starfield/starfield.webm" type="video/webm" /></video>

This is a shader I made that renders a flight through a starfield. It’s meant to look like the galactic map that you can see in No Man’s Sky. Here is a link to the project on shadertoy:

[No Man’s Starfield][1]

<!--more-->

The cool thing about this is that it runs inside a shader. A shader is a small program that runs on the graphics card and is usually used to create simple effects like shadows or reflections. However, it can also be used to make [really complex things][2]. In a shader, all pixels are computed separately and in paralell. That means the program gets the pixel coordinate and computes a color for it. This program is then called for each pixel in the frame.

To render 3D worlds, realtime graphics apps usually use depth buffers. However, inside a shader, one is forced to use raytracing. This means that for each pixel, a virtual light ray is followed from the camera until it hits something.

In this case, I need to check if the ray hits a star. Computing the distance between every ray and every star to check if it’s less than the star radius would take too long. Instead, the ray travels through a 3D grid. Every grid cell either has a star or not. This is determined using simplex noise. With this technique, the ray needs only to be compared to the stars within the grid cells that the ray travels through, and only those grid cells that contain a star.

Using raytracing also makes it easy to bend rays. My shader uses this to bend light rays close to black holes. Black holes occasionally appear instead of stars.

{{< img "starfield.jpg" "" >}}

 [1]: https://www.shadertoy.com/view/MtcGDf
 [2]: https://www.shadertoy.com/results?query=&sort=love&filter=
