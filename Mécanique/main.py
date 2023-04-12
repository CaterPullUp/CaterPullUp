#Auteur: Logan Cadorette
#Description:
"""
Ce code génère des graphiques représentant le couple nécessaire pour soulever le robot de 37 mm
en fonction de l'angle du moteur par rapport à la verticale. Pour ce modèle le
moteur est en haut (à la place de l'électroaimant et la patte n'est que 2 barres
attaché par un joint libre et dont l'extrémité de la barre attachée à la barre fixée au moteur est
est coincé dans une glissière verticale.
"""


import math
import matplotlib.pyplot as plt



def calculate_tau(qB_deg):
    # Longueurs des barres en mm
    L1 = 174/1000
    L2 = 116/1000
    distance = 37/1000

    # Angle entre la barre de 174 mm et celle de 116 mm
    qA = math.atan2(L2, L1)

    # Angle entre la verticale et la barre de 174 mm
    qB = math.radians(qB_deg)

    # Angle entre la verticale et la barre de 116 mm
    qC = math.atan2(distance, L2)

    # Distance de l'extrémité de la deuxième barre au point de pivot
    r = L1 * math.sin(qA)

    # Calcul de la force nécessaire pour soulever la charge de 4,905 N (poids/2)
    F = 4.905 / math.cos(qC - qB)

    # Calcul du couple nécessaire par le moteur
    tau = F * r

    return tau

def plot_torque(qB_range, tau_list, title):
    plt.plot(qB_range, tau_list)
    plt.xlabel('Angle qB (degrés)')
    plt.ylabel('Couple nécessaire (N.m)')
    plt.title(title)
    plt.grid()
    plt.xticks(range(0, 121, 5), rotation=45)
    plt.yticks(range(0, 56, 5))
    plt.xlim(0, 120)
    plt.ylim(0, 55)
    plt.show()

def main():
    # Plage d'angles qB en degrés
    qB_range = range(0, 181, 1)

    # Liste pour stocker les couples nécessaires
    tau_list = []

    for qB_deg in qB_range:
        tau = calculate_tau(qB_deg)
        tau_list.append(tau)

    # Affichage du premier graphique des couples nécessaires en fonction de l'angle qB
    plt.figure()
    plt.plot(qB_range, tau_list)
    plt.xlabel('Angle qB (degrés)')
    plt.ylabel('Couple nécessaire (N.m)')
    plt.title('Plage complète')
    plt.grid(True)

    # Affichage du deuxième graphique des couples nécessaires en fonction de l'angle qB
    plt.figure()
    plt.plot(qB_range[30:116], tau_list[30:116])
    plt.xlabel('Angle qB (degrés)')
    plt.xticks(range(30, 116, 5))
    plt.ylabel('Couple nécessaire (N.m)')
    plt.yticks(range(0, 56, 5))
    plt.ylim(0, 55)
    plt.title('Plage limitée')
    plt.grid(True)

    # Affichage du troisième graphique des couples nécessaires en fonction de l'angle qB
    plt.figure()
    plt.plot(qB_range[30:106], tau_list[30:106])
    plt.xlabel('Angle qB (degrés)')
    plt.xticks(range(30, 106, 5), rotation=45)
    plt.ylabel('Couple nécessaire (N.m)')
    plt.yticks(range(0, 16, 1))
    plt.ylim(0, 15)
    plt.title('Plage limitée et angles inclinés')
    plt.grid(True)

    plt.show()
def plot_graph4():
    # Plage d'angles qB en degrés
    qB_range = range(28, 103, 1)

    # Liste pour stocker les couples nécessaires
    tau_list = []

    for qB_deg in qB_range:
        tau = calculate_tau(qB_deg)
        tau_list.append(tau)

    # Affichage du graphique des couples nécessaires en fonction de l'angle qB
    fig, ax = plt.subplots()
    ax.plot(qB_range, tau_list)
    ax.set_xlabel('Angle qB (degrés)')
    ax.set_ylabel('Couple nécessaire (N.m)')
    ax.set_title('Graphique 4 : Angle qB de 28 à 102 degrés')
    ax.set_xticks(range(28, 103, 10))
    ax.set_yticks(range(0, 10, 1))
    plt.ylim([0, 10])
    plt.grid(True)
    plt.show()

def get_tau_for_qB(qB_deg):
    # Calcul du couple nécessaire pour l'angle qB spécifié en degrés
    tau = calculate_tau(qB_deg)
    return tau
if __name__ == '__main__':
    main()
    plot_graph4()

