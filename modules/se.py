import serial, os, sys

def serial_ports():
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result

class Arduino:
    def __init__(self, com, baudrate=9600):
        self.com  = com
        self.name = ''
        self.baudrate = baudrate

        self.s = serial.Serial()
        self.s.port = self.com
        self.s.baudrate = self.baudrate

    def pair(self, test=False):
        s = self.s
        try:
            s.open()
        except:
            print "get here"
            pass
            print "get here"
        try:
            s.flush()
            x = 0
            print "Pairing..."
            while x < 100000:
                bytesToRead = s.inWaiting()
                data = s.read(bytesToRead)
                print data
                if '57' in data:
                    print "Success"
                    if test == True:
                        return True
                    else:
                        return 'rpm'
                elif 't' in data:
                    print "Success"
                    if test == True:
                        return True
                    else:
                        return 'tracklight'

            print "Pairing Failed..."
            return False
        except:
            print "Pairing Failed..."
            return False

    def send(self, x):
        s = self.s
        try:
            s.open()
        except:
            pass
        #while s.out_waiting() > 0:
        #    pass
        s.write(x.encode('utf8'))
        s.flush()
        s.flushOutput()
        s.flushInput()
