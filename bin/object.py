from pygame.draw import line, circle
#from pygame.gfxdraw import circle
import math

def rotate2d(pos, rad): x,y=pos; s,c = math.sin(rad), math.cos(rad); return x*c-y*s, y*c+x*s

def distance(loc1, loc2):
    locations_1 = [loc1[x] for x in range(len(loc1))]
    locations_2 = [loc2[x] for x in range(len(loc2))]
    locations   = [loc1[x] - loc2[x] for x in range(len(loc1))]

    return math.sqrt(sum([l**2 for l in locations]))

def Convert(p, camera, width, height):
    #Apply camera transform info to cube
    x = p[0] + camera.x; y = p[1] + camera.y; z = (p[2] + 1.0) + camera.z

    xrot = camera.get_xrot()
    yrot = camera.get_yrot()

    x, z = rotate2d((x, z), xrot)
    y, z = rotate2d((y, z), yrot)

    #if point is behind camera
    if z <= 0:
        return None, None, None, None

    #Apply z-axis to x and y
    x = x / z;           y = y / z

    #Convert -1 -> 1 coordinates to pixel location
    x = (x * (width  / 2))  + (width  / 2)
    y = (y * (height / 2))  + (height / 2)

    r_max = 100
    r = int(r_max / z)
    if r > r_max: r = r_max

    return int(x), int(y), z, r

class Crosshair:
    def render(self, screen):
        width  = screen.get_width()
        height = screen.get_height()

        #(w)idth and (h)eight of crosshair
        w      = width  / 1000.0
        h      = height / 1000.0

        x1     = (width  / 2) - (w / 2)
        y1     = (height / 2)

        x2     = (width  / 2) + (w / 2)
        y2     = y1

        line(screen, (255, 255, 255), (x1, y1), (x2, y2))

class Point:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def render(self, screen, camera):
        width  = screen.get_width()
        height = screen.get_height()

        x, y, z, r = Convert((self.x, self.y, self.z), camera, width, height)
        try:
            color = int(80000.0 / z)
            if color > 255: color = 255
            #circle(screen, x, y, r, (color, color, color))
            circle(screen, (color, color, color), (x, y), r)
        except:
            return

class Projectile:
    def __init__(self, loc, heading, speed=1):
        self.loc     = list(loc)
        self.heading = heading
        self.speed   = speed

    def render(self, screen, camera):
        width  = screen.get_width()
        height = screen.get_height()

        self.loc[0] += self.speed

        x, y, z, r = Convert(self.loc, camera, width, height)

        try:
            circle(screen, (255, 255, 255), (x, y), r)
        except:
            return

class Cube:
    points  = (-.5, .5, 1.0), (-.5, -.5, 1.0), (.5, -.5, 1.0), (.5, .5, 1.0)
    points += (-.5, .5, 2.0), (-.5, -.5, 2.0), (.5, -.5, 2.0), (.5, .5, 2.0)

    lines   = [((-.5, .5, 1.0), (-.5, -.5, 1.0)), ((-.5, -.5, 1.0), (.5, -.5, 1.0)),
               ((.5, -.5, 1.0), (.5, .5, 1.0)), ((.5, .5, 1.0), (.5, .5, 2.0)),
               ]

    def render(self, screen, camera):
        width  = screen.get_width()
        height = screen.get_height()

        for count, p in enumerate(self.points):
            x, y, z, r = Convert(p, camera, width, height)

            #Draw circles to screen
            try:
                circle(screen, (255, 255, 255), (x, y), r)
            except:
                continue

        for l in self.lines:
            x1, y1, z, r = Convert(l[0], camera, width, height)
            x2, y2, z, r = Convert(l[1], camera, width, height)

            try:
                line(screen, (255, 255, 255), (x1, y1), (x2, y2))
            except:
                continue
