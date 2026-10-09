#include <windows.h>
#include <fstream>
#include <string>

std::string g_AppID64 = "";
std::string g_UserID64 = "";
const char* g_DefaultLanguage64 = "english"; // Idioma padrão fixo em inglês

void InicializarConfiguracoesx64() {
    std::ifstream fileAppID("steamappid.txt");
    if (fileAppID.is_open()) {
        std::getline(fileAppID, g_AppID64);
        fileAppID.close();
    }

    std::ifstream fileUserID("userid.txt");
    if (fileUserID.is_open()) {
        std::getline(fileUserID, g_UserID64);
        fileUserID.close();
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        InicializarConfiguracoesx64();
    }
    return TRUE;
}

extern "C" {
    bool SteamAPI_Init() {
        return true;
    }

    bool SteamAPI_IsSubscribed() {
        return true;
    }

    bool SteamAPI_IsSubscribedApp(unsigned int appID) {
        return true;
    }

    bool SteamAPI_RestartAppIfNecessary(unsigned int unOwnAppID) {
        return false;
    }

    unsigned long long SteamUser_GetSteamID() {
        try {
            if (!g_UserID64.empty()) {
                return std::stoull(g_UserID64);
            }
        }
        catch (...) {}
        return 0;
    }

    void* SteamUser() {
        static char facedeInterface64 = { 0 };
        return (void*)&facedeInterface64;
    }

    void* SteamApps() {
        static char facadeAppsInterface64 = { 0 };
        return (void*)&facadeAppsInterface64;
    }

    const char* SteamApps_GetCurrentGameLanguage() {
        return g_DefaultLanguage64;
    }

    // --- NOVA FUNÇÃO DE DLC ---
    bool SteamApps_BIsDLCInstalled(unsigned int appID) {
        return true;
    }
}
