---
title: Android-Benachrichtigungen auf dem Schreibtisch
date: 2014-02-16T18:47:39+00:00
tags:
  - android
  - arduino
  - de
  - raspberry-pi
  - tasker

---

{{< img "head.jpg" "" >}}

Das Ziel dieses Projekts ist, Benachrichtigungen von meinem Android-Handy automatisch auf einem [LoL-Shield][1] (Lots of LEDs) anzuzeigen. Dazu benutze ich einen Raspberry Pi, der sowieso schon auf meinem Schreibtisch steht, einen Arduino für das Schild und auf dem Handy [Tasker][2], um auf Benachrichtigungen zu reagieren. Sobald eine Benachrichtigung erscheint, passiert folgendes:

{{< img "idea.png" "" >}}

<!--more-->

{{< img "png.png" "" >}}

Der Arduino-Sketch zeigt die entsprechenden Icons in 8 Graustufen an. Dazu habe ich ein Java-Programm geschrieben, das PNG-Grafiken mit 14×9 Pixeln in Arrays mit C++-Syntax umrechnet. Werden einzelne Icons per serieller Schnitstelle aktiviert, werden sie auf dem Shield angezeigt und bei mehreren periodisch durchgewechselt.

Der Arduino ist mit dem Raspberry Pi mit drei Kabeln verbunden: 5V, GND und TX. Der TX-Pin des Pi ist mit dem RX Pin des Arduino verbunden. Auf dem Pi läuft ein PHP-Script, das die Befehle an den Arduino weiterleitet. Die einzelnen Befehle für den Arduino können auch mit einem Webinterface ausgelöst werden.

Es gibt eine Demofunktion, die alle Symbole anzeigt:

{{< img "s3.gif" "" >}}

Die Konfiguration mit Tasker gestaltet sich etwas schwieriger, da es keinen Trigger gibt, der bei jeder Benachrichtigung ausgelöst wird und gleichzeitig Rückschlüsse auf Anwendung zulässt, die die Benachrichtigung ausgelöst hat. Deshalb musste ich für jede unterstützte App (Twitter, Facebook, …) einen eigenen Task anlegen, insgesamt 12. Ebenso ist es nicht möglich, mit Tasker auf das Anklicken oder Deaktivieren von Benachrichtigungen zu reagieren. Deshalb werden beim Entsperren des Displays alle Symbole auf dem LoL-Shield deaktiviert und solche, die bei eingeschaltetem Handy-Display erschienen sind, verschwinden nach 40 Sekunden wieder.

{{< img "s1.gif" "" >}}

Unabhängig von den Benachrichtigungen kann das LoL-Shield, wenn keine Icons angezeigt werden, eine Binäruhr anzeigen. Es gibt außerdem die Möglichkeit, Texte zum Arduino zu senden, die dann über das Display scrollen. Dies kann per Web-Interface geschehen oder mit der Benachrichtigungsfunktion kombiniert via Tasker weitere Informationen anzeigen, beispielsweise, wer eine Nachricht gesendet hat.

{{< img "s2.gif" "" >}}

Download: [Arduino Skript][3] (benötigt LoL-Shield [Bibliothek][4]), [PHP-Skript][5], (benötigt [PHP Serial][6]), [Java Programm][7] für Icons, [Tasker-Skript][8]

 [1]: http://jimmieprodgers.com/kits/lolshield/
 [2]: https://play.google.com/store/apps/details?id=net.dinglisch.android.taskerm
 [3]: /article/lol-notifications/lol_notifier.ino
 [4]: http://code.google.com/p/lolshield/
 [5]: /article/lol-notifications/led-api.php.txt
 [6]: https://github.com/Xowap/PHP-Serial
 [7]: /article/lol-notifications/pixelextractor.java
 [8]: /article/lol-notifications/Notification.prj.xml
