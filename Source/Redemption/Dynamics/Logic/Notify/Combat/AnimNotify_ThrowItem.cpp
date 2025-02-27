// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ThrowItem.h"
#include "..\Characters\Animation\Combat\CombatAlliesAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Redemption/Miscellaneous/RedemptionGameModeBase.h"

void UAnimNotify_ThrowItem::SpawnItemObject(const AGameItemWithItemObject* const& GameItemWithItemObject, const USkeletalMeshComponent* const& MeshComp, const ACombatNPC* const& CombatNPC)
{
	FTransform SpawnTransform = MeshComp->GetSocketTransform(FName(TEXT("RightHandIndex3")), ERelativeTransformSpace::RTS_World);
	FActorSpawnParameters ActorSpawnParemeters;
	AItemObject* SpawnedItemObject = MeshComp->GetWorld()->SpawnActor<AItemObject>(GameItemWithItemObject->GetItemObjectClass(), SpawnTransform, ActorSpawnParemeters);
	SpawnedItemObject->SetItem(const_cast<AGameItemWithItemObject*>(GameItemWithItemObject));
	SpawnedItemObject->SetNPCOwner(CombatNPC);
	SpawnedItemObject->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(SpawnedItemObject->GetActorLocation(), CombatNPC->Target->GetActorLocation()));
	if (IsValid(Cast<ACombatAllies>(MeshComp->GetOwner())))
		SpawnedItemObject->SetTargetBattleSide(EBattleSide::ENEMIES);
	else if (IsValid(Cast<ACombatEnemyNPC>(MeshComp->GetOwner())))
		SpawnedItemObject->SetTargetBattleSide(EBattleSide::ALLIES);
}

void UAnimNotify_ThrowItem::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	//Spawn Spell Object and rotate it towards the selected enemy
	if (IsValid(MeshComp->GetWorld()) && IsValid(MeshComp->GetWorld()->GetFirstPlayerController()))
		if (ACombatNPC* CombatNPC = Cast<ACombatNPC>(MeshComp->GetOwner()); IsValid(CombatNPC))
			if (auto* UIManagerWorldSubsystem = MeshComp->GetWorld()->GetSubsystem<UUIManagerWorldSubsystem>(); IsValid(UIManagerWorldSubsystem))
				if (const auto* const RedemptionGameModeBase = Cast<ARedemptionGameModeBase>(UGameplayStatics::GetGameMode(MeshComp->GetWorld())); IsValid(RedemptionGameModeBase))
					if (AGameItemWithItemObject* GameItemWithItemObject = Cast<AGameItemWithItemObject>(UIManagerWorldSubsystem->InventoryMenuWidget->GetPickedItem()); IsValid(GameItemWithItemObject)) {
						SpawnItemObject(GameItemWithItemObject, MeshComp, CombatNPC);
						UGameplayStatics::PlaySound2D(MeshComp->GetWorld(), RedemptionGameModeBase->GetAudioManager()->GetUseAssaultSoundCue());
					}
}