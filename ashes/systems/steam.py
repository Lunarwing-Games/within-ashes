# This is the actual interface between Steamworks and the game.
# Since we want to keep Steam from dying due to this code, types are
# semi-enforced, keeping them inline with C

import ctypes
import sys, os

class SteamInterface:
    def __init__(self):
        self.__cwd = os.path.dirname(os.path.abspath(sys.argv[0]))
        if sys.platform == "win32":
            self.steamlib = ctypes.cdll.LoadLibrary(f"{self.__cwd}/pysteam.dll")
        elif sys.platform == "darwin":
            self.steamlib = ctypes.cdll.LoadLibrary(f"{self.__cwd}/libpysteam.dylib")
        else:
            self.steamlib = ctypes.cdll.LoadLibrary(f"{self.__cwd}/ibpysteam.so")
        
        self.steamlib.psteam_init()
    
    def is_ready(self) -> bool:
        return bool(self.steamlib.psteam_is_ready())
    
    def shutdown(self):
        self.steamlib.psteam_shutdown()
        return

    def get_achievement(self, ach_id: str):
        self.steamlib.psteam_grant_ach(ach_id.encode())
        return
    
    def set_stat(self, stat_id: str, value: int):
        return NotImplemented
    
    def get_stat(self, stat_id: str):
        return NotImplemented