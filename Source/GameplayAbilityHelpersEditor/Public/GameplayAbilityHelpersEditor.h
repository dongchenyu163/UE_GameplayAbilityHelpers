#pragma once

#include "CoreMinimal.h"
#include "IAssetTypeActions.h"
#include "Modules/ModuleManager.h"

class FGameplayAbilityHelpersEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    
    /** All created asset type actions.  Cached here so that we can unregister it during shutdown. */
    TArray< TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;
};
