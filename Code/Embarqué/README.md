# Embarqué
Le répertoire Embarqué contient 2 répertoires contenant les codes respectifs de la carte OpenCr et de la carte ESP32.

## Carte OpenCr
La carte OpenCr s'occupe du contrôle bas niveau du robot. En effet, le contrôle des moteurs et des électroaimants est fait par cette carte. De plus, la séquence de mouvement du robot est gérée par cette carte en fonction des messages reçus par UART.

## Carte ESP32
La carte ESP32 agit comme intermédiaire entre l'interface utilisateur et la carte OpenCr. L'interface établit une connexion Bluetooth avec l'ESP32 et lui transmet des messages. La conformité des messages est validée selon la parité par l'ESP32, puis les messages sont traités et simplifiés pour être transmis à la carte OpenCr par UART.
