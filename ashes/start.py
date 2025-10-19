import pygame
import time
import sys
import threading

from .systems import player, npc_manager
from .systems.steam import *

TITLE = "Within Ashes"
WINDOW = (800, 600)
FPS = 60

def steam_callback_thread(steamapi, stop_event):
    """Background thread to pump SteamAPI Callbacks"""
    while not stop_event.is_set():
        try:
            steamapi.steamlib.psteam_callbacks()
        except Exception as ex:
            print(f"[pysteam] Callback error: {ex}")

    time.sleep(0.33)

def main():
    pygame.init()
    screen = pygame.display.set_mode(WINDOW)
    pygame.display.set_caption(TITLE)
    clock = pygame.time.Clock()
    active = True
    dt = 0.0

    # Player + NPC inits
    plr = player.Player()
    npc_man = npc_manager.NPCManager()

    # Steamworks
    steamapi = SteamInterface()

    # Preparing SteamCallback thread
    stop_event = threading.Event()
    callback_thread = threading.Thread(
        target=steam_callback_thread, args=(steamapi, stop_event), daemon=True
    )
    callback_thread.start()

    try:
        while active:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    active = False

            # World logical update
            plr.update(dt)
            npc_man.update(dt)

            # Rendering output
            screen.fill("black")

            pygame.display.flip()
            dt = clock.tick(FPS) / 1000

    finally:
        stop_event.set()
        callback_thread.join(timeout=1)
        steamapi.shutdown()
        pygame.quit()
        sys.exit(0)
