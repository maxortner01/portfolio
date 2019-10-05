import socket, struct, select

class UDP:
    def __init__(self, port=20771, ip='127.0.0.1'):
        self.ip = ip
        self.port = port

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        keys = {}
        f = open('bin/info.txt', 'r')
        for line in f:
            keys[line.split('\t')[0].strip()] = line.split('\t')[1].strip()
        f.close()

        self.keys = keys

    def open(self):
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.settimeout(.1)
        self.sock.bind((self.ip, self.port))

    def close(self):
        self.sock.close()

    def receive(self, val='all'):
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

if __name__ == '__main__':
    u = UDP()
    u.open()
    while True:
        print u.receive(val='rpm')
