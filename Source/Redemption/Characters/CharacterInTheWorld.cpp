// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterInTheWorld.h"
#include "Kismet/GameplayStatics.h"
#include "..\Characters\NonCombat\NonCombatEnemyNPC.h"
#include "Engine/TargetPoint.h"
#include "Redemption/Miscellaneous/RedemptionGameModeBase.h"
#include "Redemption/Dynamics/Miscellaneous/QuestAndItsStage.h"
#include "Redemption/Dynamics/Gameplay/Managers/QuestManager.h"

// Sets default values
ACharacterInTheWorld::ACharacterInTheWorld()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacterInTheWorld::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacterInTheWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterInTheWorld::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FName ACharacterInTheWorld::GetCharacterName() const
{
	return CharacterName;
}

UBehaviorTree* ACharacterInTheWorld::GetTreeAsset() const
{
	return TreeAsset;
}

ASmartObject* ACharacterInTheWorld::GetSmartObject() const
{
	return SmartObject;
}

void ACharacterInTheWorld::SetSmartObject(const ASmartObject* const Object)
{
	SmartObject = const_cast<ASmartObject*>(Object);
}

