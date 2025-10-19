from hostile_npc import *
from passive_npc import *
import pygame

# The NPC Manager does exactly that, manages all the NPCs from a central class.
# This class can be a bit complex overall but it's better than manually
# managing each NPC on their own (that would be terrible!)

class NPCManager:
    def __init__(self): ...

    def update(self, dt): ...