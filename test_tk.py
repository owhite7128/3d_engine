import math
import tkinter as tk
import subprocess
import time

#16:9

H = 360
W = 640
hH = H/2
hW = W/2

ang = math.pi 
t = math.pi / 2
x = 1
y = 0
z = 1
fps = 0

start_time = time.time()


root = tk.Tk()
cvs  = tk.Canvas(root,height=H,width=W)

cvs.pack()
root.update()


colors = ['#000000','#00FF00','#0000FF','#FF0000','#00FFFF','#FF00FF','#FFFF00','#F0F0F0']

def draw(pt_list, fce_list):
    color = 0
    for fce in fce_list:
        if fce[4] == 1:
            if fce[3] == -1:
                cvs.create_polygon (pt_list[fce[0]][0]+hW, pt_list[fce[0]][1]+hH, pt_list[fce[1]][0]+hW, pt_list[fce[1]][1]+hH, pt_list[fce[2]][0]+hW, pt_list[fce[2]][1]+hH, outline="black", fill='')
            else:
                cvs.create_polygon (pt_list[fce[0]][0]+hW, pt_list[fce[0]][1]+hH, pt_list[fce[1]][0]+hW, pt_list[fce[1]][1]+hH, pt_list[fce[2]][0]+hW, pt_list[fce[2]][1]+hH, pt_list[fce[3]][0]+hW, pt_list[fce[3]][1]+hH, outline="black", fill='')
            if color >= 7:
                color = 0
            else:
                color += 1



while True:
    pts = []
    cvs.delete("all")
    cvs.create_polygon(0,0,W,0,W,H,0,H,fill="white")
    try:
        ptaed = subprocess.check_output(['./build','monkey.obj',f'{x}', f'{y}', f'{z}', f'{ang}']).decode('utf-8').split(':')
    except subprocess.SubprocessError as err:
        print(err)
        break
    pts = ptaed[0].split('\n')
    fces = ptaed[1].split('\n')

    form_pts = []
    form_fces = []
    for pt in pts:
        if pt == "":
            break
        new_pt =  pt.split(',')
        new_pt[0] = float(new_pt[0][1:])
        new_pt[1] = float(new_pt[1][:-1])
        form_pts.append(new_pt)

    for fce in fces:
        if fce == "":
            break
        new_fce = fce.split(',')
        new_fce[0] = int(new_fce[0][1:])-1
        new_fce[1] = int(new_fce[1])-1
        new_fce[2] = int(new_fce[2])-1
        new_fce[3] = int(new_fce[3])-1
        new_fce[4] = int(new_fce[4][:-1])
        form_fces.append(new_fce)


    draw(form_pts, form_fces)

    
    fps = int((1)/(time.time()-start_time))
    start_time = time.time()
    cvs.create_text(20, 20, text=f"{fps}", fill="black", font="Helvetica")
    
    cvs.update()
    print(time.time()-start_time)
    ang += math.pi / 256
    x = math.cos(t)
    y = math.sin(t)
    z = math.cos(t)
    t += math.pi / 128

    
    
    
    
