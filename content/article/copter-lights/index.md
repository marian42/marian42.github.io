---
title: Quadrocopter Lichtsystem
date: 2013-10-15T22:47:26+00:00
tags:
  - BTduino
  - de
  - LED
  - Quadcopter

---

{{< img "DSC_0036.jpg" "" >}}

Dies ist ein Arduinoprojekt, das vier RGB-LED-Streifen an den vier Armen des Quadrocopters ansteuert. Das Ziel war, bei möglichst geringen Materialkosten möglichst viele Möglichkeiten bei der Beleuchtung des Quadrocopters zu haben.

<!--more-->Verwendete Teile:

  * 1m RGB-LED Streifen, jeweils zwei Segmente a 3x RGB pro Arm, mit 12V
  * TLC5940 LED Driver zur Steuerung der LEDs
  * ATmega328p (der Microcontroller des Arduino Uno)
  * Bluetooth-Modul (muss im Flug nicht zwingend angebracht sein)
  * Kabel, zum Testen ein Breadboard

Der Arduino steuert über zwölf Kanäle jeweils den Rot-, Grün- und Blauanteil der vier LED-Streifen und kann so Farben mischen. Dazu wird der [Farbwert (HSV)][1] in RGB umgerechnet.

{{< img "arduino_Schaltplan33.png" "" >}}

Als Eingabe dienen die Fernsteuerung des Quadrocopters, ein Bluetooth-Interface und der Status des Flightcontrollers. Die Fernsteuerung sendet über zwei Kanäle den Wert eines Potenziometers und den zweier Schalter (An/Aus, Modus). Abhängig vom Modus verändert der Drehregler unterschiedliche Paramter (siehe Video). Die gleichen Eingaben können auch über das Bluetooth-Interface gemacht werden. Außerdem können dort Parameter für eigene Animationen festgelegt werden, die dann auf dem ATmega gespeichert werden und im Flug als eigene Modi auftreten. Weiterhin gibt das Lichtsystem ein optisches Signal beim Starten, beim Sperren und Entsperren, bei fehlendem GPS-Signal und bei ausgeschalteter Fernsteuerung. Dazu liest der Arduino die Signale der APM-Pins für die [Status-LEDs][2] (A4 – A6).

{{< img "DSC_00071.jpg" "" >}}

{{< img "DSC_0008.jpg" "" >}}

Nachdem ich das Projekt einige Zeit mit einem Breadboard getestet habe, sind nun alle Komponenten auf ein Stück Lochbrett gelötet, mit Steckverbindungen, sodass ich die Teile auch für andere Projekte verwenden kann. Außerdem habe ich eine Programmierschnittstelle (rechts) für den Arduino angelötet.

{{< img "q1.png" "" >}}

Für das Android-Interface habe ich meine selbstgeschriebene [Android-App][3] verwendet, die es ermöglicht, Benutzeroberflächen für Arduino-Projekte zu erstellen. In der App werden die Farben der vier LED-Ausgänge in Echtzeit angezeigt. Weiterhin können der Modus und der entsprechende Wert verändert werden.

Mit diesen Parametern können eigene Animationen konfiguriert werden:

  * Farbwert
  * Offset der Farbwerte zwischen den vier Armen
  * Offset der Farbwerte für die einzelnen Arme
  * Geschwindigkeit, mit der sich der Farbwert verändert (0 -> keine Änderung)
  * Schritt, mit dem sich der Farbwert ändert (0 -> stufenlose Änderung)
  * Sättigung

{{< img "q2.png" "" >}}

  * Sättigung für die einzelnen Arme
  * Helligkeit für die einzelnen Arme
  * Gesamthelligkeit Sinus (Helligkeit pulsiert alle x Millisekunden)
  * Offset Helligkeit Sinus zwischen den vier Armen
  * Zeitabstand zwischen Pausen
  * Dauer der Pausen

In der App kann die aktuelle Konfiguration gespeichert werden.

Material: <a href="/article/copter-lights/copter_leds.txt" target="_blank">Arduino-Quellcode</a>, <a href="/article/copter-lightpainting/" target="_blank">Quadcopter Lightpainting Fotos</a>

 [1]: https://de.wikipedia.org/wiki/HSV-Farbraum#Umrechnung_HSV_in_RGB
 [2]: http://copter.ardupilot.com/wiki/nav-leds/
 [3]: /article/btduino/
