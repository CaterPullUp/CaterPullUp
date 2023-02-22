from tkinter import *
from PIL import Image, ImageTk

root_win = Tk()


root_win.geometry('+350+10')

etat_electroTop = False
etat_electroMid = False
etat_electroBas = False
etape_actuelle = 0


#root_win.grid(row=0,column=0,sticky='nsew')
root_win.minsize(width=1000,height=700)
root_win.maxsize(width=1000,height=1000)




def ajout_logo(path,row,column,ratio):
    img = Image.open(path)
    img = img.resize((int(img.size[0]/ratio),int(img.size[1]/ratio)))
    img = ImageTk.PhotoImage(img)
    img_label = Label(image=img, bg="white")
    img_label.image = img
    img_label.grid(column=column, row=row, rowspan=2, sticky=NW, padx=20, pady=10)

def ajout_image(path,row,column,ratio,stick,rowspan=2,padx=0,pady=0):
    img = Image.open(path)
    img = img.resize((int(img.size[0]/ratio),int(img.size[1]/ratio)))
    img = ImageTk.PhotoImage(img)
    img_label = Label(image=img, bg="white")
    img_label.image = img
    img_label.grid(column=column, row=row, rowspan=rowspan, sticky=stick, padx=padx, pady=pady)
    return img_label

def ajout_icone(url, row, column, stick, funct, height=70, width=140):
    icon = Image.open(url)
    icon = icon.resize((int(icon.size[0]/1.5),int(icon.size[1]/1.5)))
    l_button = int(icon.size[0]/3)+5
    h_button = int(icon.size[1]/3)+5
    icon = ImageTk.PhotoImage(icon)
    icon_label = Button(image=icon, command=funct,text="Bouton", width=width, height=height)
    icon_label.image = icon
    icon_label.grid(column=column, row=row, sticky=stick,pady=0)

