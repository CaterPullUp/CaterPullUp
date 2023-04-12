# Mécanique

Une partie de la conception mécanique de CaterPullUp est inspiré du projet CampUS. Toute la modélisation 3D de CaterPullUp a été réalisé dans le logiciel Onshape. Cliquer [ici](https://cad.onshape.com/documents/3c73fee9bf57c2c5b861bb17/w/154a3ba2025068c5d3f15744/e/db63480e0887026873e43c01?renderMode=0&uiState=63f40d451734342db4c29fde) pour accéder au modèle sur Onshape. Celui-ci est composé de 2 pattes et d'un actuateur linéaire ayant chacun deux électroaimants

<!-- ## Aperçu 
Voici un aperçu de CaterPullUp. 

![CaterPullUp mi-session](https://user-images.githubusercontent.com/91679469/220222383-99d5307a-1365-44f8-9ba5-3dd9ec28e878.png) -->

## Pattes
Voici un aperçu de la patte :

![Patte mi-session](https://user-images.githubusercontent.com/91679469/220223213-e4558a8e-8ae1-4b7b-9225-d5021217ddf0.jpg)

Les deux pattes sont identiques. Celles-ci ont été conçues grâce à un mécanisme à 4 barres pour créer un mouvement fluide en utilisant un seul moteur par patte. 

## Actuateur linéaire
L'actuateur linéaire sert à aider une patte à soutenir le corps lorsque l'autre fait son déplacement. Un moteur DYNAMIXEL XL430-W250-T est utilisé pour faire tourner l'engrenage qui fait déplacer linéairement la crémaillère.

![Pignion Crémaillère mi-session](https://user-images.githubusercontent.com/91679469/220225627-d1ae4e33-2616-47a2-b0b4-71f066dd411d.png)

## Corps
Le corps de CaterPullUp est découpé au laser dans du bois. Chaque composante de CaterPullUp a sa propre place sur le corps avec des trous pépercer à la découpe laser.

![Corps mi-session](https://user-images.githubusercontent.com/91679469/220228163-77db5452-5665-4c26-a011-d5c62c0b76ea.png)

## Calculs pour la conception
### Déflection maximale de la crémaillère sans glissière.
<p align="justify">
    <img src="https://user-images.githubusercontent.com/93997878/230128710-629a4dca-6900-4858-b513-a47c867ad3b3.png" width="400" />
</p>
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; Figure 1: DCL de la crémaillère&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;<br>



 
 $d_{max} = \frac{F L^3}{3 E I} = 11,009\ mm$

où 

$I = \frac{bh^3}{12} = 1.707\times10^{-9}\ \mathrm{m^4}$

$L = 0.04157\ \mathrm{m}$

$F = ma = 1.962\ \mathrm{N}$

$E = 2.5\times10^6\ \mathrm{Pa}$

Une déflexion de $1,1\ \mathrm{cm}$ est plutôt considérable sachant que la crémaillère est en PLA et est relativement courte. Pour empêcher une telle déflexion, l'équipe a décidé d'insérer la crémaillère dans une glissière réduisant ainsi la longueur L a une longueur suffisamment courte pour réduire la déflexion pratiquement à une valeur nulle. Voici à quoi ressemble le système de crémaillère final: 

<p align="justify">
    <img src="https://user-images.githubusercontent.com/93997878/230170310-50b90960-2c5d-4ecd-b2da-823ab6590e82.png" width="500" />
</p>



### Le couple maximal du moteur XL est-il suffisant pour l'application de la crémaillère?
Trouver la force normale: $F_{normal} = F = 1,962\ \mathrm{N}$

Trouver la force de friction: $F_{f} = F_{normal} *tan(&alpha;) = 0,717\ \mathrm{N}$

où 

$&alpha; = angle\ de\ pression\ de\ l'engrenage = 20\ \mathrm{degrés}$



Trouver le coefficient de frottement causé par les forces: $&mu; = \frac{F_{f}}{F_{normal}} = 0,365\$

Trouver le couple nécessaire pour soulever la crémaillère: $T = F_{normal} *r_{engrenage} *&mu; = 0,007\ \mathrm{Nm}$

où

$r_{engrenage} = 0,01\ \mathrm{m}$

Comme $0,007\ \mathrm{Nm}$ est inférieur à $1\ \mathrm{Nm}$ soit le couple maximal toléré par le moteur, le moteur n'aura aucune difficulté à soulever la crémaillère.

### Le couple maximal du moteur XM est-il suffisant pour soulever le robot?
![image](https://user-images.githubusercontent.com/93997878/230193524-332110be-6884-417c-95c4-5cb6233dd468.png)
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; Figure 1: Diagramme de corps libre du robot 

À la figure 1, il est possible de voir les diagrammes de corps libre du robot. L'équipe a décidé que la modélisation du système était relativement compliqué (DCL officiel). C'est pourquoi elle a décidé de simplifier le diagramme pour correspondre au DCL simplifié de la figure 1. Le système simplifié a ensuite été modélisé dans le logiciel Pycharm en language python. Dépendamment de l'angle qB, le couple du moteur augmente considérablement. Cela est normal étant donné que les deux segments n'ont pas la même longueur, et que, par conséquent il y a un moment où la montée est bloqué par la glissière. À la figure 2, il est possible de voir la progression du couple moteur en fonction de l'angle qB. Comme le couple maximal supporté par un moteur XM est de 4,1 Nm (12 V) et que le système des pattes ne dépasse jamais 90 degrés, le moteur supportera sans difficulté le poids du robot à la vertical. En effet, à 90 degrés, selon la figure 2, seul 1,7 Nm est demandé au moteur.
![GraphiqueAngle](https://user-images.githubusercontent.com/93997878/231544480-094507a2-e6f3-4829-9744-d2cc1ba0a2c4.png)

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Figure 2

Le modèle a quelques failles. Tout d'abord, seul un moteur est considéré alors que dans la réalité, deux moteurs supportent le poids du corps et un électroaimant (celui du corps) allège également la charge sur les moteurs pour maintenir le robot à la vertical. Ensuite, le système est simplifié à l'extrême. En réalité, il n'y a pas que deux segments qui permettent le mouvement mais 6 segments. 


