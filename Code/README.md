### Architecture générale du fonctionnement du robot

Pour mettre sur pied un robot capable de grimper sur des murs métalliques grâce à l'utilisation d'électroaimants, il a fallut établir une architecture de contrôle. Celle-ci est décrite dans les lignes qui suivent. Le contrôle de ce robot se fait via une interface graphique utilisateur (GUI) installée sur un Raspberry Pi. Pour permettre cette communication entre le Raspberry Pi et le robot, un système de communication sans fil est utilisé, en l'occurrence le Bluetooth.

Le Bluetooth a été choisi car il est suffisamment puissant pour fournir une connexion stable à courte portée entre le Raspberry Pi et l'ESP32, qui sert de passerelle de communication entre le Raspberry Pi et la carte OpenCr. Cette dernière est chargée d'envoyer les informations nécessaires aux différentes composantes embarquées sur le robot, telles que les électroaimants, les moteurs ou la crémaillère.

La communication entre les différentes cartes électroniques se fait via le protocole I2C, qui est largement utilisé dans les systèmes embarqués en raison de sa simplicité, de sa fiabilité et de sa faible consommation d'énergie. C'est d'ailleurs pour cette raison que ce protocole a été sélectionné. Le protocole I2C permet une communication bidirectionnelle entre un maître et plusieurs esclaves, et il est basé sur une paire de fils, SDA et SCL, qui permettent la transmission de données. Le fait qu'il soit limité en termes de bande passante, ce qui signifie qu'il peut ne pas être adapté aux applications nécessitant des taux de transfert de données très élevés n'est pas préoccupant dans l'application courante puisque le nombre de données transférées ne sera pas suffisant pour causer ce genre de problèmes.


