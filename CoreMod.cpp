#include <string>
#include <list>
#include <AlgaeSDK.h>

Sexy::DialogButton* modMenuButton = nullptr;

static void __cdecl OnMainScreenLoad(Sexy::MainScreen* self, Sexy::WidgetManager* widgetManager)
{
    Sexy::Image* mainBtnImage = Algae::ReadGlobal<Sexy::Image*>(Sexy::IMAGE_MAINBUTTON);
    modMenuButton = Sexy::GameUtil::MakeDialogButton(10, self->AsButtonListener(), "Mods", mainBtnImage);
    modMenuButton->Resize(533, 380, 69, Algae::ReadVar<int>(modMenuButton, Sexy::Addr::WidgetContainer_mHeight));

    widgetManager->AddWidget(modMenuButton);
}

static void __cdecl OnMainScreenClose(Sexy::MainScreen* self, Sexy::WidgetManager* widgetManager)
{
    Sexy::GameUtil::SafeRemoveWidget(modMenuButton);
}

static void __cdecl OnMainScreenReorder(Sexy::MainScreen* self)
{
    Sexy::WidgetManager* widgetManager = Algae::ReadVar<Sexy::WidgetManager*>(self, Sexy::Addr::WidgetContainer_mWidgetManager);
    widgetManager->PutInFront(modMenuButton, self);
}

extern "C" __declspec(dllexport) void ModInit(const ModHost* host)
{
    Algae_AddPostHook(Sexy::Addr::MainScreen_AddedToManager, OnMainScreenLoad);
    Algae_AddPostHook(Sexy::Addr::MainScreen_RemovedFromManager, OnMainScreenClose);
    Algae_AddPostHook(Sexy::Addr::MainScreen_OrderInManagerChanged, OnMainScreenReorder);
    Algae_Log("Algae Core initialized!");
}
