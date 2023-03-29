#include <windows.h>

#include <array>
#include <string>

// Declare a "do-nothing" hook.
extern "C" __declspec(dllexport)
LRESULT CALLBACK GetMsgProc(int code, WPARAM wparam, LPARAM lparam)
{
    return CallNextHookEx(NULL, code, wparam, lparam);
}

// Only inject into the processes listed below.
std::array<std::wstring, 2> processesToHook{
    L"HookTests.exe",
    L"firefox.exe",
};

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        wchar_t filepath[MAX_PATH]{};
        GetModuleFileNameW(nullptr, &filepath[0], MAX_PATH);
        std::wstring filepathString(filepath);
        auto filename = filepathString.substr(filepathString.find_last_of(L'\\') + 1);
        for (const auto& processToHook: processesToHook) {
            if (filename == processToHook) {
                return TRUE;
            }
        }
        return FALSE;
        break;
    }
    default:
        break;
    }
    return TRUE;
}

