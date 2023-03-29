from tkinter import *
from tkinter import messagebox
from PIL import Image, ImageTk

import socket
import struct
import time

# sensorMACAddress = '78:21:84:82:38:a2'

sensorMACAddress = '80:7d:3a:b9:33:e2'

port = 1
'''
s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)

try:
    s.connect((sensorMACAddress,port))

except TimeoutError:
    print("Connection error")

else:
    print("Connection successfull")
    data = (0xA1B2C3D4).to_bytes(4)
    print(data)
    while(1):
        try:
            s.sendall(data)  # Tells the sensor to send the data in bytes:
        except socket.error as e:
            print("Sending error : %s" % e)
        
        time.sleep(5)
'''
def macbinaire(mac_adress):
    '''
    INPUT: mac_adress, l'adresse mac sous forme de 'str'
    OUTPUT: macbin, un 'int' representant l'adresse mac en binaire sous 8 bytes
    Cette fonction convertit une adresse mac en base 16 en 'str' vers un entier 'int'
    representant l'adresse mac en binaire sous 8 bits.
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
    return macbin

def config_bloc_envoi(mac_adress):
    SOF=1
    EOF=1
    Delim=0
    return (SOF<<127)|(Delim<<126)|(mac_adress<<78)|(Delim<<77)|(Delim<<12)|(Delim<<3)|(Delim<<1)|EOF

def modif_parite(msg):
    ind = 0
    msg_bin = bin(msg)
    for i in msg_bin:
        if i==1:
            ind+=1
        else:
            pass
    if ind%2 != 0:
        msg = msg|(1<<2)
    else:
        pass
    return msg

#Configure
window = Tk()

window.geometry('+350+10')

window.minsize(width=1000,height=700)
window.maxsize(width=1000,height=1000)

auto_win = Frame(window)
manual_win = Frame(window)

for frame in (auto_win,manual_win):
    frame.grid(row=0,column=0,sticky='nswe')

Avancer = False
etat_electroTop = False
etat_electroMid = False
etat_electroBas = False
etat_patteAvant = False
etat_corps = False
etat_patteArriere = False
etape_actuelle = 0
electro_actives = 2

def show_frame(frame):
    frame.tkraise()

def show_manual(frame):
    reset_manual()
    frame.tkraise()

#WINDOW MANUAL 
def ajout_logo(path,row,column,ratio):
    img = Image.open(path)
    img = img.resize((int(img.size[0]/ratio),int(img.size[1]/ratio)))
    img = ImageTk.PhotoImage(img)
    img_label = Label(manual_win, image=img, bg="white")
    img_label.image = img
    img_label.grid(column=column, row=row, rowspan=1, sticky=E, padx=20, pady=0)

def ajout_image(path,row,column,ratio,stick,rowspan=2,padx=0,pady=0):
    img = Image.open(path)
    img = img.resize((int(img.size[0]/ratio),int(img.size[1]/ratio)))
    img = ImageTk.PhotoImage(img)
    img_label = Label(manual_win,image=img, bg="white")
    img_label.image = img
    img_label.grid(column=column, row=row, rowspan=rowspan, sticky=stick, padx=padx, pady=pady)
    return img_label

def ajout_icone(url, row, column, stick, funct, height=70, width=140,ratio=1.5):
    icon = Image.open(url)
    icon = icon.resize((int(icon.size[0]/ratio),int(icon.size[1]/ratio)))
    l_button = int(icon.size[0]/3)+5
    h_button = int(icon.size[1]/3)+5
    icon = ImageTk.PhotoImage(icon)
    icon_label = Button(manual_win,image=icon, command=funct,text="Bouton", width=width, height=height)
    icon_label.image = icon
    icon_label.grid(column=column, row=row, sticky=stick,pady=0)

def reset_manual():
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

def chg_electroMid(img):
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
    else:
        if etat_corps:
            image = Image.open('./midActifVert.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageM = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageM)
            num_fonction = 9
            etat_electroMid = True
            electro_actives+=1
        else:
            messagebox.showerror('Action impossible', "Descendre d'abord le corps", icon='error')
        
def chg_electroBas(img):
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

def move_patteAvant(img):
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
        
    else:
        if etat_electroTop:
            messagebox.showerror('Action impossible', "Désactiver l'électroaimant avant de faire un déplacement", icon='error')
        else:
            image = Image.open('./topActifRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageT = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageT)
            etat_patteAvant = True

def move_Corps(img):
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
        
    else:
        if etat_electroMid:
            messagebox.showerror('Action impossible', "Désactiver l'électroaimant avant de faire un déplacement", icon='error')
        else:
            image = Image.open('./midActifRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageM = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageM)
            etat_corps = True

def move_patteArriere(img):
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
        
    else:
        if etat_electroBas:
            messagebox.showerror('Action impossible', "Désactiver l'électroaimant avant de faire un déplacement", icon='error')
        else:
            image = Image.open('./basActifRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageB = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageB)
            etat_patteArriere = True
    
def sequence():
    i=1
    num_fonction = 15
def etapes(progbar_img):
    global etape_actuelle
    if etape_actuelle != 6:
        etape_actuelle += 1
    else:
        etape_actuelle = 0
    image = Image.open(f'./progbar_{etape_actuelle}.png')
    image = image.resize((int(image.size[0]/2),int(image.size[1]/2)))
    manual_win.new_progbar = ImageTk.PhotoImage(image)
    progbar_img.configure(image=manual_win.new_progbar)
    num_fonction = 16

#Partie du haut
top = Frame(manual_win, width=1000,height=100,bg='#24b700')
top.grid(columnspan=4, rowspan=1, row=0)

#Partie Centrale
mid = Frame(manual_win, width=1000, height=750, bg='white')
mid.grid(columnspan=4, rowspan=5, row=1)

ajout_logo('./chenille_nobg.png', 0, 3, 7)
topimg = ajout_image('./topDesacRouge.png',1,1,5,stick=S,rowspan=1,pady=0)
midimg = ajout_image('./midDesacRouge.png',2,1,5,stick='',rowspan=1,pady=0)
basimg = ajout_image('./basDesacRouge.png',3,1,5,stick=N,rowspan=1)

btn_automatic = Button(manual_win,command=lambda:show_frame(auto_win),text='Changer pour automatique',bg='white',fg='black')
btn_automatic.grid(column=0,row=0,sticky=W,padx=20)

btn_mvmntAvant = Button(manual_win,text="Activer patte avant", bg="#24b700",fg="white", command=lambda:move_patteAvant(topimg))
btn_mvmntAvant.grid(column=0,row=1,sticky=E)

btn_mvmtCorps = Button(manual_win, text="Activer corps", bg="#24b700",fg="white", command=lambda:move_Corps(midimg))
btn_mvmtCorps.grid(column=0,row=2,sticky=E)

btn_mvmtArriere = Button(manual_win, text="Activer patte arrière", bg="#24b700",fg="white", command=lambda:move_patteArriere(basimg))
btn_mvmtArriere.grid(column=0,row=3,sticky=E)

btn_electroAvant = Button(manual_win, command=lambda:chg_electroTop(topimg),text="Activer électroaimant avant", bg="#24b700",fg="white")
btn_electroAvant.grid(column=2,row=1,sticky=W)

btn_electroCorps = Button(manual_win, command=lambda:chg_electroMid(midimg), text="Activer électroaimant corps", bg="#24b700",fg="white")
btn_electroCorps.grid(column=2,row=2,sticky=W)

btn_electroArriere = Button(manual_win, command=lambda:chg_electroBas(basimg), text="Activer électroaimant arrière", bg="#24b700",fg="white")
btn_electroArriere.grid(column=2,row=3,sticky=W)

# Textbox input terminal
text_box_manual = Text(manual_win, height = 45, width = 40, padx = 0, pady = 0)
text_box_manual.insert(1.0, "Cette boite de texte a pour utilité d'afficher le contenu du terminal directement dans le GUI. Cette boite sera donc une console pour monitor le comportement du code et du robot.")
text_box_manual.tag_configure('center', justify='center')
text_box_manual.tag_add('center',1.0,"end")
text_box_manual.grid(column=3, row= 1,rowspan=5)

# AUTOMATIC   
def arret():
    i=1
    num_fonction = 17

def aller_distance(lbl,new_text,distance):
    if distance.replace('.','',1).isdigit():
        lbl.config(text = new_text)
    else:
        lbl.config(text = 'Erreur')
    entry_log.delete(0, END)
    num_fonction = 18

def ajout_image_auto(path,row,column,ratio,stick=NW,rowspan=1,padx=20,pady=0):
    img = Image.open(path)
    img = img.resize((int(img.size[0]/ratio),int(img.size[1]/ratio)))
    img = ImageTk.PhotoImage(img)
    img_name = Label(auto_win,image=img, bg="white")
    img_name.image = img
    img_name.grid(column=column, row=row, rowspan=rowspan, sticky=stick, padx=padx, pady=pady)
    return img_name

def ajout_icone_auto(url, row, column, stick, funct,height=310, width=130,ratiox=2.2,ratioy=1.5,rowspan=1):
    icon = Image.open(url)
    icon = icon.resize((int(icon.size[0]/ratiox),int(icon.size[1]/ratioy)))
    l_button = int(icon.size[0]/3)+5
    h_button = int(icon.size[1]/3)+5
    icon = ImageTk.PhotoImage(icon)
    icon_label = Button(auto_win,image=icon, command=funct, width=width, height=height)
    icon_label.image = icon
    icon_label.grid(column=column, row=row, sticky=stick,rowspan=rowspan)
    return icon_label

def avancer_auto(icon_name):
    global Avancer
    if Avancer:
        icon = Image.open("fleche_videR.png")
        icon = icon.resize((int(icon.size[0]/2.5),int(icon.size[1]/2.5)))
        auto_win.fleche = ImageTk.PhotoImage(icon)
        icon_name.configure(image=auto_win.fleche)
        num_fonction = 14

        Avancer = False
        msg = modif_parite(config_bloc_envoi(macbinaire(sensorMACAddress))|(num_fonction<<4))
        print(msg)
        #s.send(bytes("Arreter","utf-8"))
    else:
        icon = Image.open("fleche_pleineV.png")
        icon = icon.resize((int(icon.size[0]/2.5),int(icon.size[1]/2.5)))
        auto_win.fleche = ImageTk.PhotoImage(icon)
        icon_name.configure(image=auto_win.fleche)
        num_fonction = 13
        Avancer = True
        #s.send(bytes("Avancer","utf-8"))

#Partie du haut
top = Frame(auto_win, width=1000,height=100,bg='#24b700')
top.grid(columnspan=4, rowspan=1, row=0)

#Partie Centrale
mid = Frame(auto_win, width=1000, height=750, bg='white')
mid.grid(columnspan=4, rowspan=7, row=1)

#Controle du robot
ajout_image_auto('./chenille_nobg.png', 0, 3, 7,stick = E)
ajout_image_auto('./CPU_robot.png', 2, 1, 2.1,rowspan=4,stick=N,padx=0)

avancer = ajout_icone_auto('fleche_videR.png', 3, 0, '', lambda:avancer_auto(avancer),height=350, width=110,ratiox=2.5,ratioy=2.5,rowspan=2)
avancer_lbl = Label(auto_win,text=' Avancer',bg='white',font=('Arial',20))
avancer_lbl.grid(column=0,row=5,sticky=N)

sequence_bar = ajout_icone_auto('./Sequence.png',1,0,stick = S,funct = lambda:sequence(), height=70, width=140)
sequence_lbl = Label(auto_win,text='Sequence ',bg='white',font=('Arial',20))
sequence_lbl.grid(column=0,row=2,sticky=N)

etape = ajout_icone_auto('./etape_par_etape.png',1,2,stick = S, funct = lambda:etapes(prog_bar), height=70, width=140)
etape_lbl = Label(auto_win,text=' Par étape',bg='white',font=('Arial',20))
etape_lbl.grid(column=2,row=2,sticky=N)

prog_bar = ajout_image_auto('./progbar_0.png',1,1,2,stick = '',pady=0,padx=0)

btn_distance = Button(auto_win,command=lambda:aller_distance(lbl_distance, f"Distance à parcourir:\n {entry_log.get()} mm",entry_log.get()),text="Entrer une distance (mm)", bg="#24b700",fg="white")
btn_distance.grid(column=2,row=3,sticky=S)
lbl_distance = Label(auto_win, text=" ",font=('Arial',14), fg ="black", bg="white")
lbl_distance.grid(column=2, row=4, sticky='')

stop = ajout_icone_auto('./stop.png',5,1,stick=S,height=110,width=120,funct=lambda:arret(),ratiox=1.5,ratioy=1.5)
stop_lbl = Label(auto_win,text='STOP',bg='white',font=('Arial',20))
stop_lbl.grid(column=1,row=6,sticky=N)

entry_log = Entry(auto_win,width=15,highlightthickness=3)
entry_log.grid(column=2, row=4,sticky=N,pady=0)
entry_log.config(highlightbackground = "black", highlightcolor= "black")

btn_manual = Button(auto_win,command=lambda:show_manual(manual_win),text='Changer pour manuel',bg='white',fg='black')
btn_manual.grid(column=0,row=0,sticky=W,padx=20)

# Textbox input terminal
text_box = Text(auto_win, height = 45, width = 40, padx = 0, pady = 0)
text_box.insert(1.0, "Cette boite de texte a pour utilité d'afficher le contenu du terminal directement dans le GUI. Cette boite sera donc une console pour monitor le comportement du code et du robot.")
text_box.tag_configure('center', justify='center')
text_box.tag_add('center',1.0,"end")
text_box.grid(column=3, row= 1,rowspan=7)

show_manual(manual_win)

window.mainloop()

#!!!
#s.close()