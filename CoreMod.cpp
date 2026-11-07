#include <string>
#include <list>
#include <AlgaeSDK.h>

Sexy::DialogButton* modMenuButton = nullptr;

static void __cdecl OnMainScreenLoad(Sexy::MainScreen* self, Sexy::WidgetManager* widgetManager)
{
    Sexy::Image* mainBtnImage = Algae::ReadGlobal<Sexy::Image*>(Sexy::IMAGE_MAINBUTTON);

    modMenuButton = Sexy::GameUtil::MakeDialogButton(3, self, "Mods", mainBtnImage);
    modMenuButton->Resize(541, 380, 80, Algae::ReadVar<int>(modMenuButton, Sexy::Addr::WidgetContainer_mHeight));

    Algae_Log("WIDGET ADDED: %p", modMenuButton);

    widgetManager->AddWidget(modMenuButton);
}

static void __cdecl OnMainScreenClose(Sexy::MainScreen* self, Sexy::WidgetManager* widgetManager)
{
    widgetManager->RemoveWidget(modMenuButton);
    delete modMenuButton;
}

static void __cdecl OnMainScreenReorder(Sexy::MainScreen* self)
{
    Sexy::WidgetManager* widgetManager = Algae::ReadVar<Sexy::WidgetManager*>(self, Sexy::Addr::WidgetContainer_mWidgetManager);
    Algae_Log("WidgetManager: %p", widgetManager);
    widgetManager->PutInfront(modMenuButton, self);
    // TODO hook crashes here? Need to figure out why
}

extern "C" __declspec(dllexport) void ModInit(const ModHost* host)
{
    while (!IsDebuggerPresent()) {
        Sleep(100);
    }
    Algae_AddPostHook(Sexy::Addr::MainScreen_AddedToManager, OnMainScreenLoad);
    Algae_AddPostHook(Sexy::Addr::MainScreen_RemovedFromManager, OnMainScreenClose);
    Algae_AddPostHook(Sexy::Addr::MainScreen_OrderInManagerChanged, OnMainScreenReorder);
    Algae_Log("Algae Core initialized!");
}
