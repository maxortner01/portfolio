import math

class Camera:
    x = 0; y = 0; z = 0
    xrot = 0; yrot = 0;
    speed = .0005; distance = 75

    def get_xrot(self):
        return self.xrot / 250.0

    def sprint_on(self):
        #self.speed = .001
        self.speed  = 1

    def sprint_off(self):
        #self.speed = .0005
        self.speed = .1

    def get_yrot(self):
        return self.yrot / 250.0

    def get_loc(self):
        return (self.x, self.y, self.z)

    def forward(self):
        loc = list(self.get_loc())
        loc[0] = self.speed * -math.sin(self.get_xrot()) + loc[0]
        loc[2] = self.speed * -math.cos(self.get_xrot()) + loc[2]

        self.x = loc[0]; self.y = loc[1]; self.z = loc[2]

    def backward(self):
        loc = list(self.get_loc())
        loc[0] = self.speed * math.sin(self.get_xrot()) + loc[0]
        loc[2] = self.speed * math.cos(self.get_xrot()) + loc[2]

        self.x = loc[0]; self.y = loc[1]; self.z = loc[2]

    def left(self):
        loc = list(self.get_loc())
        loc[0] = self.speed * -math.sin(self.get_xrot() - (math.pi / 2.0)) + loc[0]
        loc[2] = self.speed * -math.cos(self.get_xrot() - (math.pi / 2.0)) + loc[2]

        self.x = loc[0]; self.y = loc[1]; self.z = loc[2]

    def right(self):
        loc = list(self.get_loc())
        loc[0] = self.speed * -math.sin(self.get_xrot() + (math.pi / 2.0)) + loc[0]
        loc[2] = self.speed * -math.cos(self.get_xrot() + (math.pi / 2.0)) + loc[2]

        self.x = loc[0]; self.y = loc[1]; self.z = loc[2]
