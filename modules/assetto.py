import sys

class AC:
    def __init__(self, d):
        d = d.split("/")
        del d[len(d) - 1]
        for x in 'apps/python/simtronics'.split('/'):
            d.append(x)
        d = "/".join(d)
        #print d
        sys.path.append(d)

    def receive(self, val='all'):
        import sim_info
        return sim_info.demo()
