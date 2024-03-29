from tkinter import *
from tkinter import messagebox
from PIL import Image, ImageTk

import socket
import struct
import time


# Changer pour l'adresse mac de l'appareil utilise
sensorMACAddress = '80:7d:3a:b9:33:e2'
port = 1

# Creation du socket pour la communication bluetooth
s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)


try:
    s.connect((sensorMACAddress,port))

except TimeoutError:
    print("Connection error")

else:
    print("Connection successfull")


def macbinaire(mac_adress):
    '''
    Cette fonction convertit une adresse mac en base 16 en 'str' vers un entier 'int'
    representant l'adresse mac en binaire sous 8 bits.
    INPUT: 
        mac_adress: l'adresse mac sous forme de 'str'
    OUTPUT: 
        macbin: un 'int' representant l'adresse mac en binaire sous 8 bytes
    '''
    mac_sections=[]
    shifter=5
    for section in mac_adress.split(':'):
        mac_sections.append(int(section, base=16)<<8*shifter)
        shifter-=1
    macbin = mac_sections[0]
    mac_sections.pop(0)
    for mac in mac_sections:
        macbin|=mac

    print(macbin)
    return macbin

def config_bloc_envoi(MAC,commande,DISTANCE=0):
    '''
    Configure le bloc d'envoi pour avoir la structure globale voulue. L'ajout de la parite, de la fonction a envoyer et
    de la distance a parcourir dans le cas de la fonction avancer par distance seront ajoutees juste avant l'envoi.
    INPUT: 
        mac_adress: L'adresse mac sous forme hexadecimale
    OUTPUT: 
        Le bloc de message d'envoi dans sa structure globale.
    '''
    SOF=3
    EOF=5
    return(SOF<<70)|(commande<<64)|(MAC<<16)|(DISTANCE<<4)|EOF
    
def modif_parite(msg):
    '''
    Modification du bit de partie du message pour assurer l'integrite du message lors de la reception. La parite paire
    fut choisie.
    INPUT: 
        msg: Le message a envoyer complet, mais sans partie
    OUTPUT: 
        msg: Le message pret a etre envoye
    '''
    ind = 0
    msg_bin = bin(msg)
    for i in msg_bin:
        if i=='1':
            ind+=1
        else:
            pass
    if ind%2 != 0:
        msg = msg|(1<<3)
    else:
        pass
    return msg

def reconnect():
    '''
    Le GUI essaie de se reconnecter bluetooth lorsque la carte ne repond plus. Le GUI ne repond plus pendant la reconnexion.
    INPUT:
        Aucun input
    OUTPUT:
        Aucun output en soi, le GUI est reconnecte au bluetooth a la sortie de la fonction
    '''
    global s
    connected = False
    while(not connected):

        try:
            s.close()
            s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
            s.connect((sensorMACAddress,port))
            print("Reconnected")
            connected = True
            
        except TimeoutError:
            print("Connection error")



#Configuration de la fenetre du GUI
window = Tk()
window.title('CaterPullUp')

window.geometry('+350+10')

window.minsize(width=1000,height=700)
window.maxsize(width=1000,height=1000)

auto_win = Frame(window)
manual_win = Frame(window)

for frame in (auto_win,manual_win):
    frame.grid(row=0,column=0,sticky='nswe')

# Variables pour la gestion du GUI
etat_electroTop = False
etat_electroMid = False
etat_electroBas = False
etat_patteAvant = False
etat_corps = False
etat_patteArriere = False
etape_actuelle = 0
electro_actives = 2
en_action = False

def show_frame(frame):
    frame.tkraise()

def show_manual(frame):
    if en_action:
        messagebox.showerror('Action impossible', "Le robot est déjà en action!", icon='error')
    else:
        reset_manual()
        frame.tkraise()

#WINDOW MANUAL 
def ajout_logo(path,row,column,ratio):
    '''
    Permet d'ajouter un logo dans la fenetre manuelle
    INPUTS: 
        path: Le path de l'image du logo
        row: Ligne de la 'grid' de la fenetre ou sera affiche le logo
        column: Colonne de la 'grid' de la fenetre ou sera affiche le logo
        ratio: Ratio de reduction de l'image
    OUTPUT: 
        Aucun output en soi
    '''
    img = Image.open(path)
    img = img.resize((int(img.size[0]/ratio),int(img.size[1]/ratio)))
    img = ImageTk.PhotoImage(img)
    img_label = Label(manual_win, image=img, bg="white")
    img_label.image = img
    img_label.grid(column=column, row=row, rowspan=1, sticky=E, padx=20, pady=0)

