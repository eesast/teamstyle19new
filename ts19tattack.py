import os
import subprocess
import sys
from time import sleep



path=r'./player'
ls=os.listdir(path)
total_num=len(ls)

vs_time=[]
id_score=[]
for i in range(0,total_num):
    vs_time.append([])
    id_score.append(0)
    for j in range(0,total_num):
        vs_time[i].append(0)


#print(ls)

l=len(ls)
for i in range(0,l):
    for j in range(i+1,l):
        echo=' echo foo> /dev/null 2>&1'
        ls1='./player/'+ls[i]+echo
        ls2='./player/'+ls[j]+echo
        cm1='mkdir '+ls[i]+'_'+ls[j]
        subprocess.call(cm1,shell=True)
        print(ls1,ls2)
        for count in range(0,4):
            ser=subprocess.Popen('python3 main.py echo foo> /dev/null 2>&1',shell=True)
            sleep(2)
            if count<2:
                pl1=subprocess.Popen(ls1,shell=True)
                sleep(1)
                while True:
                    try:
                        with open('connection','r') as f:
                            a=f.read()
                        if a=='1':
                            with open('connection','w') as f:
                                f.write('0')
                            break
                        else:
                            sleep(1)
                    except :
                        sleep(1)

                pl2=subprocess.Popen(ls2,shell=True)
                r='player0:'+ls[i]+'  player1:'+ls[j]+'  winner:'
            else :
                pl2=subprocess.Popen(ls2,shell=True)
                sleep(1)
                while True:
                    try:
                        with open('connection','r') as f:
                            a=f.read()
                        if a=='1':
                            with open('connection','w') as f:
                                f.write('0')
                            break
                        else:
                            sleep(1)
                    except :
                        sleep(1)
                pl1=subprocess.Popen(ls1,shell=True)
                r='player0:'+ls[j]+'  player1:'+ls[i]+'  winner:'
            while ser.poll()==None:
                sleep(2)
            pl1.kill()
            pl2.kill()
            kl1='kill '+str(pl1.pid)
            kl2='kill '+str(pl2.pid)
            subprocess.call(kl1,shell=True)
            subprocess.call(kl2,shell=True)
            with open('this_path','r') as f:
                save_path=f.read()
            cm="mv "+save_path+" ./"+ls[i]+'_'+ls[j]+'/'+save_path+'_'
            if count<2:
                 cm=cm+ls[i]+'_'+ls[j]+'.zip'
            else:
                 cm=cm+ls[j]+'_'+ls[i]+'.zip'
            subprocess.call(cm,shell=True)
            sleep(1)
            res=None
            with open('temp_result','r') as f:
                res=f.read()
                r=r+res+'\n'
                res=int(res)
            with open('result','a') as f:
                f.write(r)
                if count==3:
                    f.write('\n')
            if count<2:
                vs_time[i][j]+=1
            else:
                vs_time[j][i]+=1
            if count<2:
                if res==0:
                    id_score[i]+=2
                elif res==1:
                    id_score[j]+=2
                else:
                    id_score[j]+=1
                    id_score[i]+=1
            else :
                if res==0:
                    id_score[j]+=2
                elif res==1:
                    id_score[i]+=2
                else:
                    id_score[i]+=1
                    id_score[j]+=1
with open('final_socre','w') as f:
    for i in range(0,total_num):
        tes='team: '+ls[i]+'  score:'+str(id_score[i])+'\n'
        f.write(tes)

with open('total_com','w') as f:
    for i in range(0,total_num):
        f.write(ls[i])
        f.write(' ')
    f.write('\n')
    for i in range(0,total_num):
        for j in range(0,total_num):
            f.write(str(vs_time[i][j]))
            f.write('  ')
        f.write('\n')
