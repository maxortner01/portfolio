import pygame
from pygame.locals import *
from pygame.draw import circle, line
from pygame.gfxdraw import line as gline
from matplotlib.colors import hex2color
from math import sin, cos, tan, radians
from modules.udp import UDP
import json

def celtofar(c):
    return c * (9/5) + 32

def finalColor(h):
    y = []
    h = hex2color(h)
    for x in h:
        y.append(int(x * 255))

    return (y[0], y[1], y[2])

class base:
    def __init__(self, x, y, game, e='dark'):
        self.game = game
        self.runningGame = self.game.split('/')[len(self.game.split('/')) - 1]
        self.fps = 0
        e = e.lower()

        #self.distance = 0
        self.dem = {'x': x, 'y': y}

        self.indicators = {'abs': pygame.image.load('bin/dashes/images/indicators/abs.png'),
                            'check-engine': pygame.image.load('bin/dashes/images/indicators/checkengine.png'),
                            'fuel': pygame.image.load('bin/dashes/images/indicators/fuel.png'),
                            'handbrake': pygame.image.load('bin/dashes/images/indicators/handbrake.png'),
                            'headlights': pygame.image.load('bin/dashes/images/indicators/headlights.png'),
                            'headlights-unlit': pygame.image.load('bin/dashes/images/indicators/headlights-unlit.png'),
                            'oil': pygame.image.load('bin/dashes/images/indicators/oil.png'),
                            'abs-unlit': pygame.image.load('bin/dashes/images/indicators/abs-unlit.png'),
                            'handbrake-unlit': pygame.image.load('bin/dashes/images/indicators/handbrake-unlit.png'),
                            'checkengine-unlit': pygame.image.load('bin/dashes/images/indicators/checkengine-unlit.png'),
                            'fuel-unlit': pygame.image.load('bin/dashes/images/indicators/fuel-unlit.png'),
                            'tc': pygame.image.load('bin/dashes/images/indicators/tc.png'),
                            'tc-unlit': pygame.image.load('bin/dashes/images/indicators/tc-unlit.png'),
                            'tc-off': pygame.image.load('bin/dashes/images/indicators/tc-off.png'),
                            'tc-off-unlit': pygame.image.load('bin/dashes/images/indicators/tc-off-unlit.png'),
                            'tp': pygame.image.load('bin/dashes/images/indicators/tp.png'),
                            'tp-unlit': pygame.image.load('bin/dashes/images/indicators/tp-unlit.png')
                            }

        self.indisize = (int(self.dem['x'] / 14), int(self.dem['x'] / 14))
        for indi in self.indicators:
            self.indicators[indi] = pygame.transform.scale(self.indicators[indi], self.indisize)


        self.center = (x / 2, y / 2)
        pygame.font.init()

        self.fonts = {'rpms-bold': pygame.font.SysFont('monospace', int(self.dem['x'] / 65), bold=True),
                        'speed': pygame.font.Font('bin/fonts/Laconic/Laconic_Bold.otf', int(self.dem['x'] / 15)),
                        'speed-small': pygame.font.Font('bin/fonts/Laconic/Laconic_Light.otf', int(self.dem['x'] / 66)),
                        'speed-extrasmall': pygame.font.Font('bin/fonts/Laconic/Laconic_Light.otf', int(self.dem['x'] / 76)),
                        'speed-extrasmall2': pygame.font.Font('bin/fonts/Laconic/Laconic_Light.otf', int(self.dem['x'] / 120)),
                        'std-small': pygame.font.Font('bin/fonts/RPM.otf', int(self.dem['x'] / 75)),
                        'std-med': pygame.font.Font('bin/fonts/RPM.otf', int(self.dem['x'] / 60)),
                        'rpms': pygame.font.Font('bin/fonts/Laconic/Laconic_Bold.otf', int(self.dem['x'] / 65)),
                        'std-med-bold': pygame.font.Font('bin/fonts/Laconic/Laconic_Bold.otf', int(self.dem['x'] / 60)),
                        'odometer': pygame.font.Font('bin/fonts/odometer.ttf', int(self.dem['x'] / 65))
                        }
        self.needle = ''

        self.screen = pygame.display.set_mode((x, y))
        pygame.display.gl_set_attribute(GL_MULTISAMPLEBUFFERS, 8)
        pygame.display.gl_set_attribute(GL_MULTISAMPLESAMPLES, 8)
        self.running = True
        self.isboost = False

    def execute(self):
        colors = self.colors
        pygame.display.set_caption('Dashboard')
        pygame.init()

        u = UDP(self.game)
        u.open()

        self.bg = pygame.image.load('bin/dashes/images/bg1.png')
        self.bg = pygame.transform.scale(self.bg, (self.dem['x'], self.dem['y']))
        frames = 0

        while self.running:
            frames = frames + 1

            try:
                data = u.receive()
                if self.runningGame == 'AssettoCorsa.exe' or self.runningGame == 'pCARS2.exe' or self.runningGame == 'pCARS2AVX.exe':
                    rpms = int(data['rpm'])
                else:
                    rpms = int(data['rpm']) * 10

                maxrpm = int(data['maxRpm'] * 10)
                throttle = int(data['Throttle'] * 180)
                brake = int(data['Brake'] * 180)

                if self.runningGame == 'AssettoCorsa.exe':
                    speed = data['Speed'] * 0.621371 * 8
                else:
                    speed = data['Speed'] * 2.23694 * 8

                gear = int(data['Gear'])


            except Exception as ex:
                #print str(ex) + "lll"
                print ("You must activate UDP telemetry data sending in the menu of the game")
                rpms = 0
                maxrpm = 0
                throttle = 0
                brake = 0
                speed = 0
                gear = 0
                water = 0
                oil = 0
                self.screen.fill(colors['background'])
                x = self.fonts['std-med-bold'].size("Initializing...")[0] / 2
                ya = self.fonts['std-med-bold'].size("Initializing...")[1] / 2
                text = self.fonts['std-med-bold'].render("Initializing...", True, colors['white'])
                self.screen.blit(text, (self.center[0] - x, self.center[1] - ya))
                pygame.display.flip()
                continue

            try:
                ab = data['abs']
            except:
                ab = 0

            #print pygame.time.get_ticks() * 0.001
            mps = (speed / 8) * 0.000277778
            self.last = pygame.time.get_ticks() * 0.001
            print "last     " + str(self.last)
            self.distance = self.distance + (mps * ((pygame.time.get_ticks() * 0.001) -  self.last))
            #self.distance = self.distance * 100
            #print str(self.distance)

            #print "distance " + str(self.distance * 100)
            #self.distance = float(format(self.distance * 10000, '.9f'))
            #self.distance = self.distance * 10000
            #self.distance = self.distance / 10000
            #b = float(format(b, '.5f'))
            #self.distance = self.distance + b
            #raw_input('')

            #for key in cflags:
            #    print key + ": " + cflags[key]

            try:
                water = int(celtofar(data['water-temp']))
            except:
                water = 0

            #print water

            try:
                oil = data['oil-pressure'] * 0.14503773773
            except:
                oil = None

            try:
                boost = data['Boost']
                self.isboost = data['isboost']
            except:
                boost = None

            try:
                fuel = (data['fuel'], data['maxFuel'])
            except Exception as ex:
                fuel = (0, 0)

            try:
                fuelpress = data['fuelpress']
            except:
                fuelpress = 0

            if fuel[1] == 1902:
                self.fuel = fuel[0]
                tyres = list(data['tyres'])
                inflate = []
                on = []
                air = []

                b = 0
                for x in tyres:
                    y = ""
                    for g in range(3 - len(bin(x)[2:])):
                        y = y + "0"
                    air.insert(b, list(y + str(bin(x)[2:]))[0])
                    on.insert(b, list(y + str(bin(x)[2:]))[2])
                    inflate.insert(b, list(y + str(bin(x)[2:]))[1])
                    b += 1

                y = ""
                for x in range(8 - len(bin(ab)[2:])):
                    y = y + '0'
                carflags = y + bin(ab)[2:]
                #print carflags
                #print carflags
                try:
                    self.cflags = {'handbrake': carflags[2],
                                'abs': carflags[3],
                                'speed-limiter': carflags[4],
                                'check-engine': carflags[5],
                                'engine-on': carflags[6],
                                'headlights': carflags[7],
                                'tc': carflags[0],
                                'anti-roll': carflags[1],
                                'tires-inflated': inflate,
                                'tires-onground': air,
                                'tires-attached': on
                            }
                except:
                    self.cflags = {'handbrake': 0,
                                'abs': 0,
                                'speed-limiter': 0,
                                'check-engine': 0,
                                'engine-on': 0,
                                'headlights': 0,
                                'tc': 0,
                                'anti-roll': 0,
                                'tires-inflated': inflate,
                                'tires-onground': air,
                                'tires-attached': on
                            }
            elif self.runningGame == 'AssettoCorsa.exe':
                self.fuel = fuel[0]
                self.wheelpressure = list(data['wheel-pressure'])
                #print data['auto']

                self.cflags = {'handbrake': 0,
                            'abs': data['abs'],
                            'speed-limiter': 0,
                            'check-engine': 0,
                            'engine-on': 1,
                            'headlights': 0,
                            'tc': data['tc'],
                            'anti-roll': 0
                        }
                #print "abs: " + str(self.cflags['abs'])
                #print 'tc:  ' + str(self.cflags['tc'])
            else:
                self.cflags = {'handbrake': 0,
                            'abs': 0,
                            'speed-limiter': 0,
                            'check-engine': 0,
                            'engine-on': 0,
                            'headlights': 0,
                            'tc': 0,
                            'anti-roll': 0
                        }

                self.cflags = {'handbrake': 0,
                            'abs': 0,
                            'speed-limiter': 0,
                            'check-engine': 0,
                            'engine-on': 0,
                            'headlights': 0,
                            'tc': 0,
                            'anti-roll': 0,
                            'tires-inflated': 0,
                            'tires-onground': 0,
                            'tires-attached': 0
                        }


            if self.runningGame == 'pCARS2.exe' or self.runningGame == 'pCARS2AVX.exe' or self.runningGame == 'AssettoCorsa.exe':
                maxrpm = maxrpm / 10

            self.screen.fill(colors['background'])

            if self.runningGame == 'AssettoCorsa.exe':
                if gear == 0:
                    gear = "R"
                elif gear == 1:
                    gear = "N"
                else:
                    gear = gear - 1
            else:
                if gear == 0:
                    gear = "N"
                elif gear == -1:
                    gear = "R"

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.close()
                    u.close()
                    self.running = False

            self.draw_gauges(maxrpm, water, oil, fuelpress)
            self.drawThrottle(throttle)
            self.drawBrake(brake)
            self.drawSpeed(gear, int(speed), self.distance)
            if self.runningGame == 'pCARS2.exe' or self.runningGame == 'pCARS2AVX.exe':
                #print speed
                self.draw_needle(rpms, speed, water=water, oil=oil, fuel=fuel, fuelpress=fuelpress)
            elif self.runningGame == 'AssettoCorsa.exe':
                self.draw_needle(rpms, speed, fuel=fuel)
            else:
                self.draw_needle(rpms, speed)

            #self.screen.blit(self.bg, (0, 0))
            self.fps = int(frames / (pygame.time.get_ticks() * .001))
            print "\t\tFPS: " + str(self.fps)

            pygame.display.flip()


        pygame.display.quit()
