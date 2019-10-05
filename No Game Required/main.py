import pygame
from pygame.locals import *
from pygame.draw import circle, line
from matplotlib.colors import hex2color
from math import sin, cos, tan, radians
from modules.udp import UDP

def finalColor(h):
    y = []
    h = hex2color(h)
    for x in h:
        y.append(int(x * 255))

    return (y[0], y[1], y[2])

class dashboard:
    def __init__(self, x, y):
        self.dem = {'x': x, 'y': y}
        self.circles = {'rpm': {'inner_circle': int(x / 10), 'outer_circle': int(x / 7), 'outer_circle2': int(x / 6.95), 'throttle-outer': int(x / 12), 'throttle-inner': int(x / 13)},
                        'speed': {'main': int(x / 8), 'circle2': int(x / 9), 'main2': int(x / 7.9)}
                        }
        self.colors = {'background': finalColor('#26212B'), 'white': finalColor('#FFFFFF'), 'needle': finalColor('#E0A600'),
                        'red-line': finalColor('#A92C1E'), 'throttle': finalColor('#D63826'), 'brake': finalColor('#3C52D6')
                        }
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
                        }
        self.needle = ''

        self.screen = pygame.display.set_mode((x, y))
        self.running = True

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

        #SECONDARY GUAGES
        circle(self.screen, colors['white'], (int(x), int(y)), int(self.dem['x'] / 20), 3)   #BOOST
        circle(self.screen, colors['white'], (int(xa), int(ya)), int(self.dem['x'] / 20), 3) #OIL
        circle(self.screen, colors['white'], (int(xb), int(yb)), int(self.dem['x'] / 19.5), 3) #WATER

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
            line(self.screen, colors['white'], (x, y), (xb, yb), 2)

        text = self.fonts['speed-extrasmall2'].render(str("Water Temp F"), True, colors['white'])
        x = self.fonts['speed-extrasmall2'].size("Water Temp F")[0]
        self.screen.blit(text, (waterCenter[0] - x / 2, waterCenter[1] + int(self.dem['x'] / 37) / 1.2))

        for val in range(41):
            x = int(self.dem['x'] / 20) * cos(radians(val * 6 + 150)) + waterCenter[0]
            y = int(self.dem['x'] / 20) * sin(radians(val * 6 + 150)) + waterCenter[1]

            xb = int(self.dem['x'] / 22.5) * cos(radians(val * 6 + 150)) + waterCenter[0]
            yb = int(self.dem['x'] / 22.5) * sin(radians(val * 6 + 150)) + waterCenter[1]

            #lineDraw(x, y, obj, [xb, yb])
            #circle(self.screen, colors['white'], (speedCenter[0], speedCenter[1]), int(self.dem['x'] / 9.5), 1)
            line(self.screen, colors['white'], (x, y), (xb, yb), 1)

        #BASE SPEEDOMETER
        circle(self.screen, colors['white'], speedCenter, circles['speed']['main2'], 2)

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
            line(self.screen, colors['white'], (x, y), (xb, yb), 3)

        for val in range(24):
            x = int(self.dem['x'] / 8.75) * cos(radians(val * 9 + 68)) + speedCenter[0]
            y = int(self.dem['x'] / 8.75) * sin(radians(val * 9 + 68)) + speedCenter[1]

            xb = int(self.dem['x'] / 8) * cos(radians(val * 9 + 68)) + speedCenter[0]
            yb = int(self.dem['x'] / 8) * sin(radians(val * 9 + 68)) + speedCenter[1]

            #lineDraw(x, y, obj, [xb, yb])
            #text = self.fonts['speed-small'].render(str(val), True, colors['white'])
            #self.screen.blit(text, (xt, yt))
            line(self.screen, colors['white'], (x, y), (xb, yb), 1)

        for val in range(120):
            x = int(self.dem['x'] / 8.35) * cos(radians(val * 1.8 + 68)) + speedCenter[0]
            y = int(self.dem['x'] / 8.35) * sin(radians(val * 1.8 + 68)) + speedCenter[1]

            xb = int(self.dem['x'] / 8) * cos(radians(val * 1.8 + 68)) + speedCenter[0]
            yb = int(self.dem['x'] / 8) * sin(radians(val * 1.8 + 68)) + speedCenter[1]

            #lineDraw(x, y, obj, [xb, yb])
            #text = self.fonts['speed-small'].render(str(val), True, colors['white'])
            #self.screen.blit(text, (xt, yt))
            line(self.screen, colors['white'], (x, y), (xb, yb), 1)


        #BASE RPM
        circle(self.screen, colors['background'], self.center, self.circles['rpm']['outer_circle2'])
        circle(self.screen, colors['white'], self.center, self.circles['rpm']['inner_circle'], drawwidth)
        circle(self.screen, colors['white'], self.center, self.circles['rpm']['outer_circle2'], 2)

        #REDLINE
        if maxrpm > 0:
            self.drawRedLine(maxrpm)

        #INDICATORS

        #RPM MAIN
        for val in range(11):
            x = circles['rpm']['outer_circle'] * cos(radians(val * 27 + 90)) + self.dem['x'] / 2
            y = circles['rpm']['outer_circle'] * sin(radians(val * 27 + 90)) + self.dem['y'] / 2

            xb = int(self.dem['x'] / 8) * cos(radians(val * 27 + 90)) + self.dem['x'] / 2
            yb = int(self.dem['x'] / 8) * sin(radians(val * 27 + 90)) + self.dem['y'] / 2

            xt = int(self.dem['x'] / 6.5) * cos(radians(val * 27 + 90)) + self.dem['x'] / 2
            yt = int(self.dem['x'] / 6.5) * sin(radians(val * 27 + 90)) + self.dem['y'] / 2

            #lineDraw(x, y, obj, [xb, yb])
            text = self.fonts['speed-small'].render(str(val), True, colors['white'])
            #self.screen.blit(text, (xt, yt))
            self.screen.blit(text, (xt - int(self.dem['x'] / 66) / 2 + 4, yt - int(self.dem['x'] / 66) / 2))
            line(self.screen, colors['white'], (x, y), (xb, yb), 3)

        #SECONDARY
        for val in range(21):
            x = circles['rpm']['outer_circle'] * cos(radians(val * 13.5 + 90)) + self.dem['x'] / 2
            y = circles['rpm']['outer_circle'] * sin(radians(val * 13.5 + 90)) + self.dem['y'] / 2

            xb = int(self.dem['x'] / 7.5) * cos(radians(val * 13.5 + 90)) + self.dem['x'] / 2
            yb = int(self.dem['x'] / 7.5) * sin(radians(val * 13.5 + 90)) + self.dem['y'] / 2

            #lineDraw(x, y, obj, [xb, yb])
            line(self.screen, colors['white'], (x, y), (xb, yb), 1)

        for val in range(101):
            x = circles['rpm']['outer_circle'] * cos(radians(val * 2.7 + 90)) + self.dem['x'] / 2
            y = circles['rpm']['outer_circle'] * sin(radians(val * 2.7 + 90)) + self.dem['y'] / 2

            xb = int(self.dem['x'] / 7.25) * cos(radians(val * 2.7 + 90)) + self.dem['x'] / 2
            yb = int(self.dem['x'] / 7.25) * sin(radians(val * 2.7 + 90)) + self.dem['y'] / 2

            #lineDraw(x, y, obj, [xb, yb])
            line(self.screen, colors['white'], (x, y), (xb, yb), 1)


        #self.draw_needle(0)

    def draw_needle(self, rpm, speed, water):
        l = rpm * .027
        b = speed * .1125

        water = water - 100
        c = float(water / 1)
        colors = self.colors
        circles = self.circles
        speedCenter = self.speedCenter
        waterCenter = self.waterCenter

        x = circles['rpm']['outer_circle'] * cos(radians(l + 90)) + self.dem['x'] / 2
        y = circles['rpm']['outer_circle'] * sin(radians(l + 90)) + self.dem['y'] / 2

        xb = circles['rpm']['inner_circle'] * cos(radians(l + 90)) + self.dem['x'] / 2
        yb = circles['rpm']['inner_circle'] * sin(radians(l + 90)) + self.dem['y'] / 2
        line(self.screen, colors['needle'], (x, y), (xb, yb), 7)


        #x = circles['rpm']['outer_circle'] * cos(radians(l + 68)) + speedCenter[0]
        #y = circles['rpm']['outer_circle'] * sin(radians(l + 68)) + speedCenter[1]

        x = speedCenter[0]
        y = speedCenter[1]

        xb = circles['speed']['main'] * cos(radians(b + 68)) + speedCenter[0]
        yb = circles['speed']['main'] * sin(radians(b + 68)) + speedCenter[1]
        line(self.screen, colors['needle'], (x, y), (xb, yb), 3)

        if water >= 0.0:
            x = waterCenter[0]
            y = waterCenter[1]

            xb = int(self.dem['x'] / 20) * cos(radians(c * 1.5 + 150)) + waterCenter[0]
            yb = int(self.dem['x'] / 20) * sin(radians(c * 1.5 + 150)) + waterCenter[1]
            line(self.screen, colors['needle'], (x, y), (xb, yb), 2)

    def drawRedLine(self, maxrpm):
        colors = self.colors
        circles = self.circles
        v = maxrpm

        while v < 10000:
            val = v * .027
            x = circles['rpm']['outer_circle'] * cos(radians(val + 90)) + self.dem['x'] / 2
            y = circles['rpm']['outer_circle'] * sin(radians(val + 90)) + self.dem['y'] / 2

            xb = int(self.dem['x'] / 7.25) * cos(radians(val + 90)) + self.dem['x'] / 2
            yb = int(self.dem['x'] / 7.25) * sin(radians(val + 90)) + self.dem['y'] / 2

            #lineDraw(x, y, obj, [xb, yb])
            line(self.screen, colors['red-line'], (x, y), (xb, yb), 1)
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
            line(self.screen, colors['throttle'], (x, y), (xb, yb), 1)

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
            line(self.screen, colors['brake'], (x, y), (xb, yb), 1)

    def drawSpeed(self, val, speed):
        colors = self.colors
        circles = self.circles
        x = self.fonts['speed'].size(str(val))[0] / 2
        ya = self.fonts['speed'].size(str(val))[1] / 2
        text = self.fonts['speed'].render(str(val), True, colors['white'])
        self.screen.blit(text, (self.center[0] - x, self.center[1] - ya))

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

    def execute(self):
        colors = self.colors
        pygame.display.set_caption('Dashboard')
        pygame.init()

        u = UDP()
        u.open()

        while self.running:
            try:
                data = u.receive()
                rpms = int(data['rpm']) * 10
                maxrpm = int(data['Max rpm'] * 10)
                throttle = int(data['Throttle'] * 180)
                brake = int(data['Brake'] * 180)
                speed = int(data['Speed'] * 2.23694 * 8)
                gear = int(data['Gear'])

                #WATER TEMPERATURE, OIL PRESSURE, FUEL, BOOST
                try:
                    water = int(data['water-temp'])
                except:
                    water = 0

                try:
                    oil = int(data['oil-pressure'])
                except:
                    oil = None


            except Exception as ex:
                print str(ex)
                rpms = 0
                maxrpm = 0
                throttle = 0
                brake = 0
                speed = 0
                gear = 0
                water = 0
                oil = 0

            self.screen.fill(colors['background'])

            if gear == 0:
                gear = "N"
            elif gear == -1:
                gear = "R"

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    u.close()
                    self.running = False
            self.draw_gauges(maxrpm, water, oil)
            self.drawThrottle(throttle)
            self.drawBrake(brake)
            self.drawSpeed(gear, speed)
            self.draw_needle(rpms, speed, 100)
            pygame.display.flip()



if __name__ == '__main__':
    d = dashboard(1280, 720)
    d.execute()
