import os, xmltodict
import tkMessageBox as msgbox

def patchGame(gameloc, ip, port):
    exe = gameloc.split("/")[len(gameloc.split("/")) - 1]
    if exe.lower() == 'dirt4.exe':
        path = os.path.expanduser('~\\Documents\\My Games\\DiRT 4\\hardwaresettings')
        if os.path.exists(path) and os.path.isfile(path + "\\hardware_settings_config.xml"):
            with open(path + "\\hardware_settings_config.xml") as fd:
                doc = xmltodict.parse(fd.read())

            doc['hardware_settings_config']['motion_platform']['udp']['@enabled'] = 'true'
            doc['hardware_settings_config']['motion_platform']['udp']['@extradata'] = '3'
            doc['hardware_settings_config']['motion_platform']['udp']['@ip'] = ip
            doc['hardware_settings_config']['motion_platform']['udp']['@port'] = port
            doc['hardware_settings_config']['motion_platform']['udp']['@delay'] = '1'

            f = open(path + "\\hardware_settings_config.xml", 'w')
            f.write(xmltodict.unparse(doc, pretty=True))
            f.close()

            return True
        else:
            msgbox.showerror('Error', "Can't find the Dirt 4 Documents directory!")
            return False
    elif exe.lower() == 'drt.exe':
        path = os.path.expanduser('~\\Documents\\My Games\\DiRT Rally\\hardwaresettings')
        if os.path.exists(path) and os.path.isfile(path + "\\hardware_settings_config.xml"):
            with open(path + "\\hardware_settings_config.xml") as fd:
                doc = xmltodict.parse(fd.read())

            doc['hardware_settings_config']['motion_platform']['udp']['@enabled'] = 'true'
            doc['hardware_settings_config']['motion_platform']['udp']['@extradata'] = '3'
            doc['hardware_settings_config']['motion_platform']['udp']['@ip'] = ip
            doc['hardware_settings_config']['motion_platform']['udp']['@port'] = port
            doc['hardware_settings_config']['motion_platform']['udp']['@delay'] = '1'

            f = open(path + "\\hardware_settings_config.xml", 'w')
            f.write(xmltodict.unparse(doc, pretty=True))
            f.close()

            return True
        else:
            msgbox.showerror('Error', "Can't find the Dirt Rally Documents directory!")
            return False
    elif exe.lower() == 'assettocorsa.exe':
        g = gameloc.split('/')[:len(gameloc.split('/')) - 1]
        g = "/".join(g) + '/apps/python/'
        if os.path.exists(g + '/apps/python/simtronics') and os.path.isfile(g + '/apps/python/simtronics/sim_info.py'):
            return True

        try:
            os.mkdir(g + 'simtronics')
            os.mkdir(g + 'simtronics/stdlib')
            os.mkdir(g + 'simtronics/stdlib64')

            f = open(g + 'simtronics/__init__.py', 'w')
            f.close()

            t = open('bin/assetto/simtronics/sim_info.py', 'r')
            f = open(g + 'simtronics/sim_info.py', 'w')
            f.write(t.read())
            f.close()
            t.close()

            t = open('bin/assetto/simtronics/_ctypes.pyd', 'r')
            f = open(g + 'simtronics/stdlib/_ctypes.pyd', 'w')
            f.write(t.read())
            f.close()
            t.close()

            t = open('bin/assetto/simtronics/64/_ctypes.pyd', 'r')
            f = open(g + 'simtronics/stdlib64/_ctypes.pyd', 'w')
            f.write(t.read())
            f.close()
            t.close()

            return True
        except Exception as ex:
            msgbox.showerror('Error', "Error installing patch: " + str(ex))
            print str(ex)
            return False


if __name__ == '__main__':
    patchGame('D:/SteamLibrary/steamapps/common/assettocorsa/AssettoCorsa.exe', '127.0.0.1', '20771')
    raw_input('')
