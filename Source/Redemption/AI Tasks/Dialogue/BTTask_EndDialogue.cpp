// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_EndDialogue.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "..\UI\HUD\Dialogue\DialogueBox.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "..\Characters\Player\PlayerCharacter.h"

UBTTask_EndDialogue::UBTTask_EndDialogue(const FObjectInitializer& ObjectInitializer)
{
	bCreateNodeInstance = true;
	NodeName = "End Dialogue";
}

EBTNodeResult::Type UBTTask_EndDialogue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(MyBlackboard) || !IsValid(PlayerController))
		return EBTNodeResult::Failed;

	UDialogueBox* DialogueBoxWidget = Cast<UDialogueBox>(MyBlackboard->GetValueAsObject(DialogueBoxWidgetKeySelector.SelectedKeyName));

	if (!IsValid(DialogueBoxWidget))
		return EBTNodeResult::Failed;

	UUIManagerWorldSubsystem* const UIManagerWorldSubsystem = GetWorld()->GetSubsystem<UUIManagerWorldSubsystem>();
	APlayerCharacter* PlayerCharacter = nullptr;
	if (GetWorld())
		PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetCharacter());
	if (!IsValid(PlayerCharacter) || !IsValid(UIManagerWorldSubsystem))
		return EBTNodeResult::Failed;

	DialogueBoxWidget->RemoveFromParent();

	PlayerCharacter->IsInDialogue = false;

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);

	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>("IsInDialogue", false);
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>("FirstDialoguePassed", false);

	PlayerController->bShowMouseCursor = false;
	PlayerCharacter->EnableInput(PlayerController);
	//PlayerController->ActivateTouchInterface(PlayerCharacter->GetStandardTouchInterface());

	UIManagerWorldSubsystem->DialogueBoxWidget->GetResponseVerticalBox()->ClearChildren();

	UIManagerWorldSubsystem->DialogueBoxWidget->ConditionalBeginDestroy();
	UIManagerWorldSubsystem->DialogueBoxWidget = nullptr;

	return EBTNodeResult::Succeeded;
}