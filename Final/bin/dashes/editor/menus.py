import pygame, sys, os
from pygame.draw import circle, rect
from matplotlib.colors import hex2color
from pygame.font import Font as f

def finalColor(h):
    y = []
    h = hex2color(h)
    for x in h:
        y.append(int(x * 255))

    return (y[0], y[1], y[2])

def color2hex(h):
    return '#%02x%02x%02x' % h

def clamp(val, minimum=0, maximum=255):
    if val < minimum:
        return minimum
    if val > maximum:
        return maximum
    return val

def colorscale(hexstr, scalefactor):
    hexstr = hexstr.strip('#')

    if scalefactor < 0 or len(hexstr) != 6:
        return hexstr

    r, g, b = int(hexstr[:2], 16), int(hexstr[2:4], 16), int(hexstr[4:], 16)

    r = clamp(r * scalefactor)
    g = clamp(g * scalefactor)
    b = clamp(b * scalefactor)

    return finalColor("#%02x%02x%02x" % (r, g, b))

directory = ""

def Font(name, size):
    fonts = []
    for fl in os.listdir(directory + 'bin/fonts'):
        if "." in fl:
            fonts.append(directory + 'bin/fonts/' + fl)
        else:
            for b in os.listdir(directory + 'bin/fonts/' + fl):
                fonts.append(directory + 'bin/fonts/' + fl + "/" + b)

    index = 0
    for x in fonts:
        n = "".join("".join(x.split('/')[len(x.split('/')) - 1:]).split('.')[:1])
        if name.lower() == n.lower():
            return f(fonts[index], size)

        index += 1


    raise ValueError('Font not recognized "' + name + '"')

def inside(box, mousepos):
    if mousepos[0] >= box[0] and mousepos[0] <= (box[0] + box[2]) and mousepos[1] >= box[1] and mousepos[1] <= (box[1] + box[3]):
        return True

class Gauge(object):
    def __init__(self, radius, center, t='RPM'):
        self.radius = radius
        self.center = center
        self.guide  = False
        self.width  = 2
        self.type   = t

class Button(object):
    def __init__(self, surface, (x, y), (width, height), color, text='', *argv):
        self.x = x
        self.y = y

        self.width  = width
        self.height = height

        self.text    = text
        self.surface = surface
        self.color   = color

        if len(argv) == 0:
            self.command = self.no
        else:
            self.command = argv[0]

    def no(self):
        print "no button"

    def click(self):
        return self.command()

    def draw(self):
        size = Font('Laconic_Bold', 16).size(self.text)
        tco  = ((self.width / 2) - (size[0] / 2), (self.height / 2) - (size[1] / 2))

        rect(self.surface, self.color, (self.x, self.y, self.width, self.height), 1)
        self.surface.blit(Font('Laconic_Bold', 16).render(self.text, True, self.color), tco)

class Menu(object):
    visible = False
    pos = (0, 0)
    lengthHeight = (0, 0)

    def __init__(self, surface, d, dem, colors):
        sys.path.insert(0, d + "bin/dashes/")
        directory = d

        buttons = ['gauge']
        self.colors = colors
        self.button_loc = {'circle': [0, 0, int(dem['x'] / 10), int(dem['y'] / 20)]}
        self.buttons = {}
        #print d

        from dir.pydraw import draw as d
        self.surface = surface
        self.d = d(surface)
        self.render(dem)

    def gaugeclick(self):
        return Gauge(50, (0, 0))

    def register(self, pos, button='left'):
        for button in self.button_loc:
            if inside(self.button_loc[button], pos):
                return self.buttons[button].click()

        print button + " at pos " + str(pos)

    def render(self, dem):
        colors = self.colors

        bg = colorscale(color2hex(colors['black']), .8)

        x = int(dem['x'] / 10)
        y = int(dem['y'] / 10)

        buttonh = int(dem['y'] / 20)
        self.mscreen = pygame.Surface((x, y))
        self.mscreen.fill(bg)
        rect(self.mscreen, colors['white'], (0, 0, (dem['x'] / 10), (dem['y'] / 10)), 1)

        circle = Button(self.mscreen, (0, 0), (x, int(dem['y'] / 20)), colors['white'], "Gauge", self.gaugeclick)
        circle.draw()
        self.buttons['circle'] = circle

        self.lengthHeight = (x, y)

    def update(self, center):
        if self.visible:
            self.pos = center
            self.surface.blit(self.mscreen, center)
