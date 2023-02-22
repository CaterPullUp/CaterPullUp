from tkinter import *
from PIL import Image, ImageTk

#Configure
window = Tk()
window.rowconfigure(0,weight=1)
window.columnconfigure(0,weight=1)
window.state("zoomed")

auto_win = Frame(window,bg='red')
manual_win = Frame(window)

for frame in (auto_win,manual_win):
    frame.grid(row=0,column=0,sticky='nswe')
    frame.grid_columnconfigure(0,weight=1)
    frame.grid_rowconfigure(0,weight=1)


Avancer = False
etat_electroTop = False
etat_electroMid = False
etat_electroBas = False
etape_actuelle = 0

def show_frame(frame):
    frame.tkraise()

show_frame(manual_win)

#WINDOW MANUAL 
def ajout_logo(path,row,column,ratio):
    img = Image.open(path)
    img = img.resize((int(img.size[0]/ratio),int(img.size[1]/ratio)))
    img = ImageTk.PhotoImage(img)
    img_label = Label(manual_win, image=img, bg="white")
    img_label.image = img
    img_label.grid(column=column, row=row, rowspan=2, sticky=NW, padx=20, pady=10)

def ajout_image(path,row,column,ratio,stick,rowspan=2,padx=0,pady=0):
    img = Image.open(path)
    img = img.resize((int(img.size[0]/ratio),int(img.size[1]/ratio)))
    img = ImageTk.PhotoImage(img)
    img_label = Label(manual_win,image=img, bg="white")
    img_label.image = img
    img_label.grid(column=column, row=row, rowspan=rowspan, sticky=stick, padx=padx, pady=pady)
    return img_label

def ajout_icone(url, row, column, stick, funct, height=70, width=140):
    icon = Image.open(url)
    icon = icon.resize((int(icon.size[0]/1.5),int(icon.size[1]/1.5)))
    l_button = int(icon.size[0]/3)+5
    h_button = int(icon.size[1]/3)+5
    icon = ImageTk.PhotoImage(icon)
    icon_label = Button(manual_win,image=icon, command=funct,text="Bouton", width=width, height=height)
    icon_label.image = icon
    icon_label.grid(column=column, row=row, sticky=stick,pady=0)

