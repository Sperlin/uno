# UNO

 C++ Projektarbeit von Gabriel Sperling und Vsevolod Pypenko
 
## Anleitung zu dem Spiel
### Wie wird das Spiel gestartet? 
In dem main Branch auf GitHub befindet sich die aktuelle Version des Spiels.   
Bauen mithilfe von Makefile: `make`   
Starten: `./uno`  
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
  
*Zum besseren Verständnis des Programms, liegt in GitHub auch ein Klassendiagramm (`Uno.drawio.pdf`)*