def chg_electroTop(img):
    ratio = 5
    global etat_electroTop
    if etat_electroTop:
            image = Image.open('./topDesacRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            root_win.new_imageT = ImageTk.PhotoImage(image)
            img.configure(image=root_win.new_imageT)
            etat_electroTop = False
    else:
        image = Image.open('./topDesacVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        root_win.new_imageT = ImageTk.PhotoImage(image)
        img.configure(image=root_win.new_imageT)
        etat_electroTop = True

def chg_electroMid(img):
    ratio = 5
    global etat_electroMid
    if etat_electroMid:
            image = Image.open('./midDesacRouge.png')
            image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
            root_win.new_imageM = ImageTk.PhotoImage(image)
            img.configure(image=root_win.new_imageM)
            etat_electroMid = False
    else:
        image = Image.open('./midDesacVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        root_win.new_imageM = ImageTk.PhotoImage(image)
        img.configure(image=root_win.new_imageM)
        etat_electroMid = True

def chg_electroBas(img):
    ratio = 5
    global etat_electroBas
    if etat_electroBas:
        image = Image.open('./basDesacRouge.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        root_win.new_imageB = ImageTk.PhotoImage(image)
        img.configure(image=root_win.new_imageB)
        etat_electroBas = False
    else:
        image = Image.open('./basDesacVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        root_win.new_imageB = ImageTk.PhotoImage(image)
        img.configure(image=root_win.new_imageB)
        etat_electroBas = True

def move_patteAvant(img):
    ratio = 5
    global etat_electroTop
    if etat_electroTop:
        image = Image.open('./topActifVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        root_win.new_imageT = ImageTk.PhotoImage(image)
        img.configure(image=root_win.new_imageT)
        
    else:
        image = Image.open('./topActifRouge.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        root_win.new_imageT = ImageTk.PhotoImage(image)
        img.configure(image=root_win.new_imageT)

def move_Corps(img):
    ratio = 5
    global etat_electroMid
    if etat_electroMid:
        image = Image.open('./midActifVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        root_win.new_imageM = ImageTk.PhotoImage(image)
        img.configure(image=root_win.new_imageM)
        
    else:
        image = Image.open('./midActifRouge.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        root_win.new_imageM = ImageTk.PhotoImage(image)
        img.configure(image=root_win.new_imageM)


def move_patteArriere(img):
    ratio = 5
    global etat_electroBas
    if etat_electroBas:
        image = Image.open('./basActifVert.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        root_win.new_imageB = ImageTk.PhotoImage(image)
        img.configure(image=root_win.new_imageB)
        
    else:
        image = Image.open('./basActifRouge.png')
        image = image.resize((int(image.size[0]/ratio),int(image.size[1]/ratio)))
        root_win.new_imageB = ImageTk.PhotoImage(image)
        img.configure(image=root_win.new_imageB)
        
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
    root_win.new_progbar = ImageTk.PhotoImage(image)
    progbar_img.configure(image=root_win.new_progbar)
        


#Partie du haut
top = Frame(root_win, width=1000,height=100,bg='#24b700')#'#b3ff00')
top.grid(columnspan=4, rowspan=1, row=0)

#Partie Centrale
mid = Frame(root_win, width=1000, height=750, bg='white')
mid.grid(columnspan=4, rowspan=7, row=1)


ajout_logo('./chenille_nobg.png', 0, 0, 7)
topimg = ajout_image('./topDesacRouge.png',2,1,5,stick=S,rowspan=1,pady=20)
midimg = ajout_image('./midDesacRouge.png',3,1,5,stick='',rowspan=1,pady=0)
basimg = ajout_image('./basDesacRouge.png',5,1,5,stick=N,rowspan=1)
prog_bar = ajout_image('./progbar_0.png',1,1,2,stick = N,pady=35)
sequence_bar = ajout_icone('./Sequence.png',1,0,stick = SE,funct = lambda:sequence())
sequence_lbl = Label(root_win,text='Sequence ',bg='white',font=('Arial',20))
sequence_lbl.grid(column=0,row=2,sticky=NE)

etape = ajout_icone('./etape_par_etape.png',1,2,stick = SW, funct = lambda:etapes(prog_bar))
etape_lbl = Label(root_win,text=' Par étape',bg='white',font=('Arial',20))
etape_lbl.grid(column=2,row=2,sticky=NW)

stop = ajout_icone('./stop.png',6,1,stick = N, height=110,width=120, funct = lambda:sequence())
stop_lbl = Label(root_win,text='STOP',bg='white',font=('Arial',20))
stop_lbl.grid(column=1,row=7,sticky=N)



btn_mvmntAvant = Button(root_win,text="Activer patte avant", bg="#24b700",fg="white", command=lambda:move_patteAvant(topimg),height=1,width=22)#command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_mvmntAvant.grid(column=0,row=2,sticky=E)

btn_mvmtCorps = Button(root_win, text="Activer corps", bg="#24b700",fg="white", command=lambda:move_Corps(midimg),height=1,width=22)#command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_mvmtCorps.grid(column=0,row=3,sticky=E)

btn_mvmtArriere = Button(root_win, text="Activer patte arrière", bg="#24b700",fg="white", command=lambda:move_patteArriere(basimg),height=1,width=22)#command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_mvmtArriere.grid(column=0,row=5,sticky=E)

btn_electroAvant = Button(root_win, command=lambda:chg_electroTop(topimg),text="Activer électroaimant avant", bg="#24b700",fg="white",height=1,width=22)#command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_electroAvant.grid(column=2,row=2,sticky=W)

btn_electroCorps = Button(root_win, command=lambda:chg_electroMid(midimg), text="Activer électroaimant corps", bg="#24b700",fg="white",height=1,width=22)#command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_electroCorps.grid(column=2,row=3,sticky=W)

btn_electroArriere = Button(root_win, command=lambda:chg_electroBas(basimg), text="Activer électroaimant arrière", bg="#24b700",fg="white",height=1,width=22)#command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_electroArriere.grid(column=2,row=5,sticky=W)

#ajout_icone('bouton_electroR.png', 2, 0, E, lambda:chg_etat_electro(1,etat_electroAvant,etat_electroMid,etat_electroBas))




root_win.mainloop()
