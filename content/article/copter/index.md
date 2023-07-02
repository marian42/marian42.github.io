---
title: Quadrocopter
date: 2013-10-26T23:57:34+00:00
tags:
  - de
  - Quadcopter

---

{{< img "DSC_0008s.jpg" "" >}}

Ich habe mir dieses Jahr den Traum erfüllt, einen selbst zusammengestellten Quadrocopter zu bauen.

<!--more-->

#### Investitionen

Für mich ist dieses Projekt bisher immer an zu hohen Kosten und mangelnden Informationen für Einsteiger gescheitert. Diese Probleme wurden zum Teil ausgeräumt durch die Erkenntnis, dass es deutlich günstigere Systeme als die von Mikrocopter gibt, als auch die Hilfe von der Community bei [fpv-community.de][1], insbesondere [dieser Einsteiger-Guide][2]. Mein Ziel bei diesem Projekt ist, möglichst wenig zu investieren und einen Copter zu haben, der später problemlos aufgerüstet werden kann, z.B. mit einer Kamera oder einem FPV-System.

#### ArduCopter

Letztendlich benutze ich als Flight Control, also als “Gehirn” des Copters, einen [ArduFlyer 2.5][3], der ein Nachbau des Open Source Projekts [ArduPilot][4] ist. Das Board ist baugleich und entsprechend kompatibel, bzw. bietet die gleichen Funktionen. Die Vorteile von ArduPilot sind die hohe Rechenleistung, die Sensoren (10 [DOF][5]) und die Kompatibilität zu verschiedener Hardware wie GPS, Kompass, Telemetrie, Kameraaufhängung.

#### Hobbyking und Teile

####

{{< img "IMG_20130820_140911s.jpg" "" >}}

Einen Großteil der Teile habe ich bei Hobbyking bestellt, das besonders günstig ist, aber einen [durchwachsenen][6] Ruf hat. Bei mir sind keine der “bekannten” Probleme mit Hobbyking aufgetreten. Die Pakete waren nach einer Woche in Deutschland, wo sie allerdings recht lange beim Zoll bearbeitet wurden. Wer im Ausland bestellt, muss ab einem bestimmten Wert damit rechnen, 19% MwSt und 4,9% Zoll zusätzlich zu bezahlen.

#### Fernsteuerung

{{< img "IMG_20130824_003531s.jpg" "" >}}

Als Fernsteuerung benutze ich die Turnigy 9X, die dadurch hervorsticht, dass sie nur etwa 10% einer typischen RC-Fernsteuerung kostet. Dies macht sich dadurch bemerkbar, dass einige Teile etwas “wackelig” wirken. Die Firmware ist ab Werk nicht zufriedenstellend, da sie Fehler enthält und bei jedem Tastendruck laut piept. Dank einer breiten Nutzerbasis gibt es allerdings auch alternative Firmwares, die sich mit [etwas Löten und einem Arduino][7] aufspielen lassen. Mit der [er9x][8] Firmware hat die Turnigy dann alle Features, die man sich wünschen kann. Außerdem habe ich eine Displaybeleuchtung und einen Akku nachgerüstet, was die 9X zu einer vollwertigen Fernsteuerung macht.

#### Technische Daten

Der Copter ist mit einem GPS-Modul, einem externen Kompass, einem Telemetriesystem zum Datenaustausch mit einer Bodenstation und LED-Streifen ausgestattet. Die Flugzeit beträgt ohne Kamera etwa 13 – 15 Minuten bei einem 3Ah Akku (12V, 3C, LiPo). Die ESCs sind mit der SimonK Firmware geflasht. Der Copter ist diagonal etwa 60cm lang und wiegt 1kg.

#### Fähigkeiten

Diese Stunts sind etwa das “[Standardrepartoire][9]” vom Ardupilot. Im Folgenden also eine Liste mit Dingen, die der Copter kann, allerdings nur die, die ich schon erfolgreich getestet habe:

  * Loitermodus: Der Copter behält automatisch die Höhe und Position bei
  * Return to Launch: Der Copter fliegt zum Startpunkt und landet. Dies ist auch das Verhalten, wenn die Verbindung zur Fernsteuerung abbricht.
  * Bodenstation: Mit einer Verbindung zu einem Handy / Laptop am Boden können Flugdaten abgerufen und Befehle gesendet werden, wie Wegpunkte, die der Copter anfliegt.
  * Follow Me: Der Copter folgt einer Person (bzw einem Handy) auf einer festgelegten Höhe

#### Kamera

{{< img "G0010081.jpg" "" >}}

Der typische Anwendungsfall von Multicoptern ist das Filmen oder Fotografieren aus der Luft. Mein Copter ist seit kurzem mit einer Gopro ausgestattet. Er wird bald ein Kamera-Gimbal bekommen, das die Neigungen des Copters während des Flugs ausgleicht.

#### Licht

{{< img "DSC_0028.jpg" "" >}}

Der Copter ist mit RGB-LED Streifen ausgestattet, die pro Arm ansteuerbar sind. Mit der Fernsteuerung kann durch verschiedene Modi durchgewechselt werden, wie “Polizei” oder einzelne Farben. Mit dieser Beleuchtung kann man bei Nacht schöne [Effekte][10] mit Langzeitbelichtung erzielen.

#### Material

  * [Onboard Videomaterial][11]
  * [Teileliste mit Links][12]
  * [Lichtsystem][13]

 [1]: http://fpv-community.de/forum.php
 [2]: http://fpv-community.de/showthread.php?24169-Anleitung-amp-Erkl%E4rung-zum-Bau-eines-Multicopters-mit-aktuellen-Komponenten
 [3]: http://www.rctimer.com/product_818.html
 [4]: http://copter.ardupilot.com/
 [5]: https://en.wikipedia.org/wiki/Degrees_of_freedom_%28mechanics%29
 [6]: https://encrypted.google.com/search?hl=de&q=hobbyking#hl=de&q=hobbyking+probleme&safe=off
 [7]: http://diyjunky.blogspot.de/2011/09/using-your-arduino-to-program-turnigy.html
 [8]: http://code.google.com/p/er9x/
 [9]: http://copter.ardupilot.com/wiki/flight-modes/
 [10]: /article/copter-lightpainting/
 [11]: https://www.youtube.com/playlist?list=PLou6JbK5uCtZ4Q6rRq4UWLk5jsg_JpIeh
 [12]: /article/copter/parts.html
 [13]: /article/copter-lights/
