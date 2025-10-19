import pygame

# Very mean, will take your goodies, and probably kill you

class HostileNPC:
    def __init__(self):
        self.position = pygame.Vector2(0.0, 0.0)
        self.velocity = pygame.Vector2(0.0, 0.0)
    
    def update(self, dt): ...

    def draw(self): ...