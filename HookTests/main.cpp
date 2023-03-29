#include <windows.h>
#include <cstdio>

int main()
{
    auto module = LoadLibraryW(L"HookLib.dll");
    if (!module) {
        printf("ERROR: LoadLibrary failed\n", module);
        return -1;
    }

    auto proc = reinterpret_cast<HOOKPROC>(GetProcAddress(module, "GetMsgProc"));
    if (!proc) {
        printf("ERROR: GetProcAddress failed\n", module);
        return -1;
    }

    auto hook = SetWindowsHookExW(WH_GETMESSAGE, proc, module, 0);
    if (!hook) {
        printf("ERROR: SetWindowsHookEx failed\n");
        return -1;
    }

    printf("SUCCESS: The hook is installed.\n");
    printf("Press ENTER to uninstall the hook.\n");
    getchar();

    if (!UnhookWindowsHookEx(hook)) {
        printf("ERROR: UnhookWindowsHookEx failed\n");
        return -1;
    }

    printf("SUCCESS: The hook is uninstalled.\n");
    printf("Press ENTER to close this program.\n");
    getchar();

    return 0;
}
