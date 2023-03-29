Le GUI permet d'envoyer des commandes à partir de l'interface jusqu'au robot et ce grâce à une connexion sans fil Bluetooth. Pour l'instant, le code du GUI ne permet que d'éventuellement pouvoir appeler des fonctions pour contrôler le robot et envoyer l'information grâce au module Bluetooth de la carte ESP32. Il est possible dans le GUI d'accéder à deux fenêtres de contrôle distinctes. La fenêtre de contrôle automatique du robot permet de faire avancer le robot sans arrêt et de faire avancer le robot d'une distance spécifiée. La fenêtre de contrôle manuel du robot permet de bouger individuellement les sections du robot (patte avant, corps, patte arrière), activer et désactiver les électroaimants sur ces sections, faire avancer le robot étape par étape de la séquence d'un mouvement complet et exécuter une séquence complète de mouvement. Un bouton d'arrêt permet d'arrêter tout mouvement en appuyant les pattes contre la surface à grimper et en activant les électroaimants ce qui permet d'immobiliser le robot sur la surface. 

# Interface graphique

L'interface graphique comprend deux fenêtres distinctes auxquelles il est possible d'avoir accès à partir du GUI. Une seule des deux fenêtre peut être ouverte à la fois, redant plus prévisible et sécuritaire l'utilisation du robot.

## Fenêtre pour l'utilisation manuelle

Les différentes sections et composantes du robot peuvent être contrôlées individuellement à l'aide de la fenêtre d'utilisation manuelle.
PHOTO
Les pattes et l'actuateur linéaire peuvent être déplacés individuellement et les électroaimants peuvent être activés et désactivés par section, le tout de façon sécuritaire en empêchant des configurations qui pourraient endommager le robot et ses composantes. La représentation visuelle du robot permet de voir si les pattes et l'actuateur sont séparément en extension ou rétractés et quels électroaimants sont activés ou désactivés.
PHOTOS
Des boîtes de message d'erreurs apparaissent lorsque l'utilisateur appuie sur un bouton menant à une configuration interdite, par soucis de ne pas endommager le robot. Une brève description de l'erreur est affichée et la fenêtre du GUI est inaccessible jusqu'à ce que l'utilisateur reconnaisse l'erreur en appuyant su le bouton 'OK'.
PHOTO

## Fenêtre pour l'utilisation automatique
