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

![image](https://user-images.githubusercontent.com/93997878/230128710-629a4dca-6900-4858-b513-a47c867ad3b3.png)

 
 $d_{max} = \frac{F L^3}{3 E I} = 11,009\ mm$

où 

$I = \frac{bh^3}{12} = 1.707\times10^{-9}\ \mathrm{m^4}$

$L = 0.04157\ \mathrm{m}$

$F = ma = 1.962\ \mathrm{N}$

$E = 2.5\times10^6\ \mathrm{Pa}$

