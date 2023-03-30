Le GUI permet d'envoyer des commandes à partir de l'interface jusqu'au robot et ce grâce à une connexion sans fil Bluetooth. Pour l'instant, le code du GUI ne permet que d'éventuellement pouvoir appeler des fonctions pour contrôler le robot et envoyer l'information grâce au module Bluetooth de la carte ESP32. Il est possible dans le GUI d'accéder à deux fenêtres de contrôle distinctes. La fenêtre de contrôle automatique du robot permet de faire avancer le robot sans arrêt et de faire avancer le robot d'une distance spécifiée. La fenêtre de contrôle manuel du robot permet de bouger individuellement les sections du robot (patte avant, corps, patte arrière), activer et désactiver les électroaimants sur ces sections, faire avancer le robot étape par étape de la séquence d'un mouvement complet et exécuter une séquence complète de mouvement. Un bouton d'arrêt permet d'arrêter tout mouvement en appuyant les pattes contre la surface à grimper et en activant les électroaimants ce qui permet d'immobiliser le robot sur la surface. 

# Interface graphique

L'interface graphique comprend deux fenêtres distinctes auxquelles il est possible d'avoir accès à partir du GUI. Une seule des deux fenêtre peut être ouverte à la fois, redant plus prévisible et sécuritaire l'utilisation du robot.

## Fenêtre pour l'utilisation manuelle


Les différentes sections et composantes du robot peuvent être contrôlées individuellement à l'aide de la fenêtre d'utilisation manuelle.
![Manuel_GUI](https://user-images.githubusercontent.com/94627446/228851357-da047edc-61ed-49c3-8a4d-e6e5aa4af75a.png)
Les pattes et l'actuateur linéaire peuvent être déplacés individuellement et les électroaimants peuvent être activés et désactivés par section, le tout de façon sécuritaire en empêchant des configurations qui pourraient endommager le robot et ses composantes. La représentation visuelle du robot permet de voir si les pattes et l'actuateur sont séparément en extension ou rétractés et quels électroaimants sont activés ou désactivés.
![basActifVert](https://user-images.githubusercontent.com/94627446/228851738-10d79a3d-7274-42be-8324-fc0ec2f17d82.png)
![basDesacRouge](https://user-images.githubusercontent.com/94627446/228851768-2b2031b8-d3b5-4c7e-9bc5-9b961d7f3be5.png)
![basDesacVert](https://user-images.githubusercontent.com/94627446/228851858-82b88dfc-8292-4e39-bd3b-f0a9d80a2d4f.png)
![basActifRouge](https://user-images.githubusercontent.com/94627446/228851945-84b4fc03-1fa6-4049-96f9-534a335ea05f.png)
Des boîtes de message d'erreurs apparaissent lorsque l'utilisateur appuie sur un bouton menant à une configuration interdite, par soucis de ne pas endommager le robot. Une brève description de l'erreur est affichée et la fenêtre du GUI est inaccessible jusqu'à ce que l'utilisateur reconnaisse l'erreur en appuyant su le bouton 'OK'.
![Erreur_GUI](https://user-images.githubusercontent.com/94627446/228852111-c7346ffe-d1e6-419e-a459-2d7653ae2985.png)

## Fenêtre pour l'utilisation automatique
La fenêtre automatique permet de contrôler le robot pour qu'il accomplisse différentes actions en lien direct avec le déplacement linéaire du robot sur la surface métallique. Les options de contrôlent incluent le déplacement du robot sans arrêt avec le bouton Avancer, le déplacement une séquence à la fois avec le bouton Séquence, le déplacement une étape de la séquence à la fois avec le bouton Étapes, le déplacement en entrant une distance avec le bouton Entrer une distance (mm) et arrêter le robot à tout moment avec le bouton ARRÊT.
![Auto_GUI](https://user-images.githubusercontent.com/94627446/228856085-ac5462e7-6c2c-4721-94dc-9d6942b756be.png)
