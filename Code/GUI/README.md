# Interface graphique

Le GUI permet d'envoyer des commandes à partir de l'interface jusqu'au robot et ce grâce à une connexion sans fil Bluetooth. Il est possible dans   le GUI d'accéder à deux fenêtres de contrôle distinctes.Une seule des deux fenêtre peut être ouverte à la fois, rnedant plus prévisible et sécuritaire l'utilisation du robot. La fenêtre de contrôle automatique du robot permet de faire avancer le robot sans arrêt, d'une distance entrée, d'une séquence à la fois, la séquence étant toutes les étapes permettant de faire avancer le robot d'une seule longueur de patte, d'une étape de la séquence à la fois et d'arrêter le mouvement du robot. La fenêtre de contrôle manuel du robot permet de bouger individuellement les sections du robot, comprenant la patte avant, le corps avec l'actuateur linéaire et la patte arrière, ainsi que d'activer et désactiver les électroaimants du robot par sections. Des fenêtres d'erreur apparaissent lorsque le robot, en mode manuel, effectuerait une action dommageable pour le robot à la suite d'une commande. Une telle action serait par exemple de déplacer la patte avant du robot alors que ses électroaimants sont activés, pouvant ainsi potentillement briser le robot physiquement. L'interface utilisateur final est le fichier CPU_GUI_FINAL.py.

## Fenêtre pour l'utilisation manuelle

Les différentes sections et composantes du robot peuvent être contrôlées individuellement à l'aide de la fenêtre d'utilisation manuelle.
![controle_manuel](https://user-images.githubusercontent.com/94627446/231640123-2a4d3360-ad61-47b1-a2bb-98ad89a9d2e0.png)


Les pattes et l'actuateur linéaire peuvent être déplacés individuellement et les électroaimants peuvent être activés et désactivés par section, le tout de façon sécuritaire en empêchant des configurations qui pourraient endommager le robot et ses composantes. La représentation visuelle du robot permet de voir si les pattes et l'actuateur sont séparément en extension ou rétractés et quels électroaimants sont activés ou désactivés.
D'abord la patte arrière rétractée avec les électroaimants activés ou désactivés:
<p align="justify">
  <img src="https://user-images.githubusercontent.com/94627446/228851858-82b88dfc-8292-4e39-bd3b-f0a9d80a2d4f.png" width="300"/>
  
  <img src="https://user-images.githubusercontent.com/94627446/228851768-2b2031b8-d3b5-4c7e-9bc5-9b961d7f3be5.png" width="300"/>
<p>
 Puis la patte arrière en extension avec les électroaimants activés ou désactivés:
<p align="justify">  
  <img src="https://user-images.githubusercontent.com/94627446/228851738-10d79a3d-7274-42be-8324-fc0ec2f17d82.png" width="300"/>
  <img src="https://user-images.githubusercontent.com/94627446/228851945-84b4fc03-1fa6-4049-96f9-534a335ea05f.png" width="300"/>
<p>
Des boîtes de message d'erreurs apparaissent lorsque l'utilisateur appuie sur un bouton menant à une configuration interdite, par soucis de ne pas endommager le robot. Une brève description de l'erreur est affichée et la fenêtre du GUI est inaccessible jusqu'à ce que l'utilisateur reconnaisse l'erreur en appuyant su le bouton 'OK'. Dans ce cas-ci le bouton Bouger patte avant est appuyé alors que les électroaimants de la patte avant sont activés:
  
![errerur_bouger](https://user-images.githubusercontent.com/94627446/228865240-c2bc4be5-c18b-4249-8ae5-c49529b22be3.png)

## Fenêtre pour l'utilisation automatique
La fenêtre automatique permet de contrôler le robot pour qu'il accomplisse différentes actions en lien direct avec le déplacement linéaire du robot sur la surface métallique. Les options de contrôlent incluent le déplacement du robot sans arrêt avec le bouton Avancer, le déplacement une séquence à la fois avec le bouton Séquence, le déplacement une étape de la séquence à la fois avec le bouton Étapes, le déplacement en entrant une distance puis en appuyant sur le bouton Avancer et arrêter le robot à tout moment avec le bouton ARRÊT.
![controle_automatique](https://user-images.githubusercontent.com/94627446/231640151-8f31da65-d9af-4f6e-9f83-932d29a607ed.png)

