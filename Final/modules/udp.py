import socket, struct, select, sys, carseour

class UDP:
    def __init__(self, g, port=20771, ip='127.0.0.1'):
        self.ip = ip
        self.port = port
        self.gameloc = g
        self.game = g.split('/')[len(g.split('/')) - 1]

        if self.game == 'AssettoCorsa.exe':
            d = self.gameloc.split('/')
            del d[len(d) - 1]
            for x in 'apps/python/simtronics'.split('/'):
                d.append(x)
            d = "/".join(d)
            sys.path.append(d)

        elif self.game == 'dirt4.exe' or self.game == 'drt.exe':
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

            keys = {}
            f = open('bin/info.txt', 'r')
            for line in f:
                keys[line.split('\t')[0].strip()] = line.split('\t')[1].strip()
            f.close()

            self.keys = keys

    def open(self):
        if self.game == 'pCARS2.exe' or self.game == 'pCARS2AVX.exe':
            try:
                self.g = carseour.live()
            except:
                pass

        try:
            self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.sock.settimeout(.1)
            self.sock.bind((self.ip, self.port))
        except:
            return

    def close(self):
        try:
            self.sock.close()
        except:
            return

    def dirtRec(self, val):
        try:
            data = self.sock.recv(512)
        except:
            return 'None'
        keys = self.keys

        if not data:
            return 'None'

        outsim_pack = struct.unpack('64f', data[0:256])

        dictionary = {}
        for id, value in enumerate(outsim_pack):
            dictionary[id] = value

        final = {}
        for i in dictionary:
            final[keys[str(i)]] = dictionary[i]

        if val == "all":
            return final

        try:
            return final[val]
        except:
            raise ValueError("Value '" + val + "' not supported.")

    def assetoRec(self, val):
        import sim_info

        if val == 'all':
            return sim_info.demo()
        else:
            try:
                return sim_info.demo()[val]
            except:
                raise ValueError("Value '" + val + "' not supported.")

    def projectRec(self, val):
        try:
            self.g = carseour.live()
        except:
            pass
        self.g = carseour.snapshot()
        g = self.g
        return {'rpm': g.mRpm, 'maxRpm': g.mMaxRPM, 'Throttle': g.mThrottle, 'Brake': g.mBrake,
                'Speed': g.mSpeed, 'Gear':g.mGear, 'water-temp': g.mWaterTempCelsius, 'oil-pressure': g.mOilPressureKPa,
                'Boost': g.mBoostAmount, 'isboost': g.mBoostActive, 'fuel': g.mFuelLevel, 'maxFuel': 1902,
                'abs': g.mCarFlags, 'tyres': g.mTyreFlags, 'fuelpress': g.mFuelPressureKPa
                }

    def receive(self, val='all'):
        if self.game == 'dirt4.exe' or self.game == 'drt.exe':
            return self.dirtRec(val)
        elif self.game == 'AssettoCorsa.exe':
            return self.assetoRec(val)
        elif self.game == 'pCARS2.exe' or self.game == 'pCARS2AVX.exe':
            return self.projectRec(val)



#if __name__ == '__main__':
#    u = UDP()
#    u.open()

#    while True:
#        print u.receive(val='rpm')
