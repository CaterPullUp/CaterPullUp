# Description du code de l'OpenCR
## Les électroaimants
### Electroaimant.h
Le fichier commence par inclure des directives de préprocesseur pour éviter les problèmes de double inclusion. Ensuite, la classe Electroaimant est définie avec des attributs protégés "etat" et "pin".

Le constructeur de la classe prend un argument "pin_" et initialise la variable "pin" avec cette valeur. La classe a également un destructeur virtuel.
La classe contient plusieurs fonctions virtuelles pures qui permettent de manipuler l'électro-aimant. Ces fonctions incluent "**setEtat**", "**getEtat**" et "**getPin**". Les fonctions "**setEtat**" et "**getEtat**" permettent respectivement de définir et d'obtenir l'état de l'électro-aimant. La fonction "getPin" permet d'obtenir le numéro de pin associé à l'électro-aimant. La classe a également deux autres fonctions virtuelles pures, "**activer**" et "**desactiver**", qui permettent d'activer ou de désactiver l'électro-aimant.

### ElectroCPU.h

Le fichier commence par inclure le fichier "Electroaimant.h" et la bibliothèque "Arduino.h". La classe ElectroCPU hérite de la classe abstraite Electroaimant, ce qui signifie qu'elle hérite toutes les fonctions de la classe Electroaimant. La classe Electroaimant se trouve dans le gabarit qui est réutilisable si le projet est réutilisé dans un autre objectif.

Ensuite, la classe ElectroCPU a un constructeur qui prend un argument "pin_" et qui appelle le constructeur de la classe Electroaimant. La classe ElectroCPU a également plusieurs fonctions virtuelles qui permettent de manipuler l'électro-aimant. Ces fonctions incluent "**activer**", "**desactiver**", "**getEtat**", "**getPin**" et "**setEtat**".

### ElectroCPU.cpp

Le code commence par inclure un fichier appelé "ElectroCPU.h". Ensuite, une classe appelée ElectroCPU est définie, qui hérite d'une classe abstraite appelée Electroaimant. La classe ElectroCPU a un constructeur qui prend un argument "pin_", qui est utilisé pour initialiser un objet de type Electroaimant. Le constructeur initialise également la variable "pin" avec la valeur de "pin_", configure le pin correspondant de la carte électronique en sortie et le met à un état bas.

Ensuite, la classe ElectroCPU a plusieurs fonctions qui permettent de manipuler l'électro-aimant: 
- La fonction "**activer**" met l'état de l'électro-aimant à vrai et configure le pin correspondant de la carte électronique à un état haut. 
- La fonction "**desactiver**" met l'état de l'électro-aimant à faux et configure le pin correspondant de la carte électronique à un état bas.
- La fonction "**getEtat**" renvoie l'état actuel de l'électro-aimant 
- La fonction "**setEtat**" permet de définir l'état de l'électro-aimant en utilisant une valeur booléenne.
- La fonction "**getPin**" renvoie le numéro de pin associé à l'électro-aimant.

### Uart.h
Le fichier contient les définitions de fonction pour le module UART de l'OpenCr.

### Uart.cpp
Le fichier contient les descriptions de fonction pour le module UART de l'OpenCr.

### Caterpullup.cpp/Caterpullup.h
Classe du robot catterpullup, contient la logique de la machine à état et de la séquence du robot.
gererEtat est la boucle principale du robot, elle contient la machine à état pour la séquence du robot.
gererMoteur verifie si cahque moteurs a atteint ou non leur position voulu et les arrêtes si c'est le cas.
gererGUI est utilisé lorsque le robot est en mode manuel, permet de gérer les mouvements demander par l'utilisateur au robot.

### Corps.cpp/Corps.h
Classe controllant le pignon crémaillère et l'aimant attacher au corps du robot. Permet d'ajouter une couche d'abstraction. Contient des fonctions permettant de monter, baisser et rapprocher l'elctroaimant ainsi que pour l'activer et le désactiver.

### DXL_Corps.cpp/DXL_Corps.h
Classe permettant de controller le moteur dynamixel en position de la crémailliere. Contient les positions d'angle voulu et la fonction go_to_position qui permet de demmander au moteur à ce rendre à la position demander.

### Patte.cpp/Patte.h
Classe controllant les pattes du robot ainsi que l'électroaimant attacher a cette dernière. Permet d'ajouter une couche d'abstraction. Contient des fonctions permettant d'étier et de replier la patte ainsi que pour activer et désactiver les électroaimants.

### DXL_Patte.cpp/DXL_Patte.h
Classe permettant de controller le moteur dynamixel en vitesse attacher à une patte. Contient les positions d'angle voulu et est mis en fonction grace à la fonction setVitesse.

### timer.cpp/timer.h
Contient un timer permettant d'ajouter des délais non bloquant.
init permet de déterminer la longeur du délai voulu et le nombre de répetition.
start commence le timer
update permet de mettre à jour le compteur, si le temps est écouler retourne true sinon retourne false

### Arduino_function.c/Arduino_function.h
Contient des marco de fonction propre à arduino afin de pouvoir simuler ces dernières lors des tests de séquence du moteur. 


### Dynamixel2ArduinoSimul.cpp/Dynamixel2ArduinoSimul.h
Permet de simuler les fonctions importante de la librairie Dynamixel2Arduino.h lorsque le code est rouler en mode test.

### SerialSimul.h/SerialSimul.cpp
Permet de simuler le fonctionnement de l'objet Serial de Arduino. Tout les messages son également écrit dans un fichier de log lorsque le code est rouler en mode test.

### OpenCR.ino
Fichier arduino contenant les fonctions setup, loop ainsi que la fonction SerialEvent1 permettant de gérer les messages UART entrant. Ce fichier contient que les appels de fonction principal permettant d'initialiser le robot et les fonctions appeler dans la loop principal.

### test.cpp
Réplique le fichier OpenCR.ino à l'exception des communications UART. Commence également en mode automatique pour pouvoir tester la séquence à l'aide d'un ordinateur linux en simulation sans avoir à utiliser la carte OpenCR

### Moteur.h
Classe abstraite des moteurs

### Dynamixel.h
Contient tout les constantes et informations lié au moteur dynamixel. Décide également si la librairie Dynamixel2Arduino.h ou Dynamixel2ArduinoSimul.h est utilisé dépendament si le code est rouler sur une carte OpenCR ou non.
