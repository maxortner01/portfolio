import pygame, menus, sys, os
from matplotlib.colors import hex2color
from pygame.draw import rect, circle
from pygame.font import Font as f
from math import sqrt, cos, sin, radians
from menus import Font

def finalColor(h):
    y = []
    h = hex2color(h)
    for x in h:
        y.append(int(x * 255))

    return (y[0], y[1], y[2])

directory = ""

def length(p1, p2):
    return sqrt((p1[1] - p2[1]) ** 2 + (p1[0] - p2[0]) ** 2)

def inside(box, mousepos):
    if mousepos[0] >= box[0] and mousepos[0] <= (box[0] + box[2]) and mousepos[1] >= box[1] and mousepos[1] <= (box[1] + box[3]):
        return True

class dashEditor:
    def __init__(self, x, y, d):
        sys.path.insert(0, d + "bin/")
        directory = d
        pygame.font.init()

        from dashes.dir.pydraw import draw

        self.dem    = {'x': x, 'y': y}
        self.center = (x / 2, y / 2)

        self.colors = {'white': finalColor('#FFFFFF'), 'black': finalColor('#26212B'), 'needle': finalColor('#E0A600')}

        self.screen = pygame.display.set_mode((x, y))
        self.running = True
        self.mpos = (0, 0)

        self.menu = menus.Menu(self.screen, d, self.dem, self.colors)
        self.draw = draw(self.screen)
        self.children = []

        self.points = (0, 0, 0, 0)

    def drawGaugeIndicators(self, t, center, radius):
        colors = self.colors

        if t == 'RPM':
            maximum = 10
            twomax = maximum * 2

            rpmCenter = center
            r         = radius

            for val in range(11 + (maximum - 10)):
                x = r * cos(radians(val * (270.0 / maximum) + 90)) + rpmCenter[0]
                y = r * sin(radians(val * (270.0 / maximum) + 90)) + rpmCenter[1]

                xb = (r / 1.15) * cos(radians(val * (270.0 / maximum) + 90)) + rpmCenter[0]
                yb = (r / 1.15) * sin(radians(val * (270.0 / maximum) + 90)) + rpmCenter[1]

                xt = (r / 1.35) * cos(radians(val * (270.0 / maximum) + 90)) + rpmCenter[0]
                yt = (r / 1.35) * sin(radians(val * (270.0 / maximum) + 90)) + rpmCenter[1]

                text = Font('Laconic_Light', int(radius / 9)).render(str(val), True, colors['white'])
                self.screen.blit(text, (xt - int(self.dem['x'] / 66) / 2 + 4, yt - int(self.dem['x'] / 66) / 2))

                self.draw.multiline(colors['white'], (x, y), (xb, yb), 3)

            for val in range(21 + (twomax - 20)):
                x = r * cos(radians(val * (270.0 / twomax) + 90)) + rpmCenter[0]
                y = r * sin(radians(val * (270.0 / twomax) + 90)) + rpmCenter[1]

                xb = (r / 1.1) * cos(radians(val * (270.0 / twomax) + 90)) + rpmCenter[0]
                yb = (r / 1.1) * sin(radians(val * (270.0 / twomax) + 90)) + rpmCenter[1]

                self.draw.line(colors['white'], (x, y), (xb, yb))

            for val in range(101 + ((maximum * 10) - 100)):
                x = r * cos(radians(val * (270.0 / (maximum * 10)) + 90)) + rpmCenter[0]
                y = r * sin(radians(val * (270.0 / (maximum * 10)) + 90)) + rpmCenter[1]

                xb = (r / 1.05) * cos(radians(val * (270.0 / (maximum * 10)) + 90)) + rpmCenter[0]
                yb = (r / 1.05) * sin(radians(val * (270.0 / (maximum * 10)) + 90)) + rpmCenter[1]

                self.draw.line(colors['white'], (x, y), (xb, yb))

            self.draw.multiline(colors['needle'], center, (center[0], center[1] + radius), width=int(radius/35))

    def drawMenu(self, pos):
        menu = self.menu
        p = self.mpos
        inside = False

        if self.mpos[0] >= menu.pos[0] and self.mpos[0] <= (menu.pos[0] + menu.lengthHeight[0]) and self.mpos[1] >= menu.pos[1] and self.mpos[1] <= (menu.pos[1] + menu.lengthHeight[1]):
            inside = True

        if menu.visible and inside == False:
            menu.visible = False
        else:
            menu.visible = True

    def drawChildren(self):
        for child in self.children:
            if child.type == 'RPM':
                self.drawGaugeIndicators(child.type, child.center, child.radius)

                self.draw.multicircle(self.colors['white'], child.center, child.radius, child.width)

            if child.guide:
                rect(self.screen, self.colors['white'], (child.center[0] - child.radius - child.width, child.center[1] - child.radius - child.width, (child.radius * 2) + child.width * 2, (child.radius * 2) + child.width * 2), 1)

                self.points = (child.center[0] - child.radius - child.width + (child.radius * 2) + child.width * 2,
                          child.center[1] - child.radius - child.width,
                          10,
                          int(((child.radius * 2) + child.width * 2) / 1)
                         )

                rect(self.screen, self.colors['white'], self.points, 1)


    def disableGuides(self):
        for child in self.children:
            child.guide = False

    def execute(self):
        colors = self.colors
        p = self.mpos
        pygame.display.set_caption('Dashboard Editor')
        pygame.init()

        frames = 0
        clickframe = 0
        currenttime = pygame.time.get_ticks()
        lastclick = 0
        lastclickpos = (0, 0)

        self.changingRadius = False

        down = False

        drawpos = ()

        while self.running:
            menu = self.menu
            self.screen.fill(colors['black'])
            self.mpos = pygame.mouse.get_pos()

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False
                elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                    lastclickpos = pygame.mouse.get_pos()
                    down = True

                    if lastclick > 0 and currenttime - lastclick <= 200:
                        if self.mpos[0] >= menu.pos[0] and self.mpos[0] <= (menu.pos[0] + menu.lengthHeight[0]) and self.mpos[1] >= menu.pos[1] and self.mpos[1] <= (menu.pos[1] + menu.lengthHeight[1]):
                            self.menu.visible = True
                            #REGISTER DOUBLE CLICK IN MENU
                        else:
                            drawpos = pygame.mouse.get_pos()
                            self.drawMenu(drawpos)
                            lastclick = 0
                    elif self.menu.visible == True and currenttime - lastclick > 200:
                        if self.mpos[0] >= menu.pos[0] and self.mpos[0] <= (menu.pos[0] + menu.lengthHeight[0]) and self.mpos[1] >= menu.pos[1] and self.mpos[1] <= (menu.pos[1] + menu.lengthHeight[1]):
                            self.menu.visible = True
                            #REGISTER CLICK IN MENU
                            newpos = (self.mpos[0] - drawpos[0], self.mpos[1] - drawpos[1])
                            obj = self.menu.register(newpos)
                            if obj != None:
                                if obj.center == (0, 0):
                                    obj.center = drawpos

                                self.children.append(obj)

                                self.menu.visible = False
                        else:
                            self.menu.visible = False

                    clickframe = frames
                    lastclick = pygame.time.get_ticks()

                    for child in self.children:
                        if length(self.mpos, child.center) <= child.radius or inside(self.points, self.mpos):
                            self.radius = child.radius
                            self.childCenter = child.center
                            child.guide = True
                        else:
                            child.guide = False

                elif event.type == pygame.MOUSEBUTTONUP and event.button == 1:
                    down = False

            print self.children

            for child in self.children:
                print child.center
                #print str(length(self.mpos, child.center)) + "\t" + str(child.radius)
                if child.guide == True and down and lastclickpos != self.mpos and not inside(self.points, self.mpos) and not self.changingRadius and length(self.mpos, child.center) <= child.radius:
                    xdif = self.mpos[0] - lastclickpos[0]
                    ydif = self.mpos[1] - lastclickpos[1]
                    child.center = (self.childCenter[0] + xdif, self.childCenter[1] + ydif)
                #    print 'buttt'
                elif inside(self.points, self.mpos) and down and child.guide:
                    dif = self.mpos[0] - lastclickpos[0]
                    child.radius = self.radius + dif

            self.menu.update(drawpos)
            self.drawChildren()

            #if down and lastclickpos != self.mpos:
            #    rect(self.screen, finalColor('#FFFFFF'), (lastclickpos[0], lastclickpos[1], self.mpos[0] - lastclickpos[0], self.mpos[1] - lastclickpos[1]), 1)

            pygame.display.update()

            currenttime = pygame.time.get_ticks()
            frames += 1
