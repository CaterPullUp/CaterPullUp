# CaterPullUp
<p style="text-align: justify;">
  Le projet de l’équipe CPU vise à améliorer et modifier un projet existant. Il s’agit du robot
quadrupède pouvant se déplacer sur des surfaces métalliques à la verticale nommé CampUS. Ce
projet fut réalisé en 2022 par des étudiants de robotique de la promotion 66 de l’Université de
Sherbrooke. L’idée d’un robot pouvant gravir des surfaces perpendiculaires au sol a plu à notre
équipe. L’équipe pense pouvoir optimiser la conception du robot pour accomplir une même tâche.
Toutefois, le mouvement du robot sera inspiré d’une chenille au lieu d’un insecte ou d’un animal
quadrupède. Cela permettra de simplifier le modèle et de diminuer le nombre de composantes du
robot diminuant ainsi son poids.
</p>



<p align="justify">
  <img src="https://user-images.githubusercontent.com/93997878/228574849-a6ea7353-1c47-4b25-a4ec-31b0bc72ba3e.png" alt="Figure 1: Allo" style="margin-right:1000px" width="500" />
  <img src="https://user-images.githubusercontent.com/93997878/228589013-9cc0341d-c45c-4e49-b7da-f8ef00dbbda3.png" style="margin-left:1000px" width="500" />
</p>
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; Figure 1: Robot de CampUS&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Figure 2: Robot de CatterPullUp

## Description du robot CaterPullUp
Le robot se déplace à l'aide de deux pattes ayant deux degrés de liberté. Il est dans l'incapacité de tourner. Cependant, cela accentue sa vitesse de manière significative, car il n'a que deux pattes à mouvoir. Deux électroaimants par patte ainsi qu'un gros électroaimant supporté par un système de crémaillère permettent au robot de se maintenir à la verticale sur un mur métallique aimanté. Tous les composants (moteurs, électroaimants) du robot sont controllés à l'aide d'une carte OpenCr qui utilise le language C++. Le tout est controllé à partir d'une interface utilisateur qui offre un mode manuel (contrôle des composantes individuelles) et un mode automatique (parcours une distance donnée). L'interface est suffisamment sécurisé pour empêché le robot de tomber, car il empêche l'exécution des séquences de mouvements pouvant entrainer sa chute. Par contre, l'interface à de la difficulté à gérer les données lorsque l'utilisateur appui sur un même bouton de manière répété et rapide. C'est un cas limite qui n'est pas géré. Aussi, l'interface communique avec le ESP32 à l'aide du Bluetooth.
### Dimensions
![DimensionsRobot](https://user-images.githubusercontent.com/93997878/228887112-465a8c42-a3ef-4334-b0ab-079351aa499e.png)
### Démonstration du robot en mouvement
<!-- Insérer la vidéo -->

## Comment se retrouver dans le GitHub CaterPullUp
### Code
### Mécanique
### Électrique




