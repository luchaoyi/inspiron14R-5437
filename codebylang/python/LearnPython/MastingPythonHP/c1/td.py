import datetime

_tstart=None
_tend=None

def start_time():
    global _tstart
    _tstart=datetime.datetime.now()

def get_delta():
    global _tstart
    _tend=datetime.datetime.now()
    return _tend - _tstart


#start_time()
#get_delta