def chg_electroTop(img):
    ratio = 5
    global etat_electroTop
    if etat_electroTop:
            image = Image.open('./topDesacRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageT = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageT)
            etat_electroTop = False
    else:
        image = Image.open('./topDesacVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        manual_win.new_imageT = ImageTk.PhotoImage(image)
        img.configure(image=manual_win.new_imageT)
        etat_electroTop = True

def chg_electroMid(img):
    ratio = 5
    global etat_electroMid
    if etat_electroMid:
            image = Image.open('./midDesacRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            manual_win.new_imageM = ImageTk.PhotoImage(image)
            img.configure(image=manual_win.new_imageM)
            etat_electroMid = False
    else:
        image = Image.open('./midDesacVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        manual_win.new_imageM = ImageTk.PhotoImage(image)
        img.configure(image=manual_win.new_imageM)
        etat_electroMid = True

def chg_electroBas(img):
    ratio = 5
    global etat_electroBas
    if etat_electroBas:
        
        image = Image.open('./basDesacRouge.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        manual_win.new_imageB = ImageTk.PhotoImage(image)
        img.configure(image=manual_win.new_imageB)
        etat_electroBas = False
    else:
        image = Image.open('./basDesacVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        manual_win.new_imageB = ImageTk.PhotoImage(image)
        img.configure(image=manual_win.new_imageB)
        etat_electroBas = True

def move_patteAvant(img):
    ratio = 5
    global etat_electroTop
    if etat_electroTop:
        image = Image.open('./topActifVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        manual_win.new_imageT = ImageTk.PhotoImage(image)
        img.configure(image=manual_win.new_imageT)
        
    else:
        image = Image.open('./topActifRouge.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        manual_win.new_imageT = ImageTk.PhotoImage(image)
        img.configure(image=manual_win.new_imageT)

def move_Corps(img):
    ratio = 5
    global etat_electroMid
    if etat_electroMid:
        image = Image.open('./midActifVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        manual_win.new_imageM = ImageTk.PhotoImage(image)
        img.configure(image=manual_win.new_imageM)
        
    else:
        image = Image.open('./midActifRouge.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        manual_win.new_imageM = ImageTk.PhotoImage(image)
        img.configure(image=manual_win.new_imageM)


def move_patteArriere(img):
    ratio = 5
    global etat_electroBas
    if etat_electroBas:
        image = Image.open('./basActifVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        manual_win.new_imageB = ImageTk.PhotoImage(image)
        img.configure(image=manual_win.new_imageB)
        
    else:
        image = Image.open('./basActifRouge.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        manual_win.new_imageB = ImageTk.PhotoImage(image)
        img.configure(image=manual_win.new_imageB)
        
        '''
        image = Image.open('./topDesacVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        root_win.new_imageT = ImageTk.PhotoImage(image)
        img.configure(image=root_win.new_imageT)
        '''       
def sequence():
    i=1
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

#Partie du haut
top = Frame(manual_win,height=100,bg='#24b700')#'#b3ff00')
top.grid(columnspan=4, rowspan=1, row=0,sticky=NSEW)
top.grid_columnconfigure(0,weight=1)

#Partie Centrale
mid = Frame(manual_win, bg='white')
mid.grid(columnspan=4, rowspan=7, row=1,sticky='')
#mid.grid_columnconfigure(0,weight=1)


ajout_logo('./chenille_nobg.png', 0, 0, 7)
topimg = ajout_image('./topDesacRouge.png',2,1,5,stick=S,rowspan=1,pady=20)
midimg = ajout_image('./midDesacRouge.png',3,1,5,stick='',rowspan=1,pady=0)
basimg = ajout_image('./basDesacRouge.png',5,1,5,stick=N,rowspan=1)
prog_bar = ajout_image('./progbar_0.png',1,1,2,stick = N,pady=35)
sequence_bar = ajout_icone('./Sequence.png',1,0,stick = SE,funct = lambda:sequence())
sequence_lbl = Label(manual_win,text='Sequence ',bg='white',font=('Arial',20))
sequence_lbl.grid(column=0,row=2,sticky=NE)

etape = ajout_icone('./etape_par_etape.png',1,2,stick = SW, funct = lambda:etapes(prog_bar))
etape_lbl = Label(manual_win,text=' Par étape',bg='white',font=('Arial',20))
etape_lbl.grid(column=2,row=2,sticky=NW)

stop = ajout_icone('./stop.png',6,1,stick = N, height=110,width=120, funct = lambda:sequence())
stop_lbl = Label(manual_win,text='STOP',bg='white',font=('Arial',20))
stop_lbl.grid(column=1,row=7,sticky=N)

btn_automatic = Button(manual_win,command=lambda:show_frame(auto_win),text='Changer pour automatique',bg='white',fg='black')
btn_automatic.grid(column=0,row=0,sticky='')

btn_mvmntAvant = Button(manual_win,text="Entrer une distance", bg="#24b700",fg="white", command=lambda:move_patteAvant(topimg))#command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_mvmntAvant.grid(column=0,row=2,sticky=E)

btn_mvmtCorps = Button(manual_win, text="Entrer une distance", bg="#24b700",fg="white", command=lambda:move_Corps(midimg))#command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_mvmtCorps.grid(column=0,row=3,sticky=E)

btn_mvmtArriere = Button(manual_win, text="Entrer une distance", bg="#24b700",fg="white", command=lambda:move_patteArriere(basimg))#command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_mvmtArriere.grid(column=0,row=5,sticky=E)

btn_electroAvant = Button(manual_win, command=lambda:chg_electroTop(topimg),text="Entrer une distance", bg="#24b700",fg="white")#command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_electroAvant.grid(column=2,row=2,sticky=W)

btn_electroCorps = Button(manual_win, command=lambda:chg_electroMid(midimg), text="Entrer une distance", bg="#24b700",fg="white")#command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_electroCorps.grid(column=2,row=3,sticky=W)

btn_electroArriere = Button(manual_win, command=lambda:chg_electroBas(basimg), text="Entrer une distance", bg="#24b700",fg="white")#command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_electroArriere.grid(column=2,row=5,sticky=W)


# AUTOMATIC   
def fleche_haut(Avancer):
    if Avancer:
        ajout_icone_auto('fleche_videR.png', 2, 0, E, lambda:fleche_haut(Avancer))
        Avancer = False
    else:
        ajout_icone_auto('fleche_pleineV.png', 2, 0, E, lambda:fleche_haut(Avancer))
        Avancer = True

def arret():
    i=1

def afficher_distance(lbl,new_text):
    lbl.config(text = new_text)

def ajout_image_auto(path,row,column,ratio):
    img = Image.open(path)
    img = img.resize((int(img.size[0]/ratio),int(img.size[1]/ratio)))
    img = ImageTk.PhotoImage(img)
    img_name = Label(auto_win,image=img, bg="white")
    img_name.image = img
    img_name.grid(column=column, row=row, rowspan=2, sticky=NW, padx=20, pady=10)
    return img_name

def ajout_icone_auto(url, row, column, stick, funct):
    icon = Image.open(url)
    icon = icon.resize((int(icon.size[0]/3),int(icon.size[1]/3)))
    l_button = int(icon.size[0]/3)+5
    h_button = int(icon.size[1]/3)+5
    icon = ImageTk.PhotoImage(icon)
    icon_label = Button(auto_win,image=icon, command=funct, width=90, height=160)
    icon_label.image = icon
    icon_label.grid(column=column, row=row, sticky=stick)
    return icon_label

def chg_iconimg(icon_name,url):
    icon = Image.open(url)
    icon = icon.resize((int(icon.size[0]/3),int(icon.size[1]/3)))
    auto_win.icon = ImageTk.PhotoImage(icon)
    icon_name.configure(image=auto_win.icon) 



#Partie du haut
top = Frame(auto_win,height=0,bg='#24b700')#'#b3ff00')
#top.grid(columnspan=3, rowspan=1, row=0)
top.grid(row=0, column=0, rowspan=1,columnspan=3, sticky='news')
top.grid_columnconfigure(0,weight=1)
top.grid_rowconfigure(0,weight=1)
#top.pack(side="top", fill="x")
#top.grid_columnconfigure(0, weight=1)

#Partie Centrale
mid = Frame(auto_win, bg='white')#width=2300, height=650, )
mid.grid(row=1,column=0,columnspan=3,rowspan=5,sticky='nsew')
mid.grid_columnconfigure(0,weight=1)
mid.grid_rowconfigure(0,weight=1)


#Partie du bas
#bas = Frame(root_win, width=1000 ,height=25 ,bg='#b3ff00')#'#24b700')
#bas.grid(columnspan=3, rowspan=2, row=4)

#Controle du robot
ajout_image_auto('./chenille_nobg.png', 0, 0, 7)
#ajout_image('./chenille.png', 0, 1, 3.5)
ajout_image_auto('./CPU_robot.png', 2, 1, 2)
#ajout_icone('fleche_videR.png', 2, 0, E, lambda:fleche_haut(Avancer))
new_icon = ajout_icone_auto('bouton_electroR.png', 2, 0, E, lambda:chg_iconimg(new_icon,"bouton_moveV.png"))

#lbl_entrerValue = Label(root_win, text="Entrer une distance:", bg ="#24b700", fg="white")
#lbl_entrerValue.grid(column=1,row=1,sticky=W)

entry_log = Entry(auto_win,width=15,bg='black',fg='white')
entry_log.grid(column=1, row=1)


btn_distance = Button(auto_win,command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_distance.grid(column=1,row=1,sticky=E)

lbl_distance = Label(auto_win, text=" ", bg ="black", fg="white")
lbl_distance.grid(column=1, row=1, sticky=S)

btn_manual = Button(auto_win,command=lambda:show_frame(manual_win),text='Changer pour manuel',bg='white',fg='black')
btn_manual.grid(column=1,row=0,sticky=W)


# Textbox input terminal
text_box = Text(auto_win, height = 10, width = 50, padx = 15, pady = 15)
text_box.insert(1.0, "Cette boite de texte a pour utilité d'afficher le contenu du terminal directement dans le GUI. Cette boite sera donc une console pour monitor le comportement du code et du robot.")
text_box.tag_configure('center', justify='center')
text_box.tag_add('center',1.0,"end")
text_box.grid(column=2, row= 2)


window.mainloop()