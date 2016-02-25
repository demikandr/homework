#!/usr/bin/env python
# -*- coding: utf-8 -*-

import random
import string
import hashlib
import re
import requests
from bs4 import BeautifulSoup
from urllib.parse import *
from hashlib import md5

import unicodedata
import time

host = u"mipt.ru"
dir = u'downloads/'
headers = {
    'User-Agent': 'Mozilla/5.0 (iPad; CPU OS 5_0 like Mac OS X) AppleWebKit/534.46 (KHTML, like Gecko) Version/5.1 Mobile/9A334 Safari/7534.48.3',
    'Referer' : 'https://mipt.ru'
}


userIdsEnd=22618
userIdsBegin=17000
md5hash=md5()
strmd5hashs=[]
counterOfLittleHashs=16000

def makeHashs(userIdsEnd):
    global strmd5hashs, userIdsBegin
    num = userIdsBegin
    while num < userIdsEnd:
        md5hash.update(str(num).encode('utf-8'))
        strmd5hashs.append(md5hash.hexdigest())
        num += 1
        
makeHashs(userIdsEnd)
        
        
def rnd():
    global counterOfLittleHashs
    lst=format(counterOfLittleHashs,'03x')
    ret = "".join(lst)
    counterOfLittleHashs+=1
    return ret

def checkWith(strmd5hash, userId, srnd):
    #~ print(count)
    path = u'https://mipt.ru/upload/iblock/' + srnd + u'/fu' + strmd5hash +'.jpg'
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
    return status


while 1:
    global strmd5hashs
    tUserId=userIdsBegin
    srnd=rnd()
    for i in range(usrIdsBegin, userIdsEnd):
        print(i)
        checkWith(i, strmd5hashs[i], srnd)
    incHash()
