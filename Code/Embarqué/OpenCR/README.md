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
