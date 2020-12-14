#!-*-coding:utf8-*-
import os
import sys


def download(filelist="app.list"):
    f=open(filelist)
    os.chdir("./deb/")
    for line in f.readlines():
        cmd="apt-get download %s" %line.strip() 
        print cmd 
        os.system(cmd)


def install(filelist="app.list"):
    f=open(filelist)
    for line in f.readlines():
        cmd="apt-get install -y %s" %line.strip() 
        print cmd 
        os.system(cmd)



def run(filelist="app.list"):
    f=open(filelist)
    for line in f.readlines():
        cmd="%s" %line.strip() 
        print cmd
        os.system(cmd)


def init():
    dir_list=set(["cpk","deb","dpkg","screen"])
    filelist=set(os.listdir("./"))

    if len(dir_list&filelist)==0:
        print "create dir ..."
        for d in dir_list:
            cmd="mkdir %s" %d
            print cmd
            os.system(cmd)
            if not os.path.exists("app.list"):
                os.system("touch app.list")

    else:
        print "dir allready exists!"




def dpkg_batch():
    filelist=os.listdir("./deb/")
    for f in filelist:
        #dpkg –x $f files/
        dir="./dpkg/"+f
        cmd="mkdir %s" %dir
        print cmd
        os.system(cmd)
        cmd="dpkg -x %s%s %s" %("./deb/",f,dir)
        print cmd
        os.system(cmd)



def get_version():
	filelist=open("app.list")
        version=open("version","w")

        for f in filelist:
            cmd="apt-cache show %s|grep Version" %f.strip()
            #print cmd 
            Version=os.popen(cmd).readlines()[0]
            #print Version
            Version=Version.strip().strip("Version:").strip(" ")
            print Version
            version.write("%s\n" %Version)

        version.close()



def cpk_init(filelist="./app.list",v=""):
    f=open(filelist)
    
    if v!="":
        version=open(v)

    os.chdir("./cpk/")
    for line in f.readlines():
        line=line.strip()
        if v!="":
            v_str=version.readline().strip()
        else:
            v_str="1.0.0"

        cmd="cpk init -v %s cpk.gnome.%s %s" %(line,line,v_str)
        print cmd
        os.system(cmd)


def mv_usr(src_dir="./dpkg/",dest_dir="./cpk/"):
    src_filelist=os.listdir(src_dir)

    for f in src_filelist:
        fd_name=f.split("_")[0]
        #print fd_name

        sd=src_dir+f+"/usr/"
        dd=dest_dir+fd_name+"/files"
        cmd="cp -r %s %s" %(sd,dd)
        print cmd
        os.system(cmd)
        

def mv_screen(src_dir="./screen/",dest_dir="./cpk/"):
    src_filelist=open("app.list").readlines()

    for f in src_filelist:
        sd=src_dir+f.strip()+".png"
        dd=dest_dir+f.strip()+"/screenshots/"
        cmd="cp  %s %s" %(sd,dd)
        print cmd
        os.system(cmd)


if __name__=="__main__":
    if len(sys.argv)<2:
        print "expect more argument!"
        sys.exit()
    if sys.argv[1]=="i":    #安装deb 
        install()
    elif sys.argv[1]=="u":     #解压deb
        dpkg_batch()
    elif sys.argv[1]=="g":     #查询deb版本信息
        get_version()
    elif sys.argv[1]=="k": #cpk init 
        if len(sys.argv)==3:
            cpk_init(v=sys.argv[2])
        else:
            cpk_init()
    elif sys.argv[1]=="m":    #
        mv_usr()
    elif sys.argv[1]=="d":    #download deb 
        download()
    elif sys.argv[1]=="du":
        download()
        os.chdir("../")
        dpkg_batch()
    elif sys.argv[1]=="--init":
        init()
    elif sys.argv[1]=="s":
        mv_screen()
    elif sys.argv[1]=="r":
        run()
    else:
        print "invaild argument!"

