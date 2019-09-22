import pygame as p
from pygame.gfxdraw import aapolygon, filled_polygon, aacircle
from pygame.draw import line, circle, aaline
from math import sqrt as sq
from math import atan2, degrees, radians, cos, sin

class draw:
    def __init__(self, surface):
        self.surface = surface

    def getpoints(self, width, deg, startpos, endpos):
        points = []

        center = startpos

        interd = deg + 90
        xb = width / 2 * cos(radians(interd)) + center[0]
        yb = width / 2 * sin(radians(interd)) + center[1]
        points.append((xb, yb))

        interd = deg - 90
        xb = width / 2 * cos(radians(interd)) + center[0]
        yb = width / 2 * sin(radians(interd)) + center[1]
        points.append((xb, yb))

        center = endpos

        interd = deg - 90
        xb = width / 2 * cos(radians(interd)) + center[0]
        yb = width / 2 * sin(radians(interd)) + center[1]
        points.append((xb, yb))

        interd = deg + 90
        xb = width / 2 * cos(radians(interd)) + center[0]
        yb = width / 2 * sin(radians(interd)) + center[1]
        points.append((xb, yb))

        return points

    def line(self, color, startpos, endpos, width=15):
        #Slope-intercept: y = slope * (x) + yinter
        slope  = (startpos[1] - endpos[1]) / (startpos[0] - endpos[0])
        yinter = startpos[1] + (slope * startpos[0])

        a = startpos[0] - endpos[0]
        b = startpos[1] - endpos[1]

        #Length
        length = sq((abs(a) ** 2) + (abs(a) ** 2))

        #Calculate triangle degree angle from hypotenuse
        deg = degrees(atan2(b, a))

        #Center Position of line

        #intercepting degree
        points  = self.getpoints(width, deg, startpos, endpos)
        fpoints = self.getpoints(width - 1, deg, startpos, endpos)

        #circle(self.surface, color, (int(xb), int(yb)), 5, 1)

        #line(self.surface, color, startpos, (xb, yb))
        filled_polygon(self.surface, (fpoints[0], fpoints[1], fpoints[2], fpoints[3]), color)
        aapolygon(self.surface, (points[0], points[1], points[2], points[3]), color)

        print deg

    def multiline(self, color, startpos, endpos, width=2):
        a = startpos[0] - endpos[0]
        b = startpos[1] - endpos[1]
        deg = degrees(atan2(b, a))


        aaline(self.surface, color, startpos, endpos)

        for x in range(width * 2):
            points = self.getpoints(x / 2, deg, startpos, endpos)
            aaline(self.surface, color, points[1], points[2])
            aaline(self.surface, color, points[0], points[3])

    def line(self, color, starpos, endpos):
        aaline(self.surface, color, starpos, endpos)

    def circle(self, color, center, radius):
        aacircle(self.surface, center[0], center[1], radius, color)

    def multicircle(self, color, center, radius, width=2):
        aacircle(self.surface, center[0], center[1], radius, color)

        for x in range(width * 2):
            aacircle(self.surface, center[0], center[1], radius + (x / 2), color)
            aacircle(self.surface, center[0], center[1], radius - (x / 2), color)
