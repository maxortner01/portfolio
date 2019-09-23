import psutil

def verification(i):
    for pid in psutil.pids():
        p = psutil.Process(pid)
        if p.name() == i:
            return True
