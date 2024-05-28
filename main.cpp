#include "src/hooks.h"

#include <minhook.h>
#include <windows.h>
#include <iostream>

#define CONSOLE

void __stdcall dll_entry(HMODULE module) {
    MH_Initialize();
    MH_CreateHookApi(L"ws2_32.dll", "connect", (void*)hooks::connect_detour, (void**)(&hooks::connect_og));
    MH_CreateHookApi(L"ws2_32.dll", "recv", (void*)hooks::recv_hook, (void**)(&hooks::recv_og));
    MH_CreateHookApi(L"ws2_32.dll", "send", (void*)hooks::send_hook, (void**)(&hooks::send_og));
    MH_CreateHookApi(L"ws2_32.dll", "GetAddrInfoW", (void*)hooks::GetAddrInfoW_detour, (void**)(&hooks::GetAddrInfoW_og));
    MH_EnableHook(MH_ALL_HOOKS);
}

[[maybe_unused]] BOOL WINAPI DllMain(void* module, const unsigned long reason, void*) {
    if (reason != DLL_PROCESS_ATTACH) return 0;

#ifdef CONSOLE
    AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
#endif

    CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(dll_entry), module, 0, nullptr);
    return 1;
}