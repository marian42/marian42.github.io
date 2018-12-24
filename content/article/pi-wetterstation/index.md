---
title: Raspberry Pi Wetterstation
date: 2013-09-23T17:27:39+00:00
tags:
  - c++
  - de
  - hardware
  - php
  - raspberry-pi
  - wetter

---

{{< img "b1.jpg" "" >}}

 Um die Daten, die meine <a href="http://marian42.de/?p=8">Arduino-Wetterstation</a> liefert, verfügbarer zu machen, habe ich mich entschieden, das Projekt jetzt mit einem Raspberry Pi weiterzuführen. Die Sensordaten werden wieder vom ILC-Board geliefert, das ich für den Schülerwettbewerb <a href="http://www.intel-leibniz-challenge.de/">Intel Leibniz Challenge</a> bekommen habe.

<!--more-->

{{< img "wiring.jpg" "" >}}

Dazu kommt ein weiterer Helligkeitssensor und ein weiterer [Temperatursensor][1]. Den Temperatursensor verwende ich, da er einen eigenen IC zum Kompensieren von Spannungsschwankungen etc. hat und so zuverlässiger ist als der Heißleiter des ILC-Boards, der über einen Spannungsteiler ausgelesen wird.

Für den Pi habe ich ein kurzes <a href="http://pi.marian42.de/wetter/ilc.cpp" target="_blank">C++-Programm</a> geschrieben, dass dank <a href="http://wiringpi.com/" target="_blank">Wiring-Pi</a> weitgehend den Arduinocode aus dem Vorgängerprojekt enthält. Dabei wird aus 5 Messungen für jeden Sensor der Mittelwert verwendet. Das Programm wird von der Kommandozeile aufgerufen und kann die Daten direkt ausgeben oder auf die SD-Karte speichern. Ein Skript führt das Programm alle 60 Sekunden aus und zeichnet so die Daten auf.

{{< img "screenshot2.png" "" >}}

Der Pi ist ans Netzwerk angeschlossen und hostet eine Webseite, über die die Daten angezeigt werden können. Die Seite greift dabei auf die letzen gemessenen Daten zurück oder kann auf Wunsch auch eine eigene Messung anfertigen.

Bei den automatischen Messungen wird außerdem ein Datensatz an Xively gesendet ([siehe auch][5]), das eine API und eine [Visualisierung][6] der Daten bereitstellt.

{{< img "xively.png" "" >}}

Im Vergleich zum [Vorgängerprojekt][7] ist die Lösung mit dem Raspberry Pi zuverlässiger, da für die SD-Karte, die Uhrzeit etc. keine spezielle Hardware notwendig ist. Wie bei der Arduinowetterstation ist die Hardware noch nicht für den Betrieb im Freien ausgerüstet, wo die Wetterdaten aussagekräftiger wären.

 [1]: https://www.adafruit.com/products/374
 [5]: http://marian42.de/?p=67
 [6]: https://xively.com/feeds/200231797
 [7]: http://marian42.de/?p=8
