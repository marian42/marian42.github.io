---
title: Game prototypes
date: 2015-07-18T15:55:40+00:00
categories:
  - Blog
tags:
  - c++
  - gamedev
  - java
  - opengl

---
I’d like to share two game prototypes I made a few years ago. The first one is based on Tetris:

<video autoplay loop src="/article/game-prototypes/tetris1.webm" type="video/webm"></video>

It was written in C++ with bare-bones OpenGL. Once you press shift, the game enters a “fast mode”, where the down button takes a piece all the way down and if you don’t press it for three seconds, it will drop where it is. This is meant to be a fast-paced version of the original Tetris.

<video autoplay loop src="/article/game-prototypes/tetris2.webm" type="video/webm"></video>

<!--more-->

The second game is based on the Osmos mechanic, in a 3D space. If two cells touch each other, the bigger one absorbs the smaller one. The goal is to become the biggest cell by avoiding bigger cells and eating smaller ones. I wrote this in Java with the LWJGL library.

<video autoplay loop src="/article/game-prototypes/cells.webm" type="video/webm"></video>

<a href="/article/game-prototypes/games.zip" target="_blank">Here is a zip file with both games</a>.
