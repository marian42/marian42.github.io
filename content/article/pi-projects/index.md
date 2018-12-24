---
title: Raspberry Pi Projekte
date: 2013-10-19T11:29:54+00:00
tags:
  - de
  - Home Automation
  - http
  - IR
  - raspberry-pi
  - RF
  - samba

---
Was macht man eigentlich mit einem Raspberry Pi? Ich habe mir vor einem halben Jahr einen gekauft. Seitdem steht er hier auf meinem Schreibtisch und führt eine Reihe von Aufgaben aus. Hier eine Übersicht:

  * http-Server für einige Webseiten auf dem Pi und die Daten auf meiner externen Festplatte
  * [Samba][2] und [FTP][3] Server für die Daten auf der Festplatte

{{< img "samba.png" "" >}}

  * [Wetterstation][4]: Mit einigen Sensoren werden einmal pro Minute Wetterdaten aufgezeichnet

{{< img "wiring.jpg" "" >}}

  * Webseite für die Wetterdaten
  * Über einen RF-Sender steuert der Pi einige Funksteckdosen in meinem Zimmer an (mit [RF-Sender][6], [ELRO-Funksteckdosen][7] und [rcswitch-pi][8])
  * Über einen IR-Sender steuert der Pi meine Stereoanlage (mit [LIRC][9])

| | | |
|---|---|---|
| {{< img "zimmer.png" "" >}} | {{< img "steckdose.jpg" "" >}} | {{< img "Screenshot_2013-10-19-12-16-43.png" "" >}} |

  * Für die Stereoanlage und die Steckdosen gibt es eine API und ein Web-Interface zum Steuern. Außerdem kann die App <a href="https://play.google.com/store/apps/details?id=net.dinglisch.android.taskerm">Tasker</a> auf meinem Handy auf die API zugreifen. Es gibt z.B. einen Task für “Schreibtischlampe umschalten”. Auf dem Homescreen liegt ein Ordner mit Verknüpfungen für diese Tasks. Der eigentliche Sinn von Tasker ist aber, solche Tasks automatisiert auszuführen. Beispielsweise schaltet Tasker morgens, wenn der Wecker klingelt, auch gleich das Licht und das Radio an.
  * Der Pi verbindet ein LoL-Shield mit dem Internet, um <a href="/article/lol-notifications">Benachrichtigungen</a> anzuzeigen.

 [1]: http://pi.marian42.de/
 [2]: http://blog.pi3g.com/2013/05/dateien-fr-windows-freigeben-raspberry-pi-als-dateiserver-mittels-samba/
 [3]: http://ihoeft.wordpress.com/2013/03/26/raspberry-pi-ftp-server-einrichten-proftpd/
 [4]: /article/wetterstation/
 [5]: http://marian42.no-ip.biz/wetter/
 [6]: http://www.ebay.de/sch/i.html?_odkw=rf+433&LH_BIN=1&_sop=15&_osacat=0&_from=R40&LH_PrefLoc=3&_trksid=p2045573.m570.l1313.TR0.TRC0.Xrf+433mhz&_nkw=rf+433mhz&_sacat=0
 [7]: http://www.amazon.de/Elro-AB440S-3C-Funksteckdosen-Funksteckdose/dp/B002QXN7X6/ref=sr_1_1?ie=UTF8&qid=1382180929&sr=8-1&keywords=elro+funksteckdose
 [8]: https://github.com/r10r/rcswitch-pi
 [9]: http://www.lirc.org/
