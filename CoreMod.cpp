#include <string>
#include <AlgaeSDK.h>

extern "C" __declspec(dllexport) void ModInit(const ModHost* host)
{
    Algae_Log("CoreMod initialized!");
}
