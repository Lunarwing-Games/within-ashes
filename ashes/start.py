import pygame, time, sys
from .systems import player

TITLE = "Within Ashes"
WINDOW = (800, 600)
FPS = 60

def main():
    pygame.init()
    screen = pygame.display.set_mode(WINDOW)
    pygame.display.set_caption(TITLE)
    clock = pygame.time.Clock()
    active = True

    while active:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                active = False

        # Updating world logic

        # Blanking and rendering
        screen.fill("black")

        pygame.display.flip()
        dt = clock.tick(FPS) / 1000
        

    # Exiting the loop and cleaning things up automagically
    pygame.quit()
    sys.exit(0)