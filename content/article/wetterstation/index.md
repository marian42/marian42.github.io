---
title: Arduino-Wetterstation mit Bluetooth, Datalogging und Android-App
date: 2013-07-09T23:43:32+00:00
tags:
  - arduino
  - bluetooth
  - c++
  - de
  - hardware

---

{{< img "DSC_0037-3.jpg" "" >}}

Die Wetterdaten für die Wetterstation werden von einem Board gesammelt, das ich für einen Schülerwettbewerb (<a href="http://www.intel-leibniz-challenge.de/">ILC</a>) bekommen und zusammengesetzt habe. Auf dem Board rechnet ein <a href="http://www.atmel.com/Images/Atmel-8386-8-and-16-bit-AVR-Microcontroller-ATxmega64A3U-128A3U-192A3U-256A3U_datasheet.pdf" target="_blank">ATxmega128A3U</a>. Temperatur, Luftfeuchte, Luftdruck, Helligkeit, Regenmenge und Windgeschwindigkeit werden bestimmt. Die letzen beiden Werte werden durch <a href="http://de.wikipedia.org/wiki/Regenmesser#Digitale_Niederschlagsmesser" target="_blank">mechanische Aufbauten</a> ermittelt, an denen ein Magnet einen Hallsensor passiert.

<!--more-->Auf dem Breadboard befindet sich ein <a href="http://www.atmel.com/Images/doc8161.pdf" target="_blank">ATmega328p</a>, auf dem Arduino-Code läuft. Das ILC-Board sammelt und sendet die sechs Wetterdaten auf Anfrage an den Arduino. Aus Zeitgründen habe ich dafür ein eigenes Protokoll implementiert, diese Aufgabe könnte eleganter und besser mit I²C o.ä. umgesetzt werden.

{{< img "Screenshot_2013-05-28-20-11-15.png" "" >}}

Der Arduino ermittelt über eine angeschlossene [DCF77][1]-Antenne die aktuelle Uhrzeit, wie in einer Funkuhr. Mithilfe eines SD-Moduls wird auf einer SD-Karte eine Textdatei angelegt, in der die Wetterdaten gespeichert werden. Die Daten werden alle vier Sekunden aufgenommen und gespeichert, mit einer Zeile pro Datensatz. Dabei verwende ich das CSV-Format, sodass die Daten später einfach ausgewertet werden.

An die serielle Schnittstelle des Arduinos ist ein Bluetooth-Modul angeschlossen. Eine selbst entwickelte [Android-App][2] empfängt die Wetterdaten und zeigt sie an. Dazu werden die Daten in Textform über die serielle Verbindung gesendet, im Format Name-Doppelpunkt-Wert, also z.B. “Temperatur:25.41”. Neben den Wetterdaten werden in der App auch die Uhrzeit des DCF-Moduls und Informationen zur Stromversorgung angezeigt.

{{< img "erklärung.jpg" "" >}}

Als Stromversorgung dient entweder ein Akku von einem Modellauto (7,2V, 3Ah), der auf dem Board auf 5V reguliert wird, oder ein Handyladegerät, das über den Micro-USB-Port an das ILC-Board angeschlossen wird. Die Widerstände auf dem Breadboard dienen dazu, zwischen dem Arduino mit 5V und dem ILC-Board (bzw. dem DCF77-Modul) mit 3,3V zu kommunizieren.

Der eine Knopf setzt den Arduino zurück und der andere schaltet das Bluetooth-Modul an oder aus. Die rote LED leuchtet auf, wenn ein Fehler auftritt, wie zum Beispiel ein fehlerhaftes Zeitsignal oder eine fehlende SD-Karte. Die rechte grüne LED leuchtet immer und die linke visualisiert das DCF-Signal, sodass man erkennen kann, ob die Antenne richtig ausgerichtet ist.

<a href="/article/wetterstation/wetterstation.png" rel="lightbox[8]" title="Arduino-Wetterstation mit Bluetooth, Datalogging und Android-App">

{{< img "wetterstation_o.png" "" >}}

{{< img "wetterstation.png" "" >}}

</a>

{{< img "schaltplan.png" "" >}}

Der Hauptnachteil von meinem Projekt ist, dass es nicht wetterfest ist und somit nicht ohne zusätzliches Gehäuse draußen aufgestellt werden kann. Die Wetterstation bringt den ATmega an seine Grenzen was <a href="http://www.atmel.com/Images/doc8161.pdf" target="_blank">Programm- und Arbeitsspeicher</a> betrifft. Für weitere Features wie eine aktive Steuerung über Bluetooth wäre also z.B. ein <a href="http://arduino.cc/de/Main/ArduinoBoardMega" target="_blank">Arduino Mega</a> notwendig. Ein weiteres Problem ist die Zuverlässigkeit des DCF77-Moduls, das drinnen oft kein Signal empfängt. In Zukunft plane ich, ein ähnliches Projekt mit einem <a href="http://de.wikipedia.org/wiki/Raspberry_Pi" target="_blank">Raspberry Pi</a> umzusetzen, der dann alle Aufgaben außer dem Sammeln der Sensordaten übernimmt. Die Daten könnten so über das Internet bereitgestellt werden und die Beschränkung durch die Bluetooth-Reichweite entfällt.

{{< img "gui.png" "" >}}

Ich habe mit dem Projekt bei der [Intel Leibniz Challenge 2013][3] teilgenommen, bin aber nicht in die Endauswahl gekommen. Für diesen Wettbewerb habe ich auch eine GUI entwickelt, mit der die Daten über eine USB-Verbindung am Computer angezeigt werdenkönnen.

Downloads: <a href="/article/wetterstation/Wetterstation.ino">Arduino-Sketch</a>, <a href="/article/wetterstation/Wetterstation_tiny.ino">Arduino-Sketch für den ATtiny</a>, <a href="http://marian42.de/?p=179">Android-App</a> (mindestens Android 4.0), <a href="/article/wetterstation/Wetterstation.fzz">Fritzing-Schaltplan</a>.

 [1]: http://de.wikipedia.org/wiki/DCF77
 [2]: http://marian42.de/?p=179
 [3]: http://www.intel-leibniz-challenge.de/
