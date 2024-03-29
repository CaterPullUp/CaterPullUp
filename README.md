# CaterPullUp
<p style="text-align: justify;">
  Le projet de l’équipe CPU vise à améliorer et modifier un projet existant. Il s’agit du robot
quadrupède pouvant se déplacer sur des surfaces métalliques à la verticale CampUS (https://github.com/UdeS-GRO/CampUS). Ce
projet fut réalisé en 2022 par des étudiants de robotique de la promotion 66 de l’Université de
Sherbrooke. L’idée d’un robot pouvant gravir des surfaces perpendiculaires au sol a plu à notre
équipe. L’équipe pense pouvoir optimiser la conception du robot pour accomplir une même tâche.
Toutefois, le mouvement du robot sera inspiré d’une chenille au lieu d’un insecte ou d’un animal
quadrupède. Cela permettra de simplifier le modèle et de diminuer le nombre de composantes du
robot diminuant ainsi son poids.
</p>



<p align="justify">
  <img src="https://user-images.githubusercontent.com/93997878/228574849-a6ea7353-1c47-4b25-a4ec-31b0bc72ba3e.png" alt="Figure 1: Allo" style="margin-right:1000px" width="400" />
  <img src="https://user-images.githubusercontent.com/93997878/228589013-9cc0341d-c45c-4e49-b7da-f8ef00dbbda3.png" style="margin-left:1000px" width="400" />
</p>
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; Figure 1: Robot de CampUS&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Figure 2: Robot de CatterPullUp

## Description du robot CaterPullUp
Le robot se déplace à l'aide de deux pattes ayant deux degrés de liberté. Il est dans l'incapacité de tourner. Cependant, cela accentue sa vitesse de manière significative, car il n'a que deux pattes à mouvoir. Deux électroaimants par patte ainsi qu'un gros électroaimant supporté par un système de crémaillère permettent au robot de se maintenir à la verticale sur un mur métallique aimanté. Tous les composants (moteurs, électroaimants) du robot sont controllés à l'aide d'une carte OpenCr qui utilise le language C++. Le tout est controllé à partir d'une interface utilisateur qui offre un mode manuel (contrôle des composantes individuelles) et un mode automatique (parcours une distance donnée). L'interface est suffisamment sécurisé pour empêché le robot de tomber, car il empêche l'exécution des séquences de mouvements pouvant entrainer sa chute. Par contre, l'interface à de la difficulté à gérer les données lorsque l'utilisateur appui sur un même bouton de manière répété et rapide. C'est un cas limite qui n'est pas géré. Aussi, l'interface communique avec le ESP32 à l'aide du Bluetooth.
### Dimensions
![DimensionsRobot](https://user-images.githubusercontent.com/93997878/228887112-465a8c42-a3ef-4334-b0ab-079351aa499e.png)
### Démonstration du robot en mouvement
<!-- https://youtube.com/shorts/IAFNHkEL4pA?feature=share                https://youtu.be/xv_MGWrIb7o -->

<a href="https://youtube.com/shorts/IAFNHkEL4pA?feature=share
" target="_blank"><img src="https://user-images.githubusercontent.com/93997878/232250133-6b04f28a-0d83-4c91-bd9e-4a6ea785202f.png" 
alt="IMAGE ALT TEXT HERE"  border="10" /></a>
<a href="https://youtu.be/xv_MGWrIb7o
" target="_blank"><img src="https://user-images.githubusercontent.com/93997878/232250300-230997d2-9676-4dd9-aa2f-3fb49adfd2ac.png" 
alt="IMAGE ALT TEXT HERE"  border="10" /></a>

## Comment se retrouver dans le GitHub CaterPullUp
### Code
Tout le code pour contrôller le robot se trouve dans le dossier *Code*, puis dans le dossier *Embarqué*. Ensuite le code du Bluetooth est dans le dossier *ESP32* alors que tout le reste du code se trouve dans le dossier *OpenCr*.
### Mécanique
Toute la conception mécanique du robot se trouve dans le *ReadMe* du dossier *Mécanique*. Un lien au début du fichier mène au logiciel Onshape où se trouve l'intégralité des fichiers 3D. Un guide d'assemblage pour le robot est fourni dans le dossier *Mécanique*. Seuls les fichiers d'impression ne sont pas fournis.
### Électrique
Le schéma électrique, le schéma d'architecture ainsi que le plan de test détaillé du circuit électrique se trouve dans le dossier.

## Étapes pour faire fonctionner le robot rapidement
1. Achetez la liste de composantes dans la liste de pièces (voir fichier joint) .
2. Suivez le lien vers le dossier Onshape dans le ReadMe mécanique pour imprimer toutes les pièces en 3D.
3. Assemblez le robot à l'aide du guide d'assemblage dans le dossier mécanique
4. Soudez la plaquette électrique de montage à l'aide du schéma électrique dans le dossier électrique et effectuer les branchements nécessaires.
5. Télécharger le dépôt GitHub sur votre ordinateur
6. Assurez-vous que la version de votre logiciel Python soit 3.5 ou plus récent
7. Indiquez l'adresse MAC de votre ESP32 dans le code python.
8. Construire et exécuter le code dans l'OpenCr.
9. Ouvrir l'interface graphique et essayer les différentes fonctions pour déplacer le robot.


## Améliorations proposées
- Incurver le support d'électroaimants pour les pattes afin de pouvoir grimper sur une cuve métallique 
- Ajouter un système permettant aux pattes du robot pour rajouter un degré de liberté

## Autre
Pour toutes questions en lien avec le projet, l'équipe CaterPullUp sera ravi de répondre à vos questions.
### Auteurs
- Logan Cadorette - cadl5028
- Justin Coulombe - couj0902
- Étienne Germain - gere3002
- Marie-Claude Montgomery-Verrier – monm1101
- Aude Regnault - rega2002
- Mathieu Trudelle - trum1304



