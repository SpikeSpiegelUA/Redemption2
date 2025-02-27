// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\Dynamics\World\Items\GameItemWithElements.h"
#include "RestorationItem.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemRestorationType :uint8
{
	HEALTH UMETA(DisplayName = "Health"),
	MANA UMETA(DisplayName = "Mana"),
};

UCLASS()
class REDEMPTION_API ARestorationItem : public AGameItemWithElements
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General Information", meta = (AllowPrivateAccess = true))
		EItemRestorationType TypeOfRestoration {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General Information", meta = (AllowPrivateAccess = true))
		int RestorationValuePercent{};

public:
	EItemRestorationType GetTypeOfRestoration() const;
	int GetRestorationValuePercent() const;
};
