// dllmain.cpp : Defines the entry point for the DLL application.
#include "Common.h"

const double PI = 3.14159265358;



uint32_t WINAPI Main(HMODULE h_module)
{

    //Create the console window
    AllocConsole();
    freopen_s((FILE**)stdout, "conout$", "w", stdout);
    freopen_s((FILE**)stdin, "conin$", "r", stdin);

    printf("[INFO] Game Addresses\n");
    printf("\tGame         0x%I64x\n", Game::IGame::GetInstance());


    if (Hooks::Init())
    {

        while (!HIBYTE(GetAsyncKeyState(VK_END)))
        {

        }

        Hooks::Unhook();

    }

    printf("[INFO] Uninjecting\n");

    //Detach the console from window
    FreeConsole();
    //Exit code 0 meaning it was successful
    FreeLibraryAndExitThread(h_module, 0);

}

BOOL APIENTRY DllMain(HMODULE h_module, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(Main), h_module, 0, nullptr);
    }

    return TRUE;
}