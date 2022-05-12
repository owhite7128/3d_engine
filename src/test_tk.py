import math
import tkinter as tk
import subprocess
import time

from matplotlib.pyplot import fill, prism

H=W=300
hH=hW=300/2

x= 0
y= 0
z= 0

root = tk.Tk()
cvs  = tk.Canvas(root,height=H,width=W)

cvs.pack()
root.update()

colors = ['#000000','#00FF00','#0000FF','#FF0000','#00FFFF','#FF00FF','#FFFF00','#F0F0F0']

def draw(pt_list, edg_list):
    color = 0
    for edg in edg_list:
        cvs.create_line(pt_list[edg[0]][0]+150,pt_list[edg[0]][1]+150,pt_list[edg[1]][0]+150,pt_list[edg[1]][1]+150, fill="#000000")
        color = color + 1



while True:
    pts = []
    clear = cvs.create_polygon(0,0,W,0,W,H,0,H,fill="white")
    try:
        ptaed = subprocess.check_output(['./build','in.mobj',f'{x}', f'{y}', f'{z}']).decode('utf-8').split(':')
    except subprocess.SubprocessError as err:
        print(err)
        break
    pts = ptaed[0].split('\n')
    edgs = ptaed[1].split('\n')

    form_pts = []
    form_edgs = []
    for pt in pts:
        if pt == "":
            break
        new_pt =  pt.split(',')
        new_pt[0] = float(new_pt[0][1:])
        new_pt[1] = float(new_pt[1][:-1])
        form_pts.append(new_pt)

    for edg in edgs:
        if edg == "":
            break
        new_edg = edg.split(',')
        new_edg[0] = int(new_edg[0][1:])
        new_edg[1] = int(new_edg[1][:-1])
        form_edgs.append(new_edg)


    print(form_pts)
    draw(form_pts, form_edgs)
    cvs.update()
    time.sleep(0.5)
    y = math.pi / 3