def ajout_image(path,row,column,ratio,stick,rowspan=2,padx=0,pady=0):
    '''
    Permet d'ajouter une image dans la fenetre manuelle
    INPUTS: 
        path: Le path de l'image
        row: Ligne de la 'grid' de la fenetre ou sera affiche l'image
        column: Colonne de la 'grid' de la fenetre ou sera affiche l'image
        ratio: Ratio de reduction de l'image
        stick: Encrage dans la position de la 'grid' entree
        rowspan: Etalement de l'image sur plusieurs positions de la 'grid'
        padx: Espacement en x
        pady: Espacement en y
    OUTPUT: 
        img_lbl: Instance de la class Label associee a l'image
    '''
    img = Image.open(path)
    img = img.resize((int(img.size[0]/ratio),int(img.size[1]/ratio)))
    img = ImageTk.PhotoImage(img)
    img_label = Label(manual_win,image=img, bg="white")
    img_label.image = img
    img_label.grid(column=column, row=row, rowspan=rowspan, sticky=stick, padx=padx, pady=pady)
    return img_label

def ajout_icone(path, row, column, stick, funct, height=70, width=140,ratio=1.5):
    '''
    Permet d'ajouter un icone dans la fenetre manuelle. Un icone est un bouton avec une image pour le representer
    INPUTS:
        path: Le path de l'image de l'icone
        row: Ligne de la 'grid' de la fenetre ou sera affiche l'icone
        column: Colonne de la 'grid' de la fenetre ou sera affiche l'icone
        stick: Encrage dans la position de la 'grid' entree
        funct: Fonction appelee lors de l'appui de l'icone
        height = Hauteur du bouton
        width = Largeur du bouton
        ratio: Ratio de reduction de l'image
    OUTPUT: 
        Aucun output en soi
    '''
    icon = Image.open(path)
    icon = icon.resize((int(icon.size[0]/ratio),int(icon.size[1]/ratio)))
    l_button = int(icon.size[0]/3)+5
    h_button = int(icon.size[1]/3)+5
    icon = ImageTk.PhotoImage(icon)
    icon_label = Button(manual_win,image=icon, command=funct,text="Bouton", width=width, height=height)
    icon_label.image = icon
    icon_label.grid(column=column, row=row, sticky=stick,pady=0)

def reset_manual():
    '''
    Permet de reinitialiser les etats et les images de la fenetre manuelle
    INPUT: 
        Aucun input
    OUTPUT: 
        Aucun output
    '''
    ratio = 5
    #reset des etats
    global etat_electroTop
    global etat_electroMid
    global etat_electroBas
    global etat_patteAvant
    global etat_corps
    global etat_patteArriere
    global etape_actuelle

    etat_electroTop = True
    etat_electroMid = False
    etat_electroBas = True
    etat_patteAvant = False
    etat_corps = False
    etat_patteArriere = False
    etape_actuelle = 0

    #image top
    image_top = Image.open('./topDesacVert.png')
    image_top = image_top.resize((int(image_top.size[0]/ratio),int(image_top.size[1]/ratio)))
    manual_win.new_imageT1 = ImageTk.PhotoImage(image_top)
    topimg.configure(image=manual_win.new_imageT1)
    #image mid
    image_mid = Image.open('./midDesacRouge.png')
    image_mid = image_mid.resize((int(image_mid.size[0]/ratio),int(image_mid.size[1]/ratio)))
    manual_win.new_imageT2 = ImageTk.PhotoImage(image_mid)
    midimg.configure(image=manual_win.new_imageT2)
    #image bas
    image_bas = Image.open('./basDesacVert.png')
    image_bas = image_bas.resize((int(image_bas.size[0]/ratio),int(image_bas.size[1]/ratio)))
    manual_win.new_imageT3 = ImageTk.PhotoImage(image_bas)
    basimg.configure(image=manual_win.new_imageT3)
    
