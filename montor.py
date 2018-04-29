import sys
import time
import os
import subprocess as sp
from email.mime.text import MIMEText
import smtplib

def send_email(s):
    m='cycle meet error!  result last change time is   '+s
    msg=MIMEText(m,'plain','utf-8')
    
    from_addr='qitthu@163.com'
    password='123456abc'
    to_addr='qit16@mails.tsinghua.edu.cn'
    msg['from']=from_addr
    msg['to']=to_addr

    smtp_server='smtp.163.com'

    server=smtplib.SMTP(smtp_server,25)
    server.set_debuglevel(1)
    server.login(from_addr,password)
    server.sendmail(from_addr,[to_addr,'857467373@qq.com'],msg.as_string())
    server.quit()

    

def check():

    with open('last_change','r') as f:
        last=f.read()
    s=sp.Popen('stat result',shell=True,stdout=sp.PIPE)
    s=s.stdout.read()
    s=s.decode('utf-8')
    start=s.find('Modify: ')
    start=start+len('Modify: ')
    end=s.find('\nChange')
    now=s[start:end]
    if now!= last:
        print('~~~~~~~~~~')
        print(now)
        print('~~~~~~~~~~~')
        print(last)
        print('~~~~~~~~~~~')
        send_email(last)
    print(now)
    print(last)
    with open('last_change','w') as f:
        f.write(now)
    print(s)

with open('last_change','w') as f:
    f.write('2008-04-26 01:48:18.000000000 +0800')


while True:
    check()
    time.sleep(5)