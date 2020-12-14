#!coding:utf8


import cProfile

def runRe():
    import re
    re.compile("foo|bar")

prof = cProfile.Profile() #return a object which support more function  
prof.enable() #start collect Profile data / prof.disable means stop collect data  
runRe()
prof.create_stats() #stop collect and create stats object to cache collect data 
prof.print_stats() #print collect data 


