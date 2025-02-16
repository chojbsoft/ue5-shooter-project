#pragma once
#include "CoreMinimal.h"
#include "TankInterface.generated.h"

UINTERFACE()
class UTankInterface : public UInterface
{
	GENERATED_BODY()
};


class ITankInterface
{
	GENERATED_BODY()
public:
	virtual void Zoom(UINT8 bZoom) = 0;
	virtual void Fire() = 0;
};