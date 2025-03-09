#pragma once
#include "CoreMinimal.h"
#include "ShooterInterface.generated.h"

UINTERFACE()
class UShooterInterface : public UInterface
{
	GENERATED_BODY()
};


class IShooterInterface
{
	GENERATED_BODY()
public:
	virtual void Zoom(UINT8 bZoom) = 0;
	virtual void Fire() = 0;
};