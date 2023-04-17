from tkinter import *
from PIL import Image, ImageTk

root_win = Tk()

root_win.geometry('+350+10')

root_win.minsize(width=1000,height=700)
root_win.maxsize(width=1000,height=1000)

Avancer = False

def fleche_haut(Avancer):
    if Avancer:
        ajout_icone('fleche_videR.png', 2, 1, W, lambda:fleche_haut(Avancer))
        Avancer = False
    else:
        ajout_icone('fleche_pleineV.png', 2, 1, W, lambda:fleche_haut(Avancer))
        Avancer = True

def arret():
    i=1

def afficher_distance(lbl,new_text):
    lbl.config(text = new_text)



def ajout_image(path,row,column,ratio,sticky=NW):
    img = Image.open(path)
    img = img.resize((int(img.size[0]/ratio),int(img.size[1]/ratio)))
    img = ImageTk.PhotoImage(img)
    img_name = Label(image=img, bg="white")
    img_name.image = img
    img_name.grid(column=column, row=row, rowspan=2, sticky=sticky, padx=0, pady=0)
    return img_name

def ajout_icone(url, row, column, stick, funct):
    icon = Image.open(url)
    icon = icon.resize((int(icon.size[0]/3),int(icon.size[1]/3)))
    l_button = int(icon.size[0]/3)+5
    h_button = int(icon.size[1]/3)+5
    root_win.fleche = ImageTk.PhotoImage(icon)
    icon_label = Button(root_win,image=root_win.fleche, command=funct, width=90, height=160)
    icon_label.image = icon
    icon_label.grid(column=column, row=row, sticky=stick)
    return icon_label

def chg_iconimg(icon_name):
    global Avancer
    if Avancer:
        icon = Image.open("fleche_videR.png")
        icon = icon.resize((int(icon.size[0]/3),int(icon.size[1]/3)))
        root_win.fleche = ImageTk.PhotoImage(icon)
        icon_name.configure(image=root_win.fleche)
        Avancer = False
    else:
        icon = Image.open("fleche_pleineV.png")
        icon = icon.resize((int(icon.size[0]/3),int(icon.size[1]/3)))
        root_win.fleche = ImageTk.PhotoImage(icon)
        icon_name.configure(image=root_win.fleche)
        Avancer = True

#Partie du haut
top = Frame(root_win, width=1000,height=100,bg='#24b700')#'#b3ff00')
top.grid(columnspan=3, rowspan=1, row=0)

#Partie Centrale
mid = Frame(root_win, width=1000, height=650, bg='white')
mid.grid(columnspan=3, rowspan=3, row=1)

#Partie du bas
#bas = Frame(root_win, width=1000 ,height=25 ,bg='#b3ff00')#'#24b700')
#bas.grid(columnspan=3, rowspan=2, row=4)

#Controle du robot
ajout_image('./chenille_nobg.png', 0, 0, 7)
#ajout_image('./chenille.png', 0, 1, 3.5)
ajout_image('./CPU_robot.png', 1, 1, 2,sticky='')
#ajout_icone('fleche_videR.png', 2, 1, W, lambda:fleche_haut(Avancer))
new_icon = ajout_icone('fleche_videR.png', 1, 2, W, lambda:chg_iconimg(new_icon))


#lbl_entrerValue = Label(root_win, text="Entrer une distance:", bg ="#24b700", fg="white")
#lbl_entrerValue.grid(column=1,row=1,sticky=W)

entry_log = Entry(root_win,width=20,bg='black',fg='white',justify=CENTER)
entry_log.grid(column=0, row=1,sticky=E)

btn_distance = Button(root_win,command=lambda:afficher_distance(lbl_distance, f"Distance à parcourir:{entry_log.get()}"),text="Entrer une distance", bg="#24b700",fg="white")
btn_distance.grid(column=0,row=1,sticky='',padx=0)

lbl_distance = Label(root_win, text=" ", bg ="white", fg="black",font=("Arial",12),width=25)
lbl_distance.grid(column=0, row=1, sticky=SW)

# Textbox input terminal
text_box = Text(root_win, height = 10, width = 40, padx = 0, pady = 0)
text_box.insert(1.0, "Cette boite de texte a pour utilité d'afficher le contenu du terminal directement dans le GUI. Cette boite sera donc une console pour monitor le comportement du code et du robot.")
text_box.tag_configure('center', justify='center')
text_box.tag_add('center',1.0,"end")
text_box.grid(column=2, row= 1,sticky=E)

root_win.mainloop()


