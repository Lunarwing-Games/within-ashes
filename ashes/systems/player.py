import pygame

class Player:
    def __init__(self):
        self.position = pygame.Vector2(0.0, 0.0)
        self.velocity = pygame.Vector2(0.0, 0.0)

    def update(self, dt): ...

    def draw(self): ...