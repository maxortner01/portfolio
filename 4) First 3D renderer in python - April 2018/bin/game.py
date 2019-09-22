import pygame, os
from object import Cube, Point, Crosshair, Projectile
from camera import Camera
from random import randint

class Game:
    def __init__(self, dem, fullscreen=True):
        if fullscreen:
            os.environ['SDL_VIDEO_WINDOW_POS'] = "%d,%d" % (0, 0)

        self.width  = dem[0]
        self.height = dem[1]

        pygame.init()
        self.screen = pygame.display.set_mode(dem)

        pygame.event.get(); pygame.mouse.get_rel()
        pygame.mouse.set_visible(0); pygame.event.set_grab(1)

    def loop(self):
        #cube   = Cube()
        camera = Camera()
        cross  = Crosshair()

        amt = 1000
        stars  = [Point(randint(-500, 500), randint(-500, 500), randint(-500, 500)) for x in range(amt)]
        projs  = []

        #play   = Point(1, 1, 1)

        left  = False
        right = False
        up    = False
        down  = False
        space = False
        ctrl  = False
        shift = False

        running = True
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                if event.type == pygame.MOUSEBUTTONDOWN:
                    projs.append(Projectile(camera.get_loc(), 0))

                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_w:
                        up = True

                    if event.key == pygame.K_s:
                        down = True

                    if event.key == pygame.K_a:
                        left = True

                    if event.key == pygame.K_d:
                        right = True

                    if event.key == pygame.K_SPACE:
                        space = True

                    if event.key == pygame.K_LCTRL:
                        ctrl = True

                    if event.key == pygame.K_ESCAPE:
                        running = False

                    if event.key == pygame.K_LSHIFT:
                        shift = True

                elif event.type == pygame.KEYUP:
                    if event.key == pygame.K_w:
                        up = False

                    if event.key == pygame.K_s:
                        down = False

                    if event.key == pygame.K_a:
                        left = False

                    if event.key == pygame.K_d:
                        right = False

                    if event.key == pygame.K_SPACE:
                        space = False

                    if event.key == pygame.K_LCTRL:
                        ctrl = False

                    if event.key == pygame.K_LSHIFT:
                        shift = False

                elif event.type == pygame.MOUSEMOTION:
                    camera.xrot += event.rel[0]
                    camera.yrot += event.rel[1]


            if up:
                camera.forward()
            elif down:
                camera.backward()

            if left:
                camera.left()
            elif right:
                camera.right()

            if space:
                camera.y += camera.speed
            elif ctrl:
                camera.y -= camera.speed

            if shift:
                camera.sprint_on()
            else:
                camera.sprint_off()

            self.screen.fill((0, 0, 0))

            #cube.render(self.screen, camera)
            #play.render(self.screen, camera)

            for star in stars:
                star.render(self.screen, camera)

            for proj in projs:
                proj.render(self.screen, camera)

            cross.render(self.screen)

            pygame.display.update()
