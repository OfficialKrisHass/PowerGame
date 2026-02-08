#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>

#include "UserWidgetBase.generated.h"

UCLASS(Abstract)
class POWERGAME_API UUserWidgetBase : public UUserWidget {

	GENERATED_BODY()

public:
#ifdef WITH_EDITOR
	inline virtual const FText GetPaletteCategory() override { return NSLOCTEXT("UMG", "PaletteCategory", "Power Game"); }
#endif
	

};