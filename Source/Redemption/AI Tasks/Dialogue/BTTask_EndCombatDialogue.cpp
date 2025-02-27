// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_EndCombatDialogue.h"
#include "..\Characters\Player\PlayerCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "Redemption/Miscellaneous/RedemptionGameModeBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_EndCombatDialogue::UBTTask_EndCombatDialogue(const FObjectInitializer& ObjectInitializer)
{
	bCreateNodeInstance = true;
	NodeName = "End the combat dialogue";
}

EBTNodeResult::Type UBTTask_EndCombatDialogue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto* UIManagerWorldSubsystem = GetWorld()->GetSubsystem<UUIManagerWorldSubsystem>();
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (!IsValid(PlayerCharacter))
		return EBTNodeResult::Failed;

	UIManagerWorldSubsystem->BattleMenuWidget->GetMenuBorder()->SetVisibility(ESlateVisibility::Hidden);
	UIManagerWorldSubsystem->BattleMenuWidget->IsPreparingToTalk = false;
	UIManagerWorldSubsystem->DialogueBoxWidget->RemoveFromParent();
	UIManagerWorldSubsystem->AlliesInfoBarsWidget->AddToViewport();
	PlayerCharacter->IsInDialogue = false;
	
	if (const auto* RedemptionGameModeBase = Cast<ARedemptionGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())); IsValid(RedemptionGameModeBase)) {
		RedemptionGameModeBase->GetAudioManager()->DungeonCombatBackgroundMusicAudioComponents[RedemptionGameModeBase->GetAudioManager()->IndexInArrayOfCurrentPlayingBGMusic]->SetPaused(false);
		RedemptionGameModeBase->GetAudioManager()->GetDungeonTalkBackgroundMusicAudioComponent_Daat()->SetPaused(true);
	}

	UIManagerWorldSubsystem->DialogueBoxWidget->GetResponseVerticalBox()->ClearChildren();

	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>("FirstDialoguePassed", false);
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>("IsInDialogue", false);

	UIManagerWorldSubsystem->DialogueBoxWidget->ConditionalBeginDestroy();
	UIManagerWorldSubsystem->DialogueBoxWidget = nullptr;

	if(APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()); IsValid(PlayerController))
		PlayerCharacter->EnableInput(PlayerController);

	return EBTNodeResult::Succeeded;
}
