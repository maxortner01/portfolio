import pygame, math
from pygame.draw import line, rect
from random import randint

#(y/6)*(4-y)

RESOLUTION = 10.0
WIDTH = 1920
HEIGHT = 1080

class Particle:
    def __init__(self, location):
        self.location = list(location)
        self.magnitude = 0

    def update(self, screen):
        val = Game.getDiff(self.location[0], self.location[1])
        try:
            angle = math.tan(val)
        except:
            angle = 0

        self.magnitude = val

        self.location[0] += math.cos(angle)
        self.location[1] += math.sin(angle)

        #if   self.location[0] > screen.get_rect()[2]: self.location[0] = 0
        #elif self.location[1] > screen.get_rect()[3]: self.location[1] = 0
        #elif self.location[0] < 0: self.location[0] = screen.get_rect()[2]
        #elif self.location[1] < 0: self.location[1] = screen.get_rect()[3]

    def render(self, screen):
        self.update(screen)
        #print self.location
        #print self.magnitude
        if self.magnitude == 0: self.magnitude = 1.0
        c = 255.0 / abs(self.magnitude)
        c = -c + 255.0

        try:
            if c > 255.0: c = (255, 0, 0)
            elif c < 0:   c = (0, 0, 0)
            else: c = (int(c), int(c), int(c))
        except:
            return

        #loc = Game.transform(self.location[0], self.location[1])
        #loc[0] += screen.get_rect()[2] / 2; loc[1] += screen.get_rect()[3] / 2
        loc = self.location

        if   loc[0] > screen.get_rect()[2]: return
        elif loc[1] > screen.get_rect()[3]: return
        elif loc[0] < 0: return
        elif loc[1] < 0: return

        #if Game.transform(loc[0], loc[1])[0] < 0:
        #    return
        c = (255, 255, 255)

        rect(screen, c, (int(loc[0]), int(loc[1]), 1, 1))


class Game:
    offset = [0, 0]

    def __init__(self, dem):
        self.width  = dem[0]
        self.height = dem[1]

        pygame.init()
        Game.screen = pygame.display.set_mode(dem)
        Game.parts  = pygame.Surface(dem, pygame.SRCALPHA)
        Game.temps  = pygame.Surface(dem)


    @staticmethod
    def transform(x, y, scale=1):
        return [(scale * x) - int((WIDTH * scale) / 2), ((scale * y)* -1) + int((HEIGHT * scale) / 2)]

    @staticmethod
    def formula(x, y):
        #return (y / 6) * (4 - y)

        #y = -y; y += int(HEIGHT / 2)
        #x += int(WIDTH  / 2)

        x, y = Game.transform(x, y)

        #x *= 2; y *= 2

        #if y == 0.0: y = 1.0

        try:
            return float(x) / float(y)
            #return math.sqrt(math.pow(y / 100.0, 2) + math.pow(x / 100.0, 2))
        except:
            return 0


    @staticmethod
    def getDiff(x, y):
        return Game.formula(x, y)

    @staticmethod
    def getDist(pos1, pos2):
        return math.sqrt(math.pow(pos1[0] - pos2[0], 2) + math.pow(pos1[1] - pos2[1], 2))

    @staticmethod
    def avg(ls):
        return float(sum(ls)) / float(len(ls))

    def save(self, loc):
        pygame.image.save(Game.temps, loc)

    def genChargeField(self, particles):
        length = math.sqrt(math.pow(self.width, 2) + math.pow(self.height, 2))

        for y in range((self.height / RESOLUTION) + 1):
            for x in range((self.width / RESOLUTION) + 1):
                distances = []
                for p in particles:
                    for i in range(int(p.magnitude)):
                        distances.append( (abs(Game.getDist((x * RESOLUTION, y * RESOLUTION), p.location)) / length) )

                c = int(Game.avg(distances) * 255.0)
                if c < 0: c = 0
                elif c > 255: c = 255

                c = (c, c, c)
                rect(Game.temps, c, (x * RESOLUTION, y * RESOLUTION, RESOLUTION, RESOLUTION))

                #Game.temps.set_at((x, y), c)

            print str(y) + "/" + str(self.height / RESOLUTION + 1)

    def loop(self):
        running = True

        zoom = 1.0
        amt = 10000
        particles = [Particle((randint(0, self.width), randint(0, self.height))) for x in range(amt)]
        #self.renderTemps()
        for y in range( int(self.height / RESOLUTION) + 1 ):
            for x in range( int(self.width / RESOLUTION) + 1 ):
                val = Game.getDiff(x * RESOLUTION, y * RESOLUTION)

                #angle = math.atan(val)
                #line(Game.temps, (100, 100, 100), (x * RESOLUTION, y * RESOLUTION), (x * float(RESOLUTION) + (float(RESOLUTION) * math.cos(angle)), y * RESOLUTION + (float(RESOLUTION) * math.sin(angle))))

                #if val == 0: val = 1.0
                try:
                    c = 255.0 / abs(val)
                except:
                    rect(Game.temps, (0, 127, 65), (x * RESOLUTION, y * RESOLUTION, RESOLUTION, RESOLUTION))
                    continue

                c = -c + 255.0

                if c > 255.0: c = 255.0
                elif c < 0:   c = 0

                rect(Game.temps, (int(c) / 2, 0, int(-c + 255.0) / 2), (x * RESOLUTION, y * RESOLUTION, RESOLUTION, RESOLUTION))
                #Game.temps.fill((255, 0, 0))

        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_SPACE:
                        time = str(pygame.time.get_ticks() / 1000.0)[:5]
                        self.genChargeField(particles)
                        print "t" + time + ".png"
                        self.save("t" + time + ".png")

                    elif event.key == pygame.K_UP:
                        zoom += .1

                    elif event.key == pygame.K_DOWN:
                        zoom -= .1

                elif event.type == pygame.MOUSEMOTION:
                    if pygame.mouse.get_pressed()[1]:
                        Game.offset[0] += event.rel[0]
                        Game.offset[1] += event.rel[1]

            self.screen.fill((0, 0, 0))
            Game.parts.fill((0, 0, 0, 0))

            if pygame.mouse.get_pressed()[2]:
                p = ((pygame.mouse.get_pos()[0] - Game.offset[0]) / zoom, (pygame.mouse.get_pos()[1] + Game.offset[1]) / zoom)
                print "Pos:   " + str(Game.transform(p[0], p[1]))
                print "f':    " + str(Game.getDiff(p[0], p[1]))
                print "theta: " + str(math.degrees(math.atan(Game.getDiff(p[0], p[1])))) + "\n"

            #for y in range( int(self.height / RESOLUTION) + 1 ):
            #    for x in range( int(self.width / RESOLUTION) + 1 ):
            #        slope = math.tan(Game.getDiff(x, y))
            #        line(self.screen, (255, 255, 255),
            #            (x * RESOLUTION, y * RESOLUTION),
            #            ((x * RESOLUTION) + (1 * 5), (y * RESOLUTION) + (slope * 2))
            #        )

            for p in particles:
                p.render(Game.parts)

            Game.screen.blit(pygame.transform.scale(Game.temps, (int(self.width * zoom), int(self.height * zoom))), Game.offset)
            Game.screen.blit(pygame.transform.scale(Game.parts, (int(self.width * zoom), int(self.height * zoom))), Game.offset)

            pygame.display.update(Game.screen.get_rect())
            #pygame.time.wait(100)

if __name__ == '__main__':
    Game((WIDTH, HEIGHT)).loop()
