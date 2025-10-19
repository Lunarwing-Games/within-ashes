#ifndef PYSTEAM_H
#define PYSTEAM_H

#ifdef __cplusplus
extern "C" {
#endif

// The docs specify a uint32 AppID
#define SteamAppID (uint32_t)480

// Defining the PySteam API macro for visibility
#if defined(_WIN32) || defined(_WIN64)
  #define PS_API __declspec(dllexport)
#else
  #define PS_API __attribute__((visibility("default")))
#endif

// Required includes from the stdlib and Steamworks
#include <stdbool.h>
#include <stdint.h>
#include <steam/steam_api.h>

// Initalizes Steam and returns a boolean value for success or failure
PS_API bool psteam_init(void);

// Shutdowns Steam backend for the game and frees used memory
PS_API void psteam_shutdown(void);

// Returns a boolean if Steamworks is ready or not
PS_API bool psteam_is_ready(void);

// Returns the current users SteamPersona
// Refer to; https://partner.steamgames.com/doc/api/ISteamFriends
PS_API const char *psteam_get_persona(void);

// Grants the user an achievement based on ach_id if they do not have it unlocked
PS_API bool psteam_grant_ach(const char *ach_id);

// Returns a boolean value if the provided ach_id is unlocked
PS_API bool psteam_is_ach_unlocked(const char *ach_id);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // pysteam.h
