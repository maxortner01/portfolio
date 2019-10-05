import pygame
from pygame.locals import *
from pygame.draw import circle, line, polygon, rect, aaline
from pygame.gfxdraw import line as gline
from matplotlib.colors import hex2color
from math import sin, cos, tan, radians
from modules.udp import UDP
from dir.pydraw import draw
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
        print "legacy"
        dir.base.__init__(self, x, y, game, e='dark')
        d = open('bin/data.txt', 'r')
        try:
            self.distance = json.loads(d.read())['odometer']['GT_Legacy'][self.runningGame]
        except:
            self.distance = 0
        d.close()
        e = e.lower()

        self.circles = {'v': int(self.dem['x'] / 5), 'h': int(self.dem['y'] / 4)}
        if e == 'classic':
            self.colors = {'background': finalColor('#26212B'), 'white': finalColor('#FFFFFF'), 'needle': finalColor('#E0A600'),
                            'red-line': finalColor('#A92C1E'), 'throttle': finalColor('#D63826'), 'brake': finalColor('#3C52D6'),
                            'dark-white': finalColor('#717275'), 'led': finalColor('#221D26'), 'led-lines': finalColor('#3D3545')
                            }
        else:
            self.colors = {'background': finalColor('#FFFFFF'), 'white': finalColor('#26212B'), 'needle': finalColor('#E0A600'),
                            'red-line': finalColor('#A92C1E'), 'throttle': finalColor('#D63826'), 'brake': finalColor('#3C52D6'),
                            'dark-white': finalColor('#717275'), 'led': finalColor('#221D26'), 'led-lines': finalColor('#3D3545')
                            }

        self.draw = draw(self.screen)



    def close(self):
        d = open('bin/data.txt', 'r')
        b = json.loads(d.read())
        d.close()

        d = open('bin/data.txt', 'w')
        #b['odometer']['BRZ'][self.runn] = self.distance
        b['odometer']['GT_Legacy'][self.runningGame] = self.distance
        d.write(json.dumps(b, indent=4))

        d.close()

    def draw_gauges(self, maxrpm, water, oil, fuelpress, drawwidth=2):
        colors = self.colors
        circles = self.circles
        h = int(self.dem['x'] / 4)
        v = int(self.dem['y'] / 4)

        self.rpmCenter = ((h * 3), (v * 2))
        rpmCenter = self.rpmCenter

        self.speedCenter = (h, (v * 2))
        speedCenter = self.speedCenter

        r = int(rpmCenter[0] / 5.3)

        y = v * 3
        x = h
        xa = h * 3

        left = (int(x + r), int(y - r))
        right = (int(xa - r), int(y - r))
        self.left = left
        self.right = right

        self.draw.multiline(colors['white'], (x, y), (xa, y), 3)
        self.draw.multiline(colors['white'], (x, int(y - r * 2.0)), (xa, int(y - r * 2.0)), 3)
        self.draw.multiline(colors['white'], left, right, 3)

        #xb = r * cos(radians(350)) + speedCenter[0]
        #xb = r * cos(radians(350)) + speedCenter[1]

        xa = rpmCenter[0]
        ya = rpmCenter[1]

        x = r * cos(radians(190)) + xa
        y = r * sin(radians(190)) + ya

        a = (x, y)

        xa = speedCenter[0]
        ya = speedCenter[1]

        xb = r * cos(radians(350)) + xa
        yb = r * sin(radians(350)) + ya

        b = (xb, yb)
        #line(self.screen, colors['white'], a, b, drawwidth)
        self.draw.multiline(colors['white'], a, b, 3)

        self.fuelbar = [left, right]
        self.r = r
        self.topmiddle = a[1]

        #fuel
        for x in range(3):
            amt = ((right[0] - left[0]) / 2) * x
            x = int(amt + left[0])

            #line(self.screen, colors['white'], (x, left[1]), (x, left[1] - r / 10), 3)
            self.draw.multiline(colors['white'], (x, left[1]), (x, left[1] - r / 10), 5)

        #print ""
        for x in range(7):
            amt = ((right[0] - left[0]) / 6.0) * x
            x = int(amt + left[0])

            #line(self.screen, colors['white'], (x, left[1]), (x, left[1] - r / 15))
            self.draw.multiline(colors['white'], (x, left[1]), (x, left[1] - r / 15), 2)

        #speedometer
        for val in range(12):
            text = self.fonts['speed-small'].render(str(val * 20), True, colors['white'])
            x = r * cos(radians(val * 24.5 + 90)) + speedCenter[0]
            y = r * sin(radians(val * 24.5 + 90)) + speedCenter[1]

            xb = (r / 1.15) * cos(radians(val * 24.5 + 90)) + speedCenter[0]
            yb = (r / 1.15) * sin(radians(val * 24.5 + 90)) + speedCenter[1]

            xt = (r / 1.35) * cos(radians(val * 24.5 + 90)) + speedCenter[0]
            yt = (r / 1.35) * sin(radians(val * 24.5 + 90)) + speedCenter[1]

            self.screen.blit(text, (xt - self.fonts['speed-small'].size(str(val * 20))[0] / 2, yt - self.fonts['speed-small'].size(str(val * 20))[1] / 2))
            #line(self.screen, colors['white'], (x, y), (xb, yb), 3)
            self.draw.multiline(colors['white'], (x, y), (xb, yb), 3)

        for val in range(23):
            x = r * cos(radians(val * 12.25 + 90)) + speedCenter[0]
            y = r * sin(radians(val * 12.25 + 90)) + speedCenter[1]

            xb = (r / 1.1) * cos(radians(val * 12.25 + 90)) + speedCenter[0]
            yb = (r / 1.1) * sin(radians(val * 12.25 + 90)) + speedCenter[1]

            #line(self.screen, colors['white'], (x, y), (xb, yb), 2)
            self.draw.multiline(colors['white'], (x, y), (xb, yb), 2)

        for val in range(111):
            x = r * cos(radians(val * 2.45 + 90)) + speedCenter[0]
            y = r * sin(radians(val * 2.45 + 90)) + speedCenter[1]

            xb = (r / 1.05) * cos(radians(val * 2.45 + 90)) + speedCenter[0]
            yb = (r / 1.05) * sin(radians(val * 2.45 + 90)) + speedCenter[1]

            #line(self.screen, colors['white'], (x, y), (xb, yb), 1)
            #self.draw.multiline(colors['white'], (x, y), (xb, yb), 1)
            aaline(self.screen, colors['white'], (x, y), (xb, yb))


        #rpm
        y = ""
        for x in range(5 - len(str(maxrpm))):
            y = y + '0'

        #print y + str(maxrpm)[:1]
        maximum = (y + str(maxrpm))[:2]
        if int(maximum) <= 10:
            maximum = 9

        if maxrpm > 0:
            self.drawRedLine(maxrpm, int(maximum))
        else:
            self.drawRedLine(0, int(0))

        #INDICATORS
        self.maximum = int(maximum) + 1
        maximum = self.maximum
        twomax = int(maximum) * 2
        #RPM MAIN
        for val in range(11 + (maximum - 10)):
            x = r * cos(radians(val * (270.0 / maximum) + 90)) + rpmCenter[0]
            y = r * sin(radians(val * (270.0 / maximum) + 90)) + rpmCenter[1]

            xb = (r / 1.15) * cos(radians(val * (270.0 / maximum) + 90)) + rpmCenter[0]
            yb = (r / 1.15) * sin(radians(val * (270.0 / maximum) + 90)) + rpmCenter[1]

            xt = (r / 1.35) * cos(radians(val * (270.0 / maximum) + 90)) + rpmCenter[0]
            yt = (r / 1.35) * sin(radians(val * (270.0 / maximum) + 90)) + rpmCenter[1]

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
            x = r * cos(radians(val * (270.0 / twomax) + 90)) + rpmCenter[0]
            y = r * sin(radians(val * (270.0 / twomax) + 90)) + rpmCenter[1]

            xb = (r / 1.1) * cos(radians(val * (270.0 / twomax) + 90)) + rpmCenter[0]
            yb = (r / 1.1) * sin(radians(val * (270.0 / twomax) + 90)) + rpmCenter[1]

            #lineDraw(x, y, obj, [xb, yb])
            #line(self.screen, colors['white'], (x, y), (xb, yb), 1)
            aaline(self.screen, colors['white'], (x, y), (xb, yb))

        for val in range(101 + ((maximum * 10) - 100)):
            x = r * cos(radians(val * (270.0 / (maximum * 10)) + 90)) + rpmCenter[0]
            y = r * sin(radians(val * (270.0 / (maximum * 10)) + 90)) + rpmCenter[1]

            xb = (r / 1.05) * cos(radians(val * (270.0 / (maximum * 10)) + 90)) + rpmCenter[0]
            yb = (r / 1.05) * sin(radians(val * (270.0 / (maximum * 10)) + 90)) + rpmCenter[1]

            #lineDraw(x, y, obj, [xb, yb])
            #line(self.screen, colors['white'], (x, y), (xb, yb), 1)
            aaline(self.screen, colors['white'], (x, y), (xb, yb))

        self.draw.multicircle(colors['white'], rpmCenter, r, 3)
        self.draw.multicircle(colors['white'], speedCenter, r, 3)

        if self.runningGame == 'pCARS2.exe' or self.runningGame == 'pCARS2AVX.exe':
            ra = int(r / 3.7)
            y = int(left[1] - (r / 1.7))
            length = right[1] - left[1]

            #oil
            self.oilCenter = (left[0] + ra / 2  + int(left[1] / 25), y)
            #circle(self.screen, colors['white'], self.oilCenter, ra, 2)
            self.draw.multicircle(colors['white'], self.oilCenter, ra, 2)

            #water
            self.waterCenter = (self.dem['x'] / 2, y)
            #circle(self.screen, colors['white'], self.waterCenter, ra, 2)
            self.draw.multicircle(colors['white'], self.waterCenter, ra, 2)

            #fuelpress
            self.fuelCenter = (self.dem['x'] / 2 + (self.dem['x'] / 2 - (left[0] + ra / 2  + int(left[1] / 25))), y)
            #circle(self.screen, colors['white'], self.fuelCenter, ra, 2)
            self.draw.multicircle(colors['white'], self.fuelCenter, ra, 2)

            ra = int(r / 3.8)

            waterCenter = self.waterCenter
            for val in range(5):
                v = 100 + (val * 40)
                text = self.fonts['speed-extrasmall2'].render(str(v), True, colors['white'])
                x = ra * cos(radians(val * 60 + 150)) + waterCenter[0]
                y = ra * sin(radians(val * 60 + 150)) + waterCenter[1]

                xb = (r / 4.8) * cos(radians(val * 60 + 150)) + waterCenter[0]
                yb = (r / 4.8) * sin(radians(val * 60 + 150)) + waterCenter[1]

                xt = (r / 6.8) * cos(radians(val * 60 + 150)) + waterCenter[0]
                yt = (r / 6.8) * sin(radians(val * 60 + 150)) + waterCenter[1]

                #lineDraw(x, y, obj, [xb, yb])
                xc = self.fonts['speed-extrasmall2'].size(str(v))[0]
                yc = self.fonts['speed-extrasmall2'].size(str(v))[1]
                self.screen.blit(text, (xt - xc / 2, yt - yc / 2 - 2))
                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                #line(self.screen, colors['white'], (x, y), (xb, yb), 2)
                self.draw.multiline(colors['white'], (x, y), (xb, yb), 2)

            text = self.fonts['speed-extrasmall2'].render(str("Water Temp F"), True, colors['white'])
            x = self.fonts['speed-extrasmall2'].size("Water Temp F")[0]
            self.screen.blit(text, (waterCenter[0] - x / 2, waterCenter[1] + int(self.dem['x'] / 37) / 1.5))

            text = self.fonts['speed-extrasmall2'].render(str("Fuel Pres. KPA"), True, colors['white'])
            x = self.fonts['speed-extrasmall2'].size("Fuel Pres. KPA")[0]
            self.screen.blit(text, (self.fuelCenter[0] - x / 2, self.fuelCenter[1] + int(self.dem['x'] / 37) / 1.5))

            text = self.fonts['speed-extrasmall2'].render(str("Oil Pres. KPA"), True, colors['white'])
            x = self.fonts['speed-extrasmall2'].size("Oil Pres. KPA")[0]
            self.screen.blit(text, (self.oilCenter[0] - x / 2, self.oilCenter[1] + int(self.dem['x'] / 37) / 1.5))

            text = self.fonts['speed-extrasmall'].render(str(self.fps) + " fps", True, colors['white'])
            x = self.fonts['speed-extrasmall'].size(str(self.fps) + " fps")[0]
            self.screen.blit(text, (0, 0))


            for val in range(41):
                x = ra * cos(radians(val * 6 + 150)) + waterCenter[0]
                y = ra * sin(radians(val * 6 + 150)) + waterCenter[1]

                xb = (r / 4.3) * cos(radians(val * 6 + 150)) + waterCenter[0]
                yb = (r / 4.3) * sin(radians(val * 6 + 150)) + waterCenter[1]

                #lineDraw(x, y, obj, [xb, yb])
                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                aaline(self.screen, colors['white'], (x, y), (xb, yb))

            #OIL
            oilCenter = self.oilCenter
            for val in range(5):
                v = val * 20
                text = self.fonts['speed-extrasmall2'].render(str(v), True, colors['white'])
                x = ra * cos(radians(val * 60 + 150)) + oilCenter[0]
                y = ra * sin(radians(val * 60 + 150)) + oilCenter[1]

                xb = (r / 4.8) * cos(radians(val * 60 + 150)) + oilCenter[0]
                yb = (r / 4.8) * sin(radians(val * 60 + 150)) + oilCenter[1]

                xt = (r / 6.8) * cos(radians(val * 60 + 150)) + oilCenter[0]
                yt = (r / 6.8) * sin(radians(val * 60 + 150)) + oilCenter[1]

                #lineDraw(x, y, obj, [xb, yb])
                xc = self.fonts['speed-extrasmall2'].size(str(v))[0]
                yc = self.fonts['speed-extrasmall2'].size(str(v))[1]
                self.screen.blit(text, (xt - xc / 2, yt - yc / 2 + 2))
                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                #line(self.screen, colors['white'], (x, y), (xb, yb), 2)
                self.draw.multiline(colors['white'], (x, y), (xb, yb), 2)

            for val in range(8):
                x = ra * cos(radians(val * 30 + 150)) + oilCenter[0]
                y = ra * sin(radians(val * 30 + 150)) + oilCenter[1]

                xb = (r / 4.3) * cos(radians(val * 30 + 150)) + oilCenter[0]
                yb = (r / 4.3) * sin(radians(val * 30 + 150)) + oilCenter[1]

                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                aaline(self.screen, colors['white'], (x, y), (xb, yb))

            for val in range(16):
                x = ra * cos(radians(val * 15 + 150)) + oilCenter[0]
                y = ra * sin(radians(val * 15 + 150)) + oilCenter[1]

                xb = (r / 4.3) * cos(radians(val * 15 + 150)) + oilCenter[0]
                yb = (r / 4.3) * sin(radians(val * 15 + 150)) + oilCenter[1]

                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                aaline(self.screen, colors['white'], (x, y), (xb, yb))

            fuelCenter = self.fuelCenter
            for val in range(6):
                v = val * 20
                text = self.fonts['speed-extrasmall2'].render(str(v), True, colors['white'])
                x = ra * cos(radians(val * 50 + 145)) + fuelCenter[0]
                y = ra * sin(radians(val * 50 + 145)) + fuelCenter[1]

                xb = (r / 4.8) * cos(radians(val * 50 + 145)) + fuelCenter[0]
                yb = (r / 4.8) * sin(radians(val * 50 + 145)) + fuelCenter[1]

                xt = (r / 6.8) * cos(radians(val * 50 + 145)) + fuelCenter[0]
                yt = (r / 6.8) * sin(radians(val * 50 + 145)) + fuelCenter[1]

                #lineDraw(x, y, obj, [xb, yb])
                xc = self.fonts['speed-extrasmall2'].size(str(v))[0]
                yc = self.fonts['speed-extrasmall2'].size(str(v))[1]
                self.screen.blit(text, (xt - xc / 2, yt - yc / 2 + 2))
                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                #line(self.screen, colors['white'], (x, y), (xb, yb), 2)
                self.draw.multiline(colors['white'], (x, y), (xb, yb), 2)

            for val in range(5):
                x = ra * cos(radians(val * 50 + 170)) + fuelCenter[0]
                y = ra * sin(radians(val * 50 + 170)) + fuelCenter[1]

                xb = (r / 4.4) * cos(radians(val * 50 + 170)) + fuelCenter[0]
                yb = (r / 4.4) * sin(radians(val * 50 + 170)) + fuelCenter[1]
                #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
                aaline(self.screen, colors['white'], (x, y), (xb, yb), 1)

            #line(self.screen, colors['white'], (x, left[1]), (x, left[1] + r), 1)
            self.left = left
            self.right = right


    def draw_needle(self, rpm, speed, water=-1, oil=-1, fuel=(100, 0), fuelpress=-1):
        colors = self.colors
        circles = self.circles

        #fuel
        f = fuel[0] * 100
        x = (f * 2.78) + self.fuelbar[0][0]
        left = self.fuelbar[0]
        r = self.r
        if water == 32:
            water = 0
        else:
            water = water - 100

        #print "\t\t\t" + str(f)
        #line(self.screen, colors['needle'], (x, left[1]), (x, self.topmiddle), 4)
        self.draw.multiline(colors['needle'], (x, left[1]), (x, self.topmiddle), 4)

        if water <= -100:
            c = 0
        else:
            c = abs(float(water / 1))

        #speedometer

        s = (speed / 8) * 1.227
        #print s / 1.227
        xb = r * cos(radians(s + 90)) + self.speedCenter[0]
        yb = r * sin(radians(s + 90)) + self.speedCenter[1]
        self.draw.multiline(colors['needle'], self.speedCenter, (xb, yb), 4)

        #rpm
        s = 270.0 / self.maxo
        #print s
        #print s / 1.227
        xb = r * cos(radians(rpm * s + 90)) + self.rpmCenter[0]
        yb = r * sin(radians(rpm * s + 90)) + self.rpmCenter[1]
        self.draw.multiline(colors['needle'], self.rpmCenter, (xb, yb), 4)

        if self.runningGame == 'pCARS2.exe' or self.runningGame == 'pCARS2AVX.exe':
            #WATER
            waterCenter = self.waterCenter
            oilCenter = self.oilCenter
            fuelCenter = self.fuelCenter

            if c >= 0.0:
                x = waterCenter[0]
                y = waterCenter[1]

                xb = int(r / 3.8) * cos(radians(c * 1.5 + 150)) + waterCenter[0]
                yb = int(r / 3.8) * sin(radians(c * 1.5 + 150)) + waterCenter[1]
                self.draw.multiline(colors['needle'], (x, y), (xb, yb), 2)
            elif c < 0:
                x = waterCenter[0]
                y = waterCenter[1]

                xb = int(r / 3.8) * cos(radians(50 * 1.5 + 150)) + waterCenter[0]
                yb = int(r / 3.8) * sin(radians(50 * 1.5 + 150)) + waterCenter[1]
                self.draw.multiline(colors['needle'], (x, y), (xb, yb), 2)

            x = oilCenter[0]
            y = oilCenter[1]

            xb = int(r / 3.8) * cos(radians(oil * 1.5 + 150)) + oilCenter[0]
            yb = int(r / 3.8) * sin(radians(oil * 1.5 + 150)) + oilCenter[1]
            self.draw.multiline(colors['needle'], (x, y), (xb, yb), 2)

            x = fuelCenter[0]
            y = fuelCenter[1]

            xb = int(r / 3.8) * cos(radians(fuelpress * 1.2 + 145)) + fuelCenter[0]
            yb = int(r / 3.8) * sin(radians(fuelpress * 1.2 + 145)) + fuelCenter[1]
            self.draw.multiline(colors['needle'], (x, y), (xb, yb), 2)


            left = self.left
            right = self.right
            x = left[0] + int(self.dem['x'] / 60)
            y = right[0] - int(self.dem['x'] / 60)
            fifty = int(self.dem['x'] / 50)
            width = y - x
            b = left[1] + 4 * 1.0
            size = self.indisize
            height = float(b - self.r)
            #rect(self.screen, colors['led'], (x, left[1] + 1, width, height), 0)
            #line(self.screen, colors['white'], (x, left[1] + 1), (x, left[1] + 1 + height), 1)

            if self.runningGame == 'AssettoCorsa.exe':
                if self.cflags['abs'] > 0:
                    self.screen.blit(self.indicators['abs'], (x - size[0] / 2 + 2, left[1] + 1 - size[1] / 2 + (fifty * 1)))
                else:
                    self.screen.blit(self.indicators['abs-unlit'], (x - size[0] / 2 + 2, (left[1] + 1 - size[1] / 2) + (fifty * 1)))
            else:
                if self.cflags['abs'] == '1' or self.cflags['engine-on'] == '0':
                    self.screen.blit(self.indicators['abs'], (x - size[0] / 2 + 2, left[1] + 1 - size[1] / 2 + (fifty * 1)))
                else:
                    self.screen.blit(self.indicators['abs-unlit'], (x - size[0] / 2 + 2, (left[1] + 1 - size[1] / 2 + (fifty * 1))))

            if self.cflags['handbrake'] == '1' or self.cflags['engine-on'] == '0':
                self.screen.blit(self.indicators['handbrake'], (x - size[0] / 2, left[1] + 1 - size[1] / 2 + (fifty * 3)))
            else:
                self.screen.blit(self.indicators['handbrake-unlit'], (x - size[0] / 2, left[1] + 1 - size[1] / 2 + (fifty * 3)))

            if self.cflags['check-engine'] == '1' or self.cflags['engine-on'] == '0':
                self.screen.blit(self.indicators['check-engine'], (x - size[0] / 2, left[1] + 1 - size[1] / 2 + (fifty * 5)))
            else:
                self.screen.blit(self.indicators['checkengine-unlit'], (x - size[0] / 2, left[1] + 1 - size[1] / 2 + (fifty * 5)))

            x = right[0] - int(self.dem['x'] / 60)

            if self.cflags['headlights'] == '1' or self.cflags['engine-on'] == '0':
                self.screen.blit(self.indicators['headlights'], (x - size[0] / 2 + 2, left[1] + 1 - size[1] / 2 + (fifty * 1)))
            else:
                self.screen.blit(self.indicators['headlights-unlit'], (x - size[0] / 2 + 2, left[1] + 1 - size[1] / 2 + (fifty * 1)))

            if self.runningGame == 'AssettoCorsa.exe':
                if self.cflags['tc'] == 0:
                    self.screen.blit(self.indicators['tc-off'], (x - size[0] / 2 + 2, left[1] + 1 - size[1] / 2 + (fifty * 3)))
                else:
                    self.screen.blit(self.indicators['tc-off-unlit'], (x - size[0] / 2 + 2, left[1] + 1 - size[1] / 2 + (fifty * 3)))
            else:
                if self.cflags['tc'] == '1' or self.cflags['engine-on'] == '0':
                    self.screen.blit(self.indicators['tc'], (x - size[0] / 2 + 2, left[1] + 1 - size[1] / 2 + (fifty * 3)))
                else:
                    self.screen.blit(self.indicators['tc-unlit'], (x - size[0] / 2 + 2, left[1] + 1 - size[1] / 2 + (fifty * 3)))

            if self.runningGame == 'AssettoCorsa.exe':
                i = False
                for h in self.wheelpressure:
                    if h < 29:
                        i = True
                        break

                if i:
                    self.screen.blit(self.indicators['tp'], (x - size[0] / 2 + 2, left[1] + 1 - size[1] / 2 + (fifty * 5)))
                else:
                    self.screen.blit(self.indicators['tp-unlit'], (x - size[0] / 2 + 2, left[1] + 1 - size[1] / 2 + (fifty * 5)))
            elif self.runningGame == 'pCARS2.exe' or self.runningGame == 'pCARS2AVX.exe':
                i = False
                for h in self.cflags['tires-inflated']:
                    if h == 0:
                        i = True
                        break

                if i or self.cflags['engine-on'] == '0':
                    self.screen.blit(self.indicators['tp'], (x - size[0] / 2 + 2, left[1] + 1 - size[1] / 2 + (fifty * 5)))
                else:
                    self.screen.blit(self.indicators['tp-unlit'], (x - size[0] / 2 + 2, left[1] + 1 - size[1] / 2 + (fifty * 5)))





    def drawRedLine(self, maxrpm, maxo):
        colors = self.colors
        circles = self.circles
        v = maxrpm
        self.maxo = int(maxo + 1) * 1000
        maxo = self.maxo
        r = int(self.rpmCenter[0] / 5.35)

        if maxrpm == 0:
            return

        while v < maxo:
            val = v * (270.0 / maxo)
            x = r * cos(radians(val + 90)) + self.rpmCenter[0]
            y = r * sin(radians(val + 90)) + self.rpmCenter[1]

            xb = (r / 1.05) * cos(radians(val + 90)) + self.rpmCenter[0]
            yb = (r / 1.05) * sin(radians(val + 90)) + self.rpmCenter[1]

            #lineDraw(x, y, obj, [xb, yb])
            line(self.screen, colors['red-line'], (x, y), (xb, yb), 2)
            v = v + 1

    def drawThrottle(self, val):
        colors = self.colors
        circles = self.circles

    def drawBrake(self, val):
        colors = self.colors
        circles = self.circles

    def drawSpeed(self, gear, speed, distance):
        colors = self.colors
        circles = self.circles
        left = self.left
        right = self.right

        x = left[0] + int(self.dem['x'] / 25)
        y = right[0] - int(self.dem['x'] / 25)
        width = y - x
        b = left[1] + 4 * 1.0
        height = float(b - self.r)
        rect(self.screen, colors['led'], (x, left[1] + 1, width, height), 0)
        center = ((width / 2) + x, (height / 2) + left[1] + 1)
        l = height - int(self.dem['x'] / 35)
        xy = (x, (left[1] + 4) + l)
        xy2 = (x + width, (left[1] + 4) + l)
        midways = ((xy[0], xy[1] - l + int(self.dem['x'] / 8)), (xy2[0], xy[1] - l + int(self.dem['x'] / 8)))
        line(self.screen, colors['led-lines'], xy, xy2, 1)
        #line(self.screen, colors['white'], midways[0], midways[1], 1)
        #distance = distance
        #print distance * 100
        distance = self.distance * 100
        distance = format(distance, '.1f')
        #print distance

        #INDICATORS
        ya = self.fonts['speed'].size(str(gear))[1] / 2
        xs = self.fonts['speed'].size(str(gear))[0]
        ys = self.fonts['speed'].size(str(gear))[1]
        text = self.fonts['speed'].render(str(gear), True, colors['white'])
        self.screen.blit(text, (center[0] - (xs / 2), center[1] - (ys / 2)))

        xs = self.fonts['speed-extrasmall'].size(str(distance) + ' Miles')[0]
        ys = self.fonts['speed-extrasmall'].size(str(distance) + ' Miles')[1]
        text = self.fonts['speed-extrasmall'].render(str(distance) + ' Miles', True, colors['white'])
        self.screen.blit(text, (midways[0][0] + 8, midways[0][1] - (ys/2-3)))

        xs = self.fonts['std-med-bold'].size(str(speed / 8))[0] / 2
        ys = self.fonts['std-med-bold'].size(str(speed / 8))[1] / 2
        text = self.fonts['std-med-bold'].render(str(speed / 8), True, colors['white'])
        self.screen.blit(text, (self.speedCenter[0] - xs, self.speedCenter[1] - ys + ya + 4))

        xs = self.fonts['std-small'].size("MPH")[0] / 2
        ys = self.fonts['std-small'].size("MPH")[1] / 2
        text = self.fonts['std-small'].render("MPH", True, colors['white'])
        self.screen.blit(text, (self.speedCenter[0] - xs, self.speedCenter[1] - ys + ya + 4 + int(self.dem['x'] / 60)))

        #line(self.screen, colors['white'], (x, left[1]), (x, left[1] + r), 1)
        #polygon(self.screen, color['white'], ((x, left[1]), (x, left[1] + r), (y, left[1]), (y, left[1] + r)), 1)


        rect(self.screen, colors['white'], (x, left[1] + 1, width, height), 1)



if __name__ == '__main__':
    d = dashboard(1280, 720)
    d.execute()
