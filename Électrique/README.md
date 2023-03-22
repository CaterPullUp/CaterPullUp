Ce dossier contient le schéma d'architecture du projet. Ce schéma décrit les relations entre les différents composants du projet. Le schéma électrique du montage décrit quant à lui les branchements et le circuit d'activation des électroaimants.
# Description du cricuit électrique
Sur la carte OpenCr, trois moteurs sont branchés directement sur une alimentation de 12V, avec un fil de 12V, un fil de masse et un fil de communication. Le ESP32 est également connecté à la carte OpenCr via deux fils SCL et SDA et une alimentation de 3,3V.

En ce qui concerne les électroaimants, deux groupes de deux électroaimants sont connectés en parallèle avec une résistance de 10 kilo ohms, un transistor et une diode pour la protection. Deux autres électroaimants fonctionnent sur une alimentation de 5V, pour lesquels un régulateur de tension (*mentionner lequel*) permet de convertir l'alimentation de 12V de la carte OpenCr en 5V. Ces deux électroaimants sont également connectés en parallèle avec une résistance, un transistor et une diode. Les diodes sont placées en parallèle avec les électroaimants pour éviter que ces derniers ne produisent des pics de tension qui pourraient endommager les autres composants du circuit. Les diodes agissent comme des "soupapes" électriques, en permettant au courant de passer dans un seul sens, et en bloquant le courant dans l'autre sens. Ainsi, si une surtension se produit, elle sera "redirigée" par les diodes vers le ground, plutôt que de causer des dommages aux autres composants du circuit.

Tous ces composants ont été soudés sur un petit protoboard pour les compacter. Des tests ont été effectués après la soudure pour vérifier que les connexions étaient bonnes et que le circuit était opérationnel.

## Problèmes rencontrés et solutions mises en place
Cependant, des problèmes ont été rencontrés, notamment une surchauffe des MOSFET qui étaient court-circuités, atteignant une température supérieure à 40 degrés Celsius. Une fois le problème résolu, des dissipateurs thermiques ont été installés par mesure de sécurité pour permettre une meilleure diffusion de la chaleur.

# Plan de test du circuit électrique

|***Description test***|**Action utilisateur**|**Action système**|**Résultat**|
| -: | :- | :- | :- |
|*Fonctionnement individuel (par pair de deux ou seul pour le gros électroaimant) des électroaimants en simulant l’OpenCr avec une source*|Configurer la source à 12V et limiter le courant à 1,5 A.|Source inactive, mais affichant les valeurs correspondantes|Valeurs affichées|
||Configurer une autre source à 3,3 V et limiter le courant à 0,1 A|Source inactive, mais affichant les valeurs correspondantes|Valeurs affichées|
||Brancher les mises à la terre des sources ensemble|||
||Brancher les fils de la première source sur les ports indiqués du « protoboard » (12 V et 0V)|||
||Brancher les électroaimants aux borniers correspondants (\*le bornier isolé est pour le corps)|||
||Brancher les 3 fils sur le bloc de 3 ports. Puis, brancher 2 d’entre eux dans la mise à la terre, et le dernier sur le 3,3 V de la seconde source.  |||
||Activer les sources|2 électroaimants sur 6 devraient s’activer. ||
||Changer le fil sur le 3,3V pour un autre afin de tester une autre paire d’électroaimants|2 différents électroaimants sur les 6 devraient s’activer. Le courant devrait se situer autour de 0,26 A peu importe le fil branché.|<p>0,26 A pour chaque pair de petits électroaimants</p><p>0,26 A pour le gros</p>|
|*Vérification du régulateur de tension de 12V à 5V*|Suivre les étapes du test du fonctionnement individuel des électroaimants, mais brancher uniquement le gros électroaimant du corps au 3,3 V. Les autres électroaimants sont branchés à la mise à la terre. |||
||Activer les sources.|Le gros électroaimant est actif, les autres non. Le courant affiché est autour de 0,26 A. |0,26 A|
||Allumez un multimètre et faites toucher précautionneusement le fil de la mise à la terre à un fil noir (0V) du « protoboard ». |||
||Trouvez le port sur le « protoboard » étiqueté par un 5 et touchez-le précautionneusement avec la borne positive du multimètre.|La tension affichée devrait être située très près de 5V. |5V|
|*Fonctionnement de l’intégralité des électroaimants*|Suivre les étapes du test du fonctionnement individuel des électroaimants, mais brancher tous les électroaimants du bloc de 3 ports à la borne positive de la source de 3,3 V. |Le courant devrait être inférieur à 1 A. |0,76 A|
|*Fonctionnement des électroaimants avec l’OpenCr branché sur une source*|Brancher la source d’alimentation de l’OpenCr.|||
||Brancher les 3 ports des électroaimants du « protoboard » au port correspondant sur l’OpenCr.|||
||Changer dans le code le port de l’électroaimant voulant être testé de LOW à HIGH.|||
||S’assurer que l’alimentation soit active. Exécuter le code.|Les électroaimants branchés sur les ports mis à HIGH devraient s’activer. Les critères de courant sont les mêmes que les tests avec la source. ||


![Circuit électrique du projet](Aspose.Words.30f0346e-fbb0-458f-a6d3-985c936bfdf7.001.png)![Une image contenant diagramme, schématique
![Pignion Crémaillère mi-session](https://user-images.githubusercontent.com/91679469/220225627-d1ae4e33-2616-47a2-b0b4-71f066dd411d.png)
Description générée automatiquement](Aspose.Words.30f0346e-fbb0-458f-a6d3-985c936bfdf7.002.png)