def chg_electroTop(img):
    '''
    Bascule l'etat de l'electroaimant de la patte avant et modifie l'image correspondante. Un message envoye pour l'execution de la commande
    INPUT:
        img: Instance de la classe Label associee a l'image 
    OUTPUT:
        Aucun output en soi
    '''
    ratio = 5
    global etat_electroTop
    global electro_actives
    if etat_electroTop:
            if (electro_actives-1) < 2:
                messagebox.showerror('Action impossible', 'Deux électroaimants doivent être activés en tout temps', icon='error')
                pass
            else:
                electro_actives-=1
                if etat_patteAvant:
                    image = Image.open('./topActifRouge.png')
                else:
                    image = Image.open('./topDesacRouge.png')
                image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
                manual_win.new_imageT = ImageTk.PhotoImage(image)
                img.configure(image=manual_win.new_imageT)
                num_fonction = 8
                etat_electroTop = False
                msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
                print(msg)
                try:
                    s.send(msg.to_bytes(9,"big"))
                except socket.error:
                    reconnect()
                    
    else:
        if etat_patteAvant:
            image = Image.open('./topActifVert.png')
        else:
            image = Image.open('./topDesacVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        manual_win.new_imageT = ImageTk.PhotoImage(image)
        img.configure(image=manual_win.new_imageT)
        num_fonction = 7
        etat_electroTop = True
        electro_actives+=1
        msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
        print(msg)
        try:
            s.send(msg.to_bytes(9,"big"))
        except socket.error:
            reconnect()

def chg_electroMid(img):
    '''
    Bascule l'etat de l'electroaimant du corps et modifie l'image correspondante. Un message envoye pour l'execution de la commande
    INPUT:
        img: Instance de la classe Label associee a l'image 
    OUTPUT:
        Aucun output en soi
    '''
    ratio = 5
    global etat_electroMid
    global electro_actives
    if etat_electroMid:
        if (electro_actives-1) < 2:
            messagebox.showerror('Action impossible', 'Deux électroaimants doivent être activés en tout temps', icon='error')
            pass
        else:
            electro_actives-=1
            if etat_corps:
                image = Image.open('./midActifRouge.png')
            else:
                image = Image.open('./midDesacRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageM = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageM)
            num_fonction = 10
            etat_electroMid = False
            msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
            print(msg)
            try:
                s.send(msg.to_bytes(9,"big"))
            except socket.error:
                reconnect()
    else:
        if etat_corps:
            image = Image.open('./midActifVert.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageM = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageM)
            num_fonction = 9
            etat_electroMid = True
            electro_actives+=1
            msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
            print(msg)
            try:
                s.send(msg.to_bytes(9,"big"))
            except socket.error:
                reconnect()
        else:
            messagebox.showerror('Action impossible', "Descendre d'abord le corps", icon='error')
        
def chg_electroBas(img):
    '''
    Bascule l'etat de l'electroaimant de la patte arriere et modifie l'image correspondante. Un message envoye pour l'execution de la commande
    INPUT:
        img: Instance de la classe Label associee a l'image 
    OUTPUT:
        Aucun output en soi
    '''
    ratio = 5
    global etat_electroBas
    global electro_actives
    if etat_electroBas:
        if (electro_actives-1) < 2:
            messagebox.showerror('Action impossible', 'Deux électroaimants doivent être activés en tout temps', icon='error')
            pass
        else:
            electro_actives-=1
            if etat_patteArriere:
                image = Image.open('./basActifRouge.png')
            else:
                image = Image.open('./basDesacRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageB = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageB)
            num_fonction = 12
            etat_electroBas = False
            msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
            print(msg)
            try:
                s.send(msg.to_bytes(9,"big"))
            except socket.error:
                reconnect()
    else:
        if etat_patteArriere:
            image = Image.open('./basActifVert.png')
        else:
            image = Image.open('./basDesacVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        manual_win.new_imageB = ImageTk.PhotoImage(image)
        img.configure(image=manual_win.new_imageB)
        num_fonction = 11
        etat_electroBas = True
        electro_actives += 1
        msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
        print(msg)
        try:
            s.send(msg.to_bytes(9,"big"))
        except socket.error:
            reconnect()

def move_patteAvant(img):
    '''
    Bascule l'etat de de la patte avant (retractee ou en extension) et modifie l'image correspondante. Un message envoye pour l'execution de la commande
    INPUT:
        img: Instance de la classe Label associee a l'image 
    OUTPUT:
        Aucun output en soi
    '''
    ratio = 5
    global etat_patteAvant
    if etat_patteAvant:
        if etat_electroTop:
            messagebox.showerror('Action impossible', "Désactiver l'électroaimant avant de faire un déplacement", icon='error')
        else:
            image = Image.open('./topDesacRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageT = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageT)
            etat_patteAvant = False
            num_fonction = 2
            msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
            print(msg)
            try:
                s.send(msg.to_bytes(9,"big"))
            except socket.error:
                reconnect()
        
    else:
        if etat_electroTop:
            messagebox.showerror('Action impossible', "Désactiver l'électroaimant avant de faire un déplacement", icon='error')
        else:
            image = Image.open('./topActifRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageT = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageT)
            etat_patteAvant = True
            num_fonction = 1
            msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
            print(msg)
            try:
                s.send(msg.to_bytes(9,"big"))
            except socket.error:
                reconnect()

def move_Corps(img):
    '''
    Bascule l'etat de du corps (actuateur remonte ou descendu) et modifie l'image correspondante. Un message envoye pour l'execution de la commande
    INPUT:
        img: Instance de la classe Label associee a l'image 
    OUTPUT:
        Aucun output en soi
    '''
    ratio = 5
    global etat_corps
    if etat_corps:
        if etat_electroMid:
            messagebox.showerror('Action impossible', "Désactiver l'électroaimant avant de faire un déplacement", icon='error')
        else:
            image = Image.open('./midDesacRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageM = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageM)
            etat_corps = False
            num_fonction = 6
            msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
            print(msg)
            try:
                s.send(msg.to_bytes(9,"big"))
            except socket.error:
                reconnect()
        
    else:
        if etat_electroMid:
            messagebox.showerror('Action impossible', "Désactiver l'électroaimant avant de faire un déplacement", icon='error')
        else:
            image = Image.open('./midActifRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageM = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageM)
            etat_corps = True
            num_fonction = 5
            msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
            print(msg)
            try:
                s.send(msg.to_bytes(9,"big"))
            except socket.error:
                reconnect()

def move_patteArriere(img):
    '''
    Bascule l'etat de de la patte arriere (retractee ou en extension) et modifie l'image correspondante. Un message envoye pour l'execution de la commande
    INPUT:
        img: Instance de la classe Label associee a l'image 
    OUTPUT:
        Aucun output en soi
    '''
    ratio = 5
    global etat_patteArriere
    if etat_patteArriere:
        if etat_electroBas:
            messagebox.showerror('Action impossible', "Désactiver l'électroaimant avant de faire un déplacement", icon='error')
        else:
            image = Image.open('./basDesacRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageB = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageB)
            etat_patteArriere = False
            num_fonction = 4
            msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
            print(msg)
            try:
                s.send(msg.to_bytes(9,"big"))
            except socket.error:
                reconnect()
        
    else:
        if etat_electroBas:
            messagebox.showerror('Action impossible', "Désactiver l'électroaimant avant de faire un déplacement", icon='error')
        else:
            image = Image.open('./basActifRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageB = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageB)
            etat_patteArriere = True
            num_fonction = 3
            msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
            print(msg)
            try:
                s.send(msg.to_bytes(9,"big"))
            except socket.error:
                reconnect()

#Partie du haut
top = Frame(manual_win, width=1000,height=100,bg='#24b700')
top.grid(columnspan=4, rowspan=1, row=0)

#Partie Centrale
mid = Frame(manual_win, width=1000, height=750, bg='white')
mid.grid(columnspan=4, rowspan=5, row=1)

ajout_logo('./chenille_nobg.png', 0, 3, 7)
mode_lbl = Label(manual_win,text='Manuel',fg="white",bg='#24b700',font=('Arial',24,'bold'))
mode_lbl.grid(row=0,column=2)
topimg = ajout_image('./topDesacRouge.png',1,1,5,stick=S,rowspan=1,pady=0)
midimg = ajout_image('./midDesacRouge.png',2,1,5,stick='',rowspan=1,pady=0)
basimg = ajout_image('./basDesacRouge.png',3,1,5,stick=N,rowspan=1)

btn_automatic = Button(manual_win,command=lambda:show_frame(auto_win),text='Changer pour automatique',bg='white',fg='black')
btn_automatic.grid(column=0,row=0,sticky=W,padx=20)

btn_mvmntAvant = Button(manual_win,text="Bouger patte avant", bg="#24b700",fg="white", command=lambda:move_patteAvant(topimg))
btn_mvmntAvant.grid(column=0,row=1,sticky=E)

btn_mvmtCorps = Button(manual_win, text="Bouger corps", bg="#24b700",fg="white", command=lambda:move_Corps(midimg))
btn_mvmtCorps.grid(column=0,row=2,sticky=E)

btn_mvmtArriere = Button(manual_win, text="Bouger patte arrière", bg="#24b700",fg="white", command=lambda:move_patteArriere(basimg))
btn_mvmtArriere.grid(column=0,row=3,sticky=E)

btn_electroAvant = Button(manual_win, command=lambda:chg_electroTop(topimg),text="Modifier électroaimant avant", bg="#24b700",fg="white")
btn_electroAvant.grid(column=2,row=1,sticky=W)

btn_electroCorps = Button(manual_win, command=lambda:chg_electroMid(midimg), text="Modifier électroaimant corps", bg="#24b700",fg="white")
btn_electroCorps.grid(column=2,row=2,sticky=W)

btn_electroArriere = Button(manual_win, command=lambda:chg_electroBas(basimg), text="Modifier électroaimant arrière", bg="#24b700",fg="white")
btn_electroArriere.grid(column=2,row=3,sticky=W)

# Textbox input terminal
text_box_manual = Text(manual_win, height = 45, width = 40, padx = 0, pady = 0,wrap=WORD)
text_box_manual.insert(INSERT, "")
text_box_manual.grid(column=3, row= 1,rowspan=5)

# AUTOMATIC   
def arret(icon_name,lbl):
    '''
    Permet d'envoyer un message d'arret au robot. Cela permet d'arreter l'action en cours.
    INPUT:
        icon_name: icone d'avancement du robot
    OUTPUT:
        Aucun output en soi, mais arrete le robot dans son action en cours
    '''
    global en_action
    if not en_action:
        messagebox.showerror('Action impossible', "Le robot n'est pas en action", icon='error')
    else:
        icon = Image.open("fleche_videR.png")
        icon = icon.resize((int(icon.size[0]/2.5),int(icon.size[1]/2.5)))
        auto_win.fleche = ImageTk.PhotoImage(icon)
        icon_name.configure(image=auto_win.fleche)
        lbl.config(text = 'Le robot est immobile')
        num_fonction = 15
        # La reception veut une distance remplie de 1 en envoyant la commande d'arret
        fill = 4095
        msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction,fill))
        en_action=False
        print(msg)
        try:
            s.send(msg.to_bytes(9,"big"))
        except socket.error:
            reconnect()

def sequence():
    '''
    Permet d'envoyer une commande au robot d'executer une seule sequence.
    INPUT:
        icon_name: icone d'avancement du robot
    OUTPUT:
        Aucun output en soi, mais envoie la commande de sequence au robot
    '''
    global en_action
    if en_action:
        messagebox.showerror('Action impossible', "Le robot est déjà en action!", icon='error')
    else:
        num_fonction = 14
        msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
        print(msg)
        try:
            s.send(msg.to_bytes(9,"big"))
        except socket.error:
            reconnect()

def etapes(progbar_img):
    '''
    Permet d'avancer etape par etape de la sequence le robot et de changer la barre de progression en consideration.
    INPUT:
        progbar_img: Instance de la classe Label associee a l'image de la barre de progression
    OUTPUT:
        Aucun output en soi
    '''
    global etape_actuelle
    global en_action
    if en_action:
        messagebox.showerror('Action impossible', "Le robot est déjà en action!", icon='error')
    else:
        if etape_actuelle != 6:
            etape_actuelle += 1
        else:
            etape_actuelle = 0
        image = Image.open(f'./progbar_{etape_actuelle}.png')
        image = image.resize((int(image.size[0]/2),int(image.size[1]/2)))
        auto_win.new_progbar = ImageTk.PhotoImage(image)
        progbar_img.configure(image=auto_win.new_progbar)
        num_fonction = 13
        msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
        print(msg)
        try:
            s.send(msg.to_bytes(9,"big"))
        except socket.error:
            reconnect()

def ajout_image_auto(path,row,column,ratio,stick=NW,rowspan=1,padx=20,pady=0):
    '''
    Permet d'ajouter une image dans la fenetre automatique
    INPUTS: 
        path: Le path de l'image
        row: Ligne de la 'grid' de la fenetre ou sera affiche l'image
        column: Colonne de la 'grid' de la fenetre ou sera affiche l'image
        ratio: Ratio de reduction de l'image
        stick: Encrage dans la position de la 'grid' entree
        rowspan: Etalement de l'image sur plusieurs positions de la 'grid'
        padx: Espacement en x
        pady: Espacement en y
    OUTPUT: 
        img_name: Instance de la class Label associee a l'image
    '''
    img = Image.open(path)
    img = img.resize((int(img.size[0]/ratio),int(img.size[1]/ratio)))
    img = ImageTk.PhotoImage(img)
    img_name = Label(auto_win,image=img, bg="white")
    img_name.image = img
    img_name.grid(column=column, row=row, rowspan=rowspan, sticky=stick, padx=padx, pady=pady)
    return img_name

def ajout_icone_auto(url, row, column, stick, funct,height=310, width=130,ratiox=2.2,ratioy=1.5,rowspan=1):
    '''
    Permet d'ajouter un icone dans la fenetre automatique. Un icone est un bouton avec une image pour le representer
    INPUTS:
        path: Le path de l'image de l'icone
        row: Ligne de la 'grid' de la fenetre ou sera affiche l'icone
        column: Colonne de la 'grid' de la fenetre ou sera affiche l'icone
        stick: Encrage dans la position de la 'grid' entree
        funct: Fonction appelee lors de l'appui de l'icone
        height = Hauteur du bouton
        width = Largeur du bouton
        ratio: Ratio de reduction de l'image
    OUTPUT: 
        icon_label: Instance de la class Button associee a l'icone
    '''
    icon = Image.open(url)
    icon = icon.resize((int(icon.size[0]/ratiox),int(icon.size[1]/ratioy)))
    l_button = int(icon.size[0]/3)+5
    h_button = int(icon.size[1]/3)+5
    icon = ImageTk.PhotoImage(icon)
    icon_label = Button(auto_win,image=icon, command=funct, width=width, height=height)
    icon_label.image = icon
    icon_label.grid(column=column, row=row, sticky=stick,rowspan=rowspan)
    return icon_label

def avancer_auto(icon_name,lbl,new_text,distance):
    '''
    Permet de faire avancer sans arret le robot ou d'arreter le mouvement sans arret du robot dependemment si l'icone etait prealablement active ou non.
    Envoie aussi un message pour mentionner la fonction d'avancer ou d'arreter le mouvement continu.
    INPUT:
        icon_name: Instance de la class Button associee a l'icone
    OUTPUT:
        Aucun output en soi
    '''
    global en_action
    if en_action:
        messagebox.showerror('Action impossible', "Le robot est déjà en action!", icon='error')
    else:
        if distance == "":
            lbl.config(text = 'Le robot avance sans arrêt')
            icon = Image.open("fleche_pleineV.png")
            icon = icon.resize((int(icon.size[0]/2.5),int(icon.size[1]/2.5)))
            auto_win.fleche = ImageTk.PhotoImage(icon)
            icon_name.configure(image=auto_win.fleche)
            num_fonction = 17
            msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction))
            print(msg)
            
            try:
                s.send(msg.to_bytes(9,"big"))
            except socket.error:
                reconnect()
            en_action = True

        elif distance.isdigit():
            dist_parcour = int(distance)
            if dist_parcour >= 4000:
                lbl.config(text = 'Erreur, max 4000 mm')
            elif dist_parcour < 80:
                lbl.config(text = 'Erreur, min 80 mm')
            else:
                lbl.config(text = new_text)
                icon = Image.open("fleche_pleineV.png")
                icon = icon.resize((int(icon.size[0]/2.5),int(icon.size[1]/2.5)))
                auto_win.fleche = ImageTk.PhotoImage(icon)
                icon_name.configure(image=auto_win.fleche)
                num_fonction = 16
                msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress),num_fonction,dist_parcour))
                print(msg)
                try:
                    s.send(msg.to_bytes(9,"big"))
                except socket.error:
                    reconnect()
                en_action = True
        
        else:
            lbl.config(text = 'Erreur')
        entry_log.delete(0, END)

#Partie du haut
top = Frame(auto_win, width=1000,height=100,bg='#24b700')
top.grid(columnspan=4, rowspan=1, row=0)

#Partie Centrale
mid = Frame(auto_win, width=1000, height=750, bg='white')
mid.grid(columnspan=5, rowspan=7, row=1)

#Controle du robot
ajout_image_auto('./chenille_nobg.png', 0, 3, 7,stick = E)
mode_lbl = Label(auto_win,text='Automatique',fg="white",bg='#24b700',font=('Arial',24,'bold'))
mode_lbl.grid(row=0,column=2)
ajout_image_auto('./CPU_robot.png', 1, 1, 2.1,rowspan=5,stick=S,padx=0)

avancer = ajout_icone_auto('fleche_videR.png', 2, 0, S, lambda:avancer_auto(avancer,lbl_distance, f"Distance à parcourir:\n {entry_log.get()} mm",entry_log.get()),height=200, width=110,ratiox=2.5,ratioy=2.5,rowspan=3)
avancer_lbl = Label(auto_win,text=' Avancer',bg='white',font=('Arial',20))
avancer_lbl.grid(column=0,row=5,sticky=N)

sequence_bar = ajout_icone_auto('./Sequence.png',1,0,stick = '',funct = lambda:sequence(), height=70, width=140)
sequence_lbl = Label(auto_win,text='Sequence ',bg='white',font=('Arial',16))
sequence_lbl.grid(column=0,row=1,sticky=S)

etape = ajout_icone_auto('./etape_par_etape.png',1,2,stick = '', funct = lambda:etapes(prog_bar), height=70, width=140)
etape_lbl = Label(auto_win,text=' Par étape',bg='white',font=('Arial',16))
etape_lbl.grid(column=2,row=1,sticky=S)

prog_bar = ajout_image_auto('./progbar_0.png',1,1,2,stick = '',pady=0,padx=0)

lbl_distance = Label(auto_win, text="Le robot est immobile",font=('Arial',14), fg ="black", bg="white")
lbl_distance.grid(column=2, row=4, sticky='')

stop = ajout_icone_auto('./stop.png',6,1,stick='',height=110,width=120,funct=lambda:arret(avancer,lbl_distance),ratiox=1.5,ratioy=1.5)
stop_lbl = Label(auto_win,text='ARRÊT',bg='white',font=('Arial',18))
stop_lbl.grid(column=1,row=6,sticky=S)

entry_log = Entry(auto_win,width=15,highlightthickness=3)
entry_log.grid(column=0, row=6,sticky=N,pady=0)
entry_log.config(highlightbackground = "black", highlightcolor= "black")
entry_lbl = Label(auto_win, text='Entrer distance (mm)',bg='white',font=('Arial,14'))
entry_lbl.grid(column=0,row=5,sticky=S)

btn_manual = Button(auto_win,command=lambda:show_manual(manual_win),text='Changer pour manuel',bg='white',fg='black')
btn_manual.grid(column=0,row=0,sticky=W,padx=20)

# Textbox input terminal
text_box = Text(auto_win, height = 45, width = 40, padx = 0, pady = 0,wrap=WORD)
text_box.insert(INSERT, "")
text_box.grid(column=3, row= 1,rowspan=7,sticky=W)

show_manual(manual_win)

window.mainloop()
