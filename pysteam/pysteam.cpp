#include "pysteam.hpp"
#include <stdio.h>
#include <steam/steam_api.h>

static bool g_SteamReady = false;

PS_API bool psteam_init(void) {
    if (SteamAPI_RestartAppIfNecessary(SteamAppID)) {
        fprintf(stderr, "[pysteam] Steam restart is required!\n");
        return false;
    }

    if (!SteamAPI_Init()) {
        fprintf(stderr, "[pysteam] SteamAPI_Init failed!\n");
        g_SteamReady = false;
        return false;
    }

    g_SteamReady = true;
    fprintf(stdout, "[pysteam] SteamAPI_Init success!\n");
    return true;
}

PS_API void psteam_shutdown(void) {
    if (g_SteamReady) {
        SteamAPI_Shutdown();
        g_SteamReady = false;
        fprintf(stdout, "[PySteam] SteamAPI shutdown completed.\n");
    }
}

PS_API bool psteam_is_ready(void) {
    return g_SteamReady && SteamAPI_IsSteamRunning();
}

PS_API const char *psteam_get_persona(void) {
    if (!psteam_is_ready()) return "Unknown";
    return SteamFriends()->GetPersonaName();
}

PS_API bool psteam_grant_ach(const char *ach_id) {
    if (!psteam_is_ready() || !ach_id) return false;
    bool achieved = false;
    
    if (!SteamUserStats()->GetAchievement(ach_id, &achieved)) {
        fprintf(stderr, "[pysteam] Failed to query achievement: %s\n", ach_id);
        return false;
    }

    if (!achieved) {
        SteamUserStats()->SetAchievement(ach_id);
        SteamUserStats()->StoreStats();
        fprintf(stdout, "[pysteam] Unlocked achievement: %s\n", ach_id);
    } else {
        fprintf(stdout, "Already unlocked %s\n", ach_id);
    }

    return true;
}

PS_API bool psteam_is_ach_unlocked(const char *ach_id) {
    if (!psteam_is_ready() || !ach_id) return false;

    bool achieved = false;
    if (!SteamUserStats()->GetAchievement(ach_id, &achieved)) {
        fprintf(stderr, "[PySteam] Failed to query achievement: %s\n", ach_id);
        return false;
    }

    return achieved;
}
