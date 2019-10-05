import pygame
from pygame.locals import *
from pygame.draw import circle, line, aaline
from pygame.gfxdraw import line as gline
from matplotlib.colors import hex2color
from math import sin, cos, tan, radians
from modules.udp import UDP
from dir.pydraw import draw as dw
from dir import dir
import json

def celtofar(c):
    return c * (9/5) + 32

def finalColor(h):
    y = []
    h = hex2color(h)
    for x in h:
        y.append(int(x * 255))

    return (y[0], y[1], y[2])

class dashboard(dir.base):
    def __init__(self, x, y, game, e='dark'):
        print "motorsport"
        dir.base.__init__(self, x, y, game, e='dark')
        d = open('bin/data.txt', 'r')
        try:
            self.distance = json.loads(d.read())['odometer']['GT_Motorsport'][self.runningGame]
        except:
            self.distance = 0
        d.close()
        e = e.lower()

        self.circles = {'rpm': {'inner_circle': int(x / 10), 'outer_circle': int(x / 7), 'outer_circle2': int(x / 6.95), 'throttle-outer': int(x / 12), 'throttle-inner': int(x / 13)},
                        'speed': {'main': int(x / 8), 'circle2': int(x / 9), 'main2': int(x / 7.9)}
                        }
        if e == 'dark':
            self.colors = {'background': finalColor('#26212B'), 'white': finalColor('#FFFFFF'), 'needle': finalColor('#E0A600'),
                            'red-line': finalColor('#A92C1E'), 'throttle': finalColor('#D63826'), 'brake': finalColor('#3C52D6'),
                            'dark-white': finalColor('#717275'), 'led': finalColor('#221D26'), 'led-lines': finalColor('#3D3545')
                            }
        else:
            self.colors = {'background': finalColor('#FFFFFF'), 'white': finalColor('#26212B'), 'needle': finalColor('#E0A600'),
                            'red-line': finalColor('#A92C1E'), 'throttle': finalColor('#D63826'), 'brake': finalColor('#3C52D6'),
                            'dark-white': finalColor('#717275'), 'led': finalColor('#221D26'), 'led-lines': finalColor('#3D3545')
                            }

        self.draw = dw(self.screen)

    def close(self):
        d = open('bin/data.txt', 'r')
        b = json.loads(d.read())
        d.close()

        d = open('bin/data.txt', 'w')
        #b['odometer']['BRZ'][self.runn] = self.distance
        b['odometer']['GT_Motorsport'][self.runningGame] = self.distance
        d.write(json.dumps(b, indent=4))

        d.close()

    def draw_gauges(self, maxrpm, water, oil, drawwidth=1):
        colors = self.colors
        circles = self.circles

        self.speedCenter = (self.center[0] - self.circles['rpm']['outer_circle2'] - self.dem['x'] / 150, self.center[1] + self.dem['x'] / 50)
        speedCenter = self.speedCenter

        x = int(self.dem['x'] / 4.7) * cos(radians(95 * 2.7 + 82)) + self.center[0]
        y = int(self.dem['x'] / 4.7) * sin(radians(95 * 2.7 + 82)) + self.center[1]
        xa = int(self.dem['x'] / 4.7) * cos(radians(107.5 * 2.7 + 82)) + self.center[0]
        ya = int(self.dem['x'] / 4.7) * sin(radians(107.5 * 2.7 + 82)) + self.center[1]
        xb = int(self.dem['x'] / 4.7) * cos(radians(120 * 2.7 + 82)) + self.center[0]
        yb = int(self.dem['x'] / 4.7) * sin(radians(120 * 2.7 + 82)) + self.center[1]

        self.waterCenter = (xb, yb)
        waterCenter = self.waterCenter

        self.oilCenter = (xa, ya)
        oilCenter = self.oilCenter

        self.boostCenter = (x, y)
        boostCenter = self.boostCenter

        self.secondaryindi = int((int(self.dem['x'] / 5.3) + circles['rpm']['outer_circle']) / 2)

        #circle(self.screen, colors['dark-white'], (self.center[0], self.center[1] + int(int(self.dem['x'] / 8.4))), int(self.dem['x'] / 3.3), 2)
        circle(self.screen, colors['background'], self.center, int(self.dem['x'] / 5.3))

        self.draw.multicircle(colors['dark-white'], self.center, int(self.dem['x'] / 5.3), 2)
        #circle(self.screen, colors['dark-white'], self.center, int(self.dem['x'] / 5.3), 2)
        #circle(self.screen, colors['dark-white'], self.center, self.secondaryindi, 2)

        circle(self.screen, colors['background'], speedCenter, circles['speed']['main2'])

        #fuel
        if self.runningGame == 'AssettoCorsa.exe':
            x = int(self.dem['x'] / 4.7) * cos(radians(0)) + self.center[0]
            y = int(self.dem['x'] / 4.7) * sin(radians(0)) + self.center[1]
            self.boostCenter = (x, y)
            boostCenter = self.boostCenter

            circle(self.screen, colors['background'], (int(x), int(y)), int(self.dem['x'] / 19.5))   #BOOST
            self.draw.multicircle(colors['white'], (int(x), int(y)), int(self.dem['x'] / 19.5), 3)   #BOOST
            for val in range(3):
                if val == 0:
                    v = '0'
                elif val == 1:
                    v = '1/2'
                else:
                    v = '1'
                text = self.fonts['speed-extrasmall'].render(str(v), True, colors['white'])
                x = int(self.dem['x'] / 20) * cos(radians(val * 90 + 180)) + boostCenter[0]
                y = int(self.dem['x'] / 20) * sin(radians(val * 90 + 180)) + boostCenter[1]

                xbb = int(self.dem['x'] / 26) * cos(radians(val * 90 + 180)) + boostCenter[0]
                ybb = int(self.dem['x'] / 26) * sin(radians(val * 90 + 180)) + boostCenter[1]

                xt = int(self.dem['x'] / 37) * cos(radians(val * 90 + 180)) + boostCenter[0]
                yt = int(self.dem['x'] / 37) * sin(radians(val * 90 + 180)) + boostCenter[1]

                #lineDraw(x, y, obj, [xb, yb])
                xc = self.fonts['speed-extrasmall'].size(str(v))[0]
                yc = self.fonts['speed-extrasmall'].size(str(v))[1]
                self.screen.blit(text, (xt - xc / 2, yt - yc / 2 + 2))
                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                #line(self.screen, colors['white'], (x, y), (xbb, ybb), 2)
                self.draw.multiline(colors['white'], (x, y), (xbb, ybb), 2)

            for val in range(7):
                x = int(self.dem['x'] / 20) * cos(radians(val * 30 + 180)) + boostCenter[0]
                y = int(self.dem['x'] / 20) * sin(radians(val * 30 + 180)) + boostCenter[1]

                xbb = int(self.dem['x'] / 24) * cos(radians(val * 30 + 180)) + boostCenter[0]
                ybb = int(self.dem['x'] / 24) * sin(radians(val * 30 + 180)) + boostCenter[1]

                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                line(self.screen, colors['white'], (x, y), (xbb, ybb), 1)

            text = self.fonts['speed-extrasmall'].render(str("Fuel"), True, colors['white'])
            x = self.fonts['speed-extrasmall'].size("Fuel")[0]
            self.screen.blit(text, (boostCenter[0] - x / 2, boostCenter[1] + int(self.dem['x'] / 37) / 1.2))

        if self.runningGame == 'pCARS2.exe' or self.runningGame == 'pCARS2AVX.exe':

            circle(self.screen, colors['background'], (int(xa), int(ya)), int(self.dem['x'] / 19.4)) #OIL
            circle(self.screen, colors['background'], (int(xb), int(yb)), int(self.dem['x'] / 19.5)) #WATER
            circle(self.screen, colors['background'], (int(x), int(y)), int(self.dem['x'] / 19.5))   #BOOST

            #circle(self.screen, colors['white'], (int(x), int(y)), int(self.dem['x'] / 19.5), 3)   #BOOST
            self.draw.multicircle(colors['white'], (int(x), int(y)), int(self.dem['x'] / 19.5), 2)
            #BOOST
            for val in range(3):
                if val == 0:
                    v = '0'
                elif val == 1:
                    v = '1/2'
                else:
                    v = '1'
                text = self.fonts['speed-extrasmall'].render(str(v), True, colors['white'])
                x = int(self.dem['x'] / 20) * cos(radians(val * 90 + 180)) + boostCenter[0]
                y = int(self.dem['x'] / 20) * sin(radians(val * 90 + 180)) + boostCenter[1]

                xbb = int(self.dem['x'] / 26) * cos(radians(val * 90 + 180)) + boostCenter[0]
                ybb = int(self.dem['x'] / 26) * sin(radians(val * 90 + 180)) + boostCenter[1]

                xt = int(self.dem['x'] / 37) * cos(radians(val * 90 + 180)) + boostCenter[0]
                yt = int(self.dem['x'] / 37) * sin(radians(val * 90 + 180)) + boostCenter[1]

                #lineDraw(x, y, obj, [xb, yb])
                xc = self.fonts['speed-extrasmall'].size(str(v))[0]
                yc = self.fonts['speed-extrasmall'].size(str(v))[1]
                self.screen.blit(text, (xt - xc / 2, yt - yc / 2 + 2))
                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                #line(self.screen, colors['white'], (x, y), (xbb, ybb), 2)
                self.draw.multiline(colors['white'], (x, y), (xbb, ybb), 2)

            for val in range(7):
                x = int(self.dem['x'] / 20) * cos(radians(val * 30 + 180)) + boostCenter[0]
                y = int(self.dem['x'] / 20) * sin(radians(val * 30 + 180)) + boostCenter[1]

                xbb = int(self.dem['x'] / 24) * cos(radians(val * 30 + 180)) + boostCenter[0]
                ybb = int(self.dem['x'] / 24) * sin(radians(val * 30 + 180)) + boostCenter[1]

                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                #line(self.screen, colors['white'], (x, y), (xbb, ybb), 1)
                aaline(self.screen, colors['white'], (x, y), (xbb, ybb))

            text = self.fonts['speed-extrasmall'].render(str("Fuel"), True, colors['white'])
            x = self.fonts['speed-extrasmall'].size("Fuel")[0]
            self.screen.blit(text, (boostCenter[0] - x / 2, boostCenter[1] + int(self.dem['x'] / 37) / 1.2))

        #SECONDARY GUAGES
        #if self.runningGame == 'pCARS2.exe' or self.runningGame == 'pCARS2AVX.exe':
            #circle(self.screen, colors['white'], (int(xa), int(ya)), int(self.dem['x'] / 19.4), 3) #OIL
            #circle(self.screen, colors['white'], (int(xb), int(yb)), int(self.dem['x'] / 19.5), 3) #WATER
            self.draw.multicircle(colors['white'], (int(xb), int(yb)), int(self.dem['x'] / 19.5), 2)
            self.draw.multicircle(colors['white'], (int(xa), int(ya)), int(self.dem['x'] / 19.4), 2)

            #OIL
            for val in range(5):
                v = val * 20
                text = self.fonts['speed-extrasmall'].render(str(v), True, colors['white'])
                x = int(self.dem['x'] / 20) * cos(radians(val * 60 + 150)) + oilCenter[0]
                y = int(self.dem['x'] / 20) * sin(radians(val * 60 + 150)) + oilCenter[1]

                xb = int(self.dem['x'] / 26) * cos(radians(val * 60 + 150)) + oilCenter[0]
                yb = int(self.dem['x'] / 26) * sin(radians(val * 60 + 150)) + oilCenter[1]

                xt = int(self.dem['x'] / 37) * cos(radians(val * 60 + 150)) + oilCenter[0]
                yt = int(self.dem['x'] / 37) * sin(radians(val * 60 + 150)) + oilCenter[1]

                #lineDraw(x, y, obj, [xb, yb])
                xc = self.fonts['speed-extrasmall'].size(str(v))[0]
                yc = self.fonts['speed-extrasmall'].size(str(v))[1]
                self.screen.blit(text, (xt - xc / 2, yt - yc / 2 + 2))
                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                #line(self.screen, colors['white'], (x, y), (xb, yb), 2)
                self.draw.multiline(colors['white'], (x, y), (xb, yb), 2)

            for val in range(8):
                x = int(self.dem['x'] / 20) * cos(radians(val * 30 + 150)) + oilCenter[0]
                y = int(self.dem['x'] / 20) * sin(radians(val * 30 + 150)) + oilCenter[1]

                xb = int(self.dem['x'] / 24) * cos(radians(val * 30 + 150)) + oilCenter[0]
                yb = int(self.dem['x'] / 24) * sin(radians(val * 30 + 150)) + oilCenter[1]

                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                #line(self.screen, colors['white'], (x, y), (xb, yb), 1)
                aaline(self.screen, colors['white'], (x, y), (xb, yb))

            for val in range(16):
                x = int(self.dem['x'] / 20) * cos(radians(val * 15 + 150)) + oilCenter[0]
                y = int(self.dem['x'] / 20) * sin(radians(val * 15 + 150)) + oilCenter[1]

                xb = int(self.dem['x'] / 24) * cos(radians(val * 15 + 150)) + oilCenter[0]
                yb = int(self.dem['x'] / 24) * sin(radians(val * 15 + 150)) + oilCenter[1]

                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                #line(self.screen, colors['white'], (x, y), (xb, yb), 1)
                aaline(self.screen, colors['white'], (x, y), (xb, yb))

            #WATER
            for val in range(5):
                v = 100 + (val * 40)
                text = self.fonts['speed-extrasmall'].render(str(v), True, colors['white'])
                x = int(self.dem['x'] / 20) * cos(radians(val * 60 + 150)) + waterCenter[0]
                y = int(self.dem['x'] / 20) * sin(radians(val * 60 + 150)) + waterCenter[1]

                xb = int(self.dem['x'] / 26) * cos(radians(val * 60 + 150)) + waterCenter[0]
                yb = int(self.dem['x'] / 26) * sin(radians(val * 60 + 150)) + waterCenter[1]

                xt = int(self.dem['x'] / 37) * cos(radians(val * 60 + 150)) + waterCenter[0]
                yt = int(self.dem['x'] / 37) * sin(radians(val * 60 + 150)) + waterCenter[1]

                #lineDraw(x, y, obj, [xb, yb])
                xc = self.fonts['speed-extrasmall'].size(str(v))[0]
                yc = self.fonts['speed-extrasmall'].size(str(v))[1]
                self.screen.blit(text, (xt - xc / 2, yt - yc / 2 + 2))
                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                #line(self.screen, colors['white'], (x, y), (xb, yb), 2)
                self.draw.multiline(colors['white'], (x, y), (xb, yb), 2)

            text = self.fonts['speed-extrasmall2'].render(str("Water Temp F"), True, colors['white'])
            x = self.fonts['speed-extrasmall2'].size("Water Temp F")[0]
            self.screen.blit(text, (waterCenter[0] - x / 2, waterCenter[1] + int(self.dem['x'] / 37) / 1.2))

            text = self.fonts['speed-extrasmall2'].render(str("Oil Pressure PSI"), True, colors['white'])
            x = self.fonts['speed-extrasmall2'].size("Oil Pressure PSI")[0]
            self.screen.blit(text, (oilCenter[0] - x / 2, oilCenter[1] + int(self.dem['x'] / 37) / 1.2))


            for val in range(41):
                x = int(self.dem['x'] / 20) * cos(radians(val * 6 + 150)) + waterCenter[0]
                y = int(self.dem['x'] / 20) * sin(radians(val * 6 + 150)) + waterCenter[1]

                xb = int(self.dem['x'] / 22.5) * cos(radians(val * 6 + 150)) + waterCenter[0]
                yb = int(self.dem['x'] / 22.5) * sin(radians(val * 6 + 150)) + waterCenter[1]

                #lineDraw(x, y, obj, [xb, yb])
                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                #line(self.screen, colors['white'], (x, y), (xb, yb), 1)
                aaline(self.screen, colors['white'], (x, y), (xb, yb))

        #BASE SPEEDOMETER
        #circle(self.screen, colors['white'], speedCenter, circles['speed']['main2'], 2)
        self.draw.multicircle(colors['white'], speedCenter, circles['speed']['main2'], 2)

        #SPEEDOMETER MAIN
        for val in range(12):
            text = self.fonts['speed-small'].render(str(val * 20), True, colors['white'])
            x = circles['speed']['circle2'] * cos(radians(val * 18 + 68)) + speedCenter[0]
            y = circles['speed']['circle2'] * sin(radians(val * 18 + 68)) + speedCenter[1]

            xb = int(self.dem['x'] / 8) * cos(radians(val * 18 + 68)) + speedCenter[0]
            yb = int(self.dem['x'] / 8) * sin(radians(val * 18 + 68)) + speedCenter[1]

            xt = int(self.dem['x'] / 9.9) * cos(radians(val * 18 + 68)) + speedCenter[0]
            yt = int(self.dem['x'] / 9.9) * sin(radians(val * 18 + 68)) + speedCenter[1]

            #lineDraw(x, y, obj, [xb, yb])
            self.screen.blit(text, (xt - int(self.dem['x'] / 66) / 2 + 4, yt - int(self.dem['x'] / 66) / 2))
            #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
            #line(self.screen, colors['white'], (x, y), (xb, yb), 3)
            self.draw.multiline(colors['white'], (x, y), (xb, yb), 4)

        for val in range(24):
            x = int(self.dem['x'] / 8.75) * cos(radians(val * 9 + 68)) + speedCenter[0]
            y = int(self.dem['x'] / 8.75) * sin(radians(val * 9 + 68)) + speedCenter[1]

            xb = int(self.dem['x'] / 8) * cos(radians(val * 9 + 68)) + speedCenter[0]
            yb = int(self.dem['x'] / 8) * sin(radians(val * 9 + 68)) + speedCenter[1]

            #lineDraw(x, y, obj, [xb, yb])
            #text = self.fonts['speed-small'].render(str(val), True, colors['white'])
            #self.screen.blit(text, (xt, yt))
            #line(self.screen, colors['white'], (x, y), (xb, yb), 1)
            aaline(self.screen, colors['white'], (x, y), (xb, yb))

        for val in range(120):
            x = int(self.dem['x'] / 8.35) * cos(radians(val * 1.8 + 68)) + speedCenter[0]
            y = int(self.dem['x'] / 8.35) * sin(radians(val * 1.8 + 68)) + speedCenter[1]

            xb = int(self.dem['x'] / 8) * cos(radians(val * 1.8 + 68)) + speedCenter[0]
            yb = int(self.dem['x'] / 8) * sin(radians(val * 1.8 + 68)) + speedCenter[1]

            #lineDraw(x, y, obj, [xb, yb])
            #text = self.fonts['speed-small'].render(str(val), True, colors['white'])
            #self.screen.blit(text, (xt, yt))
            #line(self.screen, colors['white'], (x, y), (xb, yb), 1)
            aaline(self.screen, colors['white'], (x, y), (xb, yb))


        #BASE RPM
        circle(self.screen, colors['background'], self.center, self.circles['rpm']['outer_circle2'])
        #circle(self.screen, colors['white'], self.center, self.circles['rpm']['inner_circle'], 2)
        #circle(self.screen, colors['white'], self.center, self.circles['rpm']['outer_circle2'], 2)

        self.draw.multicircle(colors['white'], self.center, self.circles['rpm']['inner_circle'], 2)
        self.draw.multicircle(colors['white'], self.center, self.circles['rpm']['outer_circle2'], 2)

        #REDLINE
        #print maxrpm
        y = ""
        for x in range(5 - len(str(maxrpm))):
            y = y + '0'

        #print y + str(maxrpm)[:1]
        maximum = (y + str(maxrpm))[:2]
        if int(maximum) <= 10:
            maximum = 9

        if maxrpm > 0:
            self.drawRedLine(maxrpm, int(maximum))

        #INDICATORS
        self.maximum = int(maximum) + 1
        maximum = self.maximum
        twomax = int(maximum) * 2
        #RPM MAIN
        for val in range(11 + (maximum - 10)):
            x = circles['rpm']['outer_circle'] * cos(radians(val * (270.0 / maximum) + 90)) + self.dem['x'] / 2
            y = circles['rpm']['outer_circle'] * sin(radians(val * (270.0 / maximum) + 90)) + self.dem['y'] / 2

            xb = int(self.dem['x'] / 8) * cos(radians(val * (270.0 / maximum) + 90)) + self.dem['x'] / 2
            yb = int(self.dem['x'] / 8) * sin(radians(val * (270.0 / maximum) + 90)) + self.dem['y'] / 2

            xt = int(self.dem['x'] / 6.5) * cos(radians(val * (270.0 / maximum) + 90)) + self.dem['x'] / 2
            yt = int(self.dem['x'] / 6.5) * sin(radians(val * (270.0 / maximum) + 90)) + self.dem['y'] / 2

            #lineDraw(x, y, obj, [xb, yb])
            text = self.fonts['speed-small'].render(str(val), True, colors['white'])
            #self.screen.blit(text, (xt, yt))
            self.screen.blit(text, (xt - int(self.dem['x'] / 66) / 2 + 4, yt - int(self.dem['x'] / 66) / 2))
            #line(self.screen, colors['white'], (x, y), (xb, yb), 3)
            self.draw.multiline(colors['white'], (x, y), (xb, yb), 3)

        #SECONDARY
        #print maximum
        #print float(270.0 / twomax)
        for val in range(21 + (twomax - 20)):
            x = circles['rpm']['outer_circle'] * cos(radians(val * (270.0 / twomax) + 90)) + self.dem['x'] / 2
            y = circles['rpm']['outer_circle'] * sin(radians(val * (270.0 / twomax) + 90)) + self.dem['y'] / 2

            xb = int(self.dem['x'] / 7.5) * cos(radians(val * (270.0 / twomax) + 90)) + self.dem['x'] / 2
            yb = int(self.dem['x'] / 7.5) * sin(radians(val * (270.0 / twomax) + 90)) + self.dem['y'] / 2

            #lineDraw(x, y, obj, [xb, yb])
            aaline(self.screen, colors['white'], (x, y), (xb, yb))

        for val in range(101 + ((maximum * 10) - 100)):
            x = circles['rpm']['outer_circle'] * cos(radians(val * (270.0 / (maximum * 10)) + 90)) + self.dem['x'] / 2
            y = circles['rpm']['outer_circle'] * sin(radians(val * (270.0 / (maximum * 10)) + 90)) + self.dem['y'] / 2

            xb = int(self.dem['x'] / 7.25) * cos(radians(val * (270.0 / (maximum * 10)) + 90)) + self.dem['x'] / 2
            yb = int(self.dem['x'] / 7.25) * sin(radians(val * (270.0 / (maximum * 10)) + 90)) + self.dem['y'] / 2

            #lineDraw(x, y, obj, [xb, yb])
            aaline(self.screen, colors['white'], (x, y), (xb, yb))


        #self.draw_needle(0)

    def draw_needle(self, rpm, speed, water=-1, oil=-1, fuel=(-1, -1), fuelpress=-1):
        l = rpm * (270.0 / (self.maximum * 1000))
        #speed = (speed / 8) * 32
        b = speed * .1125
        oil = oil * 2

        water = water - 100
        if water <= -100:
            c = 0
        else:
            c = abs(float(water / 1))

        colors = self.colors
        circles = self.circles
        speedCenter = self.speedCenter
        waterCenter = self.waterCenter
        oilCenter   = self.oilCenter
        fuelCenter = self.boostCenter

        x = circles['rpm']['outer_circle'] * cos(radians(l + 90)) + self.dem['x'] / 2
        y = circles['rpm']['outer_circle'] * sin(radians(l + 90)) + self.dem['y'] / 2

        xb = circles['rpm']['inner_circle'] * cos(radians(l + 90)) + self.dem['x'] / 2
        yb = circles['rpm']['inner_circle'] * sin(radians(l + 90)) + self.dem['y'] / 2
        #line(self.screen, colors['needle'], (x, y), (xb, yb), 7)
        self.draw.line(colors['needle'], (x, y), (xb, yb))


        #x = circles['rpm']['outer_circle'] * cos(radians(l + 68)) + speedCenter[0]
        #y = circles['rpm']['outer_circle'] * sin(radians(l + 68)) + speedCenter[1]

        x = speedCenter[0]
        y = speedCenter[1]

        xb = circles['speed']['main'] * cos(radians(b + 68)) + speedCenter[0]
        yb = circles['speed']['main'] * sin(radians(b + 68)) + speedCenter[1]
        #line(self.screen, colors['needle'], (x, y), (xb, yb), 3)
        #self.draw.line(colors['needle'], (x, y), (xb, yb), 5)
        self.draw.multiline(colors['needle'], (x, y), (xb, yb), 4)

        if self.runningGame == 'pCARS2.exe' or self.runningGame == 'pCARS2AVX.exe':
            #WATER
            if c >= 0.0:
                x = waterCenter[0]
                y = waterCenter[1]

                xb = int(self.dem['x'] / 20) * cos(radians(c * 1.5 + 150)) + waterCenter[0]
                yb = int(self.dem['x'] / 20) * sin(radians(c * 1.5 + 150)) + waterCenter[1]
                #line(self.screen, colors['needle'], (x, y), (xb, yb), 2)
                self.draw.multiline(colors['needle'], (x, y), (xb, yb), 2)
            elif c < 0:
                x = waterCenter[0]
                y = waterCenter[1]

                xb = int(self.dem['x'] / 20) * cos(radians(50 * 1.5 + 150)) + waterCenter[0]
                yb = int(self.dem['x'] / 20) * sin(radians(50 * 1.5 + 150)) + waterCenter[1]
                #line(self.screen, colors['needle'], (x, y), (xb, yb), 2)
                self.draw.multiline(colors['needle'], (x, y), (xb, yb), 2)

            #Oil
            x = oilCenter[0]
            y = oilCenter[1]

            xb = int(self.dem['x'] / 20) * cos(radians(oil * 1.5 + 150)) + oilCenter[0]
            yb = int(self.dem['x'] / 20) * sin(radians(oil * 1.5 + 150)) + oilCenter[1]
            self.draw.multiline(colors['needle'], (x, y), (xb, yb), 2)
            #line(self.screen, colors['needle'], (x, y), (xb, yb), 2)

        if self.runningGame == 'pCARS2.exe' or self.runningGame == 'pCARS2AVX.exe' or self.runningGame == 'AssettoCorsa.exe':
            #Fuel
            x = fuelCenter[0]
            y = fuelCenter[1]

            if fuel[1] == 1902:
                f = fuel[0]
                f = f * 100
            else:
                try:
                    f = fuel[0] / fuel[1]
                except:
                    f = 0

                if fuel[0] == -1:
                    f = 0
                else:
                    f = f * 100

                #print fuel

            xb = int(self.dem['x'] / 20) * cos(radians(f * 1.8 + 180)) + fuelCenter[0]
            yb = int(self.dem['x'] / 20) * sin(radians(f * 1.8 + 180)) + fuelCenter[1]

            #line(self.screen, colors['needle'], (x, y), (xb, yb), 2)
            self.draw.multiline(colors['needle'], (x, y), (xb, yb), 2)



    def drawRedLine(self, maxrpm, maxo):
        colors = self.colors
        circles = self.circles
        v = maxrpm
        maxo = int(maxo + 1) * 1000

        while v < maxo:
            val = v * (270.0 / maxo)
            x = circles['rpm']['outer_circle'] * cos(radians(val + 90)) + self.dem['x'] / 2
            y = circles['rpm']['outer_circle'] * sin(radians(val + 90)) + self.dem['y'] / 2

            xb = int(self.dem['x'] / 7.25) * cos(radians(val + 90)) + self.dem['x'] / 2
            yb = int(self.dem['x'] / 7.25) * sin(radians(val + 90)) + self.dem['y'] / 2

            #lineDraw(x, y, obj, [xb, yb])
            #line(self.screen, colors['red-line'], (x, y), (xb, yb), 1)
            aaline(self.screen, colors['red-line'], (x, y), (xb, yb))
            v = v + 1

    def drawThrottle(self, val):
        colors = self.colors
        circles = self.circles
        for l in range(int(val / 4)):
            if l == 0:
                continue
            x = circles['rpm']['throttle-outer'] * sin(radians(l * 4 * -1)) + self.dem['x'] / 2
            y = circles['rpm']['throttle-outer'] * cos(radians(l * 4 * -1)) + self.dem['y'] / 2

            xb = circles['rpm']['throttle-inner'] * sin(radians(l * 4 * -1)) + self.dem['x'] / 2
            yb = circles['rpm']['throttle-inner'] * cos(radians(l * 4 * -1)) + self.dem['y'] / 2

            #lineDraw(x, y, obj, [xb, yb])
            #line(self.screen, colors['throttle'], (x, y), (xb, yb), 1)
            aaline(self.screen, colors['throttle'], (x, y), (xb, yb))

    def drawBrake(self, val):
        colors = self.colors
        circles = self.circles
        for l in range(int(val / 4)):
            if l == 0 or l == int(val / 4) - 1:
                continue
            x = circles['rpm']['throttle-outer'] * sin(radians(l * 4)) + self.dem['x'] / 2
            y = circles['rpm']['throttle-outer'] * cos(radians(l * 4)) + self.dem['y'] / 2

            xb = circles['rpm']['throttle-inner'] * sin(radians(l * 4)) + self.dem['x'] / 2
            yb = circles['rpm']['throttle-inner'] * cos(radians(l * 4)) + self.dem['y'] / 2

            #lineDraw(x, y, obj, [xb, yb])
            #line(self.screen, colors['brake'], (x, y), (xb, yb), 1)
            aaline(self.screen, colors['throttle'], (x, y), (xb, yb))

    def drawSpeed(self, val, speed, distance):
        colors = self.colors
        circles = self.circles

        #distance = distance
        distance = self.distance * 100
        distance = format(distance, '.1f')
        #print distance

        x = self.fonts['speed'].size(str(val))[0] / 2
        ya = self.fonts['speed'].size(str(val))[1] / 2
        text = self.fonts['speed'].render(str(val), True, colors['white'])
        self.screen.blit(text, (self.center[0] - x, self.center[1] - ya))

        x = self.fonts['odometer'].size(str(distance) + " Miles")[0]
        y = self.fonts['odometer'].size(str(distance) + " Miles")[1] / 2
        text = self.fonts['odometer'].render(str(distance) + " Miles", True, colors['white'])
        self.screen.blit(text, (self.center[0] - x + int(self.dem['x'] / 25), self.center[1] - y + int(self.dem['x'] / 20)))
        #print str(distance)

        x = self.fonts['std-med-bold'].size(str(speed / 8))[0] / 2
        y = self.fonts['std-med-bold'].size(str(speed / 8))[1] / 2
        text = self.fonts['std-med-bold'].render(str(speed / 8), True, colors['white'])
        self.screen.blit(text, (self.speedCenter[0] - x, self.speedCenter[1] - y + ya + 4))

        x = self.fonts['std-small'].size("MPH")[0] / 2
        y = self.fonts['std-small'].size("MPH")[1] / 2
        text = self.fonts['std-small'].render("MPH", True, colors['white'])
        self.screen.blit(text, (self.speedCenter[0] - x, self.speedCenter[1] - y + ya + 4 + int(self.dem['x'] / 60)))

        x = self.fonts['std-med'].size("RPM")[0] / 2
        yb = self.fonts['std-med'].size("RPM")[1] / 2
        text = self.fonts['std-med'].render("RPM", True, colors['white'])
        self.screen.blit(text, (self.center[0] - x, self.center[1] - yb - circles['rpm']['inner_circle'] / 1.5))

        x = self.fonts['std-small'].size("x1000")[0] / 2
        y = self.fonts['std-small'].size("x1000")[1] / 2
        text = self.fonts['std-small'].render("x1000", True, colors['white'])
        self.screen.blit(text, (self.center[0] - x, self.center[1] - y - circles['rpm']['inner_circle'] / 1.5 + yb + 4))
        #self.center[1] - y - circles['rpm']['inner_circle'] / 1.5 *

        #INDICATORS
        size = self.indisize
        c = self.speedCenter
        x = self.dem['x']
        xy = (c[0] + int(x / 9), c[1] + int(x / 20))

        #circle(self.screen, colors['white'], xy, int(self.dem['x'] / 6), 1)

        x = xy[0]
        y = xy[1]
        xb = int(self.dem['x'] / 6) * cos(radians(220)) + x
        yb = int(self.dem['x'] / 6) * sin(radians(220)) + y
        if self.runningGame == 'AssettoCorsa.exe':
            if self.cflags['abs'] > 0:
                self.screen.blit(self.indicators['abs'], (xb - size[0] / 2, yb - size[1] / 2))
            else:
                self.screen.blit(self.indicators['abs-unlit'], (xb - size[0] / 2, yb - size[1] / 2))
        else:
            if self.cflags['abs'] == '1' or self.cflags['engine-on'] == '0':
                self.screen.blit(self.indicators['abs'], (xb - size[0] / 2, yb - size[1] / 2))
            else:
                self.screen.blit(self.indicators['abs-unlit'], (xb - size[0] / 2, yb - size[1] / 2))

        xb = int(self.dem['x'] / 6) * cos(radians(205)) + x
        yb = int(self.dem['x'] / 6) * sin(radians(205)) + y
        if self.cflags['handbrake'] == '1' or self.cflags['engine-on'] == '0':
            self.screen.blit(self.indicators['handbrake'], (xb - size[0] / 2, yb - size[1] / 2))
        else:
            self.screen.blit(self.indicators['handbrake-unlit'], (xb - size[0] / 2, yb - size[1] / 2))

        xb = int(self.dem['x'] / 6) * cos(radians(190)) + x
        yb = int(self.dem['x'] / 6) * sin(radians(190)) + y
        if self.cflags['check-engine'] == '1' or self.cflags['engine-on'] == '0':
            self.screen.blit(self.indicators['check-engine'], (xb - size[0] / 2, yb - size[1] / 2))
        else:
            self.screen.blit(self.indicators['checkengine-unlit'], (xb - size[0] / 2, yb - size[1] / 2))

        #print f
        x = self.center[0]
        y = self.center[1]
        absy = 27

        if self.runningGame == 'pCARS2.exe' or self.runningGame == 'pCARS2AVX.exe':
            f = self.fuel * 100
            xb = self.secondaryindi * cos(radians(320)) + x
            yb = self.secondaryindi * sin(radians(320)) + y
            if f <= 25 or self.cflags['engine-on'] == '0':
                self.screen.blit(self.indicators['fuel'], (xb - size[0] / 2, yb - size[1] / 2))
            else:
                self.screen.blit(self.indicators['fuel-unlit'], (xb - size[0] / 2, yb - size[1] / 2))

        xb = self.secondaryindi * cos(radians(237 + absy)) + x
        yb = self.secondaryindi * sin(radians(237 + absy)) + y

        if self.cflags['headlights'] == '1' or self.cflags['engine-on'] == '0':
            self.screen.blit(self.indicators['headlights'], (xb - size[0] / 2, yb - size[1] / 2))
        else:
            self.screen.blit(self.indicators['headlights-unlit'], (xb - size[0] / 2, yb - size[1] / 2))

        xb = self.secondaryindi * cos(radians(237)) + x
        yb = self.secondaryindi * sin(radians(237)) + y

        if self.runningGame == 'AssettoCorsa.exe':
            if self.cflags['tc'] == 0:
                self.screen.blit(self.indicators['tc-off'], (xb - size[0] / 2, yb - size[1] / 2))
            else:
                self.screen.blit(self.indicators['tc-off-unlit'], (xb - size[0] / 2, yb - size[1] / 2))
        else:
            if self.cflags['tc'] == '1' or self.cflags['engine-on'] == '0':
                self.screen.blit(self.indicators['tc'], (xb - size[0] / 2, yb - size[1] / 2))
            else:
                self.screen.blit(self.indicators['tc-unlit'], (xb - size[0] / 2, yb - size[1] / 2))

        xb = self.secondaryindi * cos(radians(237 + (absy * 2))) + x
        yb = self.secondaryindi * sin(radians(237 + (absy * 2))) + y

        if self.runningGame == 'AssettoCorsa.exe':
            i = False
            for h in self.wheelpressure:
                if h < 29:
                    i = True
                    break

            if i:
                self.screen.blit(self.indicators['tp'], (xb - size[0] / 2, yb - size[1] / 2))
            else:
                self.screen.blit(self.indicators['tp-unlit'], (xb - size[0] / 2, yb - size[1] / 2))
        elif self.runningGame == 'pCARS2.exe' or self.runningGame == 'pCARS2AVX.exe':
            i = False
            for h in self.cflags['tires-inflated']:
                if h == 0:
                    i = True
                    break

            if i or self.cflags['engine-on'] == '0':
                self.screen.blit(self.indicators['tp'], (xb - size[0] / 2, yb - size[1] / 2))
            else:
                self.screen.blit(self.indicators['tp-unlit'], (xb - size[0] / 2, yb - size[1] / 2))

if __name__ == '__main__':
    d = dashboard(1280, 720)
    d.execute()
