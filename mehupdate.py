#!/usr/bin/env python
# mehupdate - update Makefiles 
# remeh - remeh@remeh.fr
# --

version = "0.1"

import os,sys

def listdirectory(path): 
    fichier=[] 
    for root, dirs, files in os.walk(path): 
        for i in files: 
            fichier.append(os.path.join(root, i)) 
    return fichier

def maj_makefile(name):
    files = listdirectory("./src/")
    cppfiles = ""
    for f in files:
        if f.endswith(".cpp"):
            cppfiles = "%s %s" % (cppfiles, (f.replace(".cpp",".o")))

    makefile = open(name,"r")
    newmakefile = open(name + ".tmp","w")

    for ligne in makefile:
        ligne = ligne.rstrip('\n\r')
        if ligne.startswith('OBJ '):
            newmakefile.write("OBJ = %s\n" % cppfiles) 
        else: 
            newmakefile.write("%s\n" % ligne)

    os.system("mv " + name + ".tmp " + name)
    print(name + " successfully updated.")


# main

# Which Makefile must be updated

name = ""
if len(sys.argv) == 1:
    print("Not enough parameter. Usage : python mehupdate.py Makefile1 Makefile2")
    exit(-1)

for i in sys.argv:
    if i.find('mehupdate.py') == -1:
        maj_makefile(i)


