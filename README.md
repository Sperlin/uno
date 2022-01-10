# UNO

 C++ Projektarbeit von Gabriel Sperling und Vsevolod Pypenko
 
## Anleitung zu dem Spiel
### Wie wird das Spiel gestartet? 
In dem `UNO V1` Release auf GitHub befindet sich die aktuelle Version des Spiels.   
Bauen mithilfe der Makefile: `make`   
Starten mit: `./uno`  
### Wie wird das Spiel gespielt?
1.	`Start a new game!` auswählen
2.	Nickname für deinen Spieler erstellen
3.	`Die Anzahl von Bots` auswählen (zwischen 1 und 3)
4.	In dem Spieler-Zug muss man die passende Karte auswählen, indem man die Farbe und die Zahl der Karte getrennt eingibt (im Falle einer Effekte-Karte schreibt man keine Zahl, sondern den Effekt (z.B., `skip`) hin), die `wild` Karten haben schwarze Farbe.
*	Wenn man keine Karte spielen kann, wird automatisch eine Karte gezogen
*	Wenn man 2 Karten in der Hand hat, und eine gespielt wird, muss in dem gleichen Zug zusätzlich noch `UNO` geschrieben werden
5.	Weiterspielen, bis man gewinnt oder verliert 
### Spielregeln
siehe (www.uno-kartenspiel.de/spielregeln/)  
  
**Unsere Anpassungen der Regeln:**   
*	**alle** Effekt-Karten können gestapelt werden, z.B. bei der `Aussetzen` Karte wird der nächste Spieler übersprungen.
*	Zudem darf jede `zieh zwei` Karte mit einer `zieh vier` Karte der gleichen Farbe gestapelt werden und umgekehrt 
*	Strafen und Punktesysteme sind nicht implementiert
*	Man darf nicht ziehen, wenn man mindestens eine Karte spielen kann       
 
## Hauptideen zur Implementierung

*Zum besseren Verständnis des Programms, liegt in `Dokumente` auch ein Klassendiagramm (`Uno.drawio.pdf`) und der Projektvorschlag*

Am Anfang wird ein *Game* Objekt erstellt. Dieses enthält alle wichtigen Daten zum Spiel, wie die Spieler, den aktuellen Zug, den aktuellen Effekt etc.. Außerdem werden darüber alle Eingaben und Ausgaben verarbeitet.

Über *Turn* Objekte werden die Informationen zu den Zügen gespeichert. Dabei wird nach jedem Zug ein neues *Turn* Objekt erstellt, das den aktuellen Spieler und die oberste Karte enthält.

Für jeden Spieler wird ein *Player* Objekt erstellt. Dabei wird zwischen *RealPlayer* und *Bot* unterschieden. Hier ist die Spielerlogik implementiert, wie zum Beispiel die Funktion zum legen einer Karte. 

Für das Kartenmanagement sind die Klassen *CardStack*, *PlayerCards* und *PlayedCards* zuständig. Hier werden in Vektoren die Karten mit ihren individuellen Farben, Werten und Effekten gespeichert. Dabei wurden für die Farben und Effekte Enumarations erstellt.

