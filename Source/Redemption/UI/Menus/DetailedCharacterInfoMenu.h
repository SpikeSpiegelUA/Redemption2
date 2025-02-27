// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components\TextBlock.h"
#include "Components\Image.h"
#include "Components\Button.h"
#include "Components\Border.h"
#include "Redemption/Characters/Player/PlayerCharacter.h"
#include "DetailedCharacterInfoMenu.generated.h"


/**
 * 
 */
UCLASS()
class REDEMPTION_API UDetailedCharacterInfoMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetCharacterInfoForAlly();
	void SetCharacterInfoForPlayer(const APlayerCharacter* const Player);

	UFUNCTION()
	void BackButtonOnClicked();

	UButton* GetBackButton() const;
	UButton* GetAbilitiesButton() const;
	UButton* GetToggleInfoButton() const;
	UBorder* GetSkillsBorder() const;
	UBorder* GetStatsBorder() const;
	UBorder* GetPhysicalResistancesBorder() const;
	UBorder* GetElementalResistancesBorder() const;
	UVerticalBox* GetButtonsVerticalBox() const;

	class ACombatAllyNPC* Ally{};
protected:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UImage* CharacterPortraitImage;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UBorder* SkillsBorder{};
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UBorder* StatsBorder{};
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UBorder* PhysicalResistancesBorder{};
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UVerticalBox* ButtonsVerticalBox{};
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UBorder* ElementalResistancesBorder{};
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UButton* BackButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UButton* AbilitiesButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UButton* ToggleInfoButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* CharacterNameTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* CharacterLevelTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* CharacterHPTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* CharacterManaTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* StrengthStatTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* PerceptionStatTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* EnduranceStatTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* CharismaStatTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* IntelligenceStatTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* WillStatTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* AgilityStatTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* LuckStatTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* MeleeSkillTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* RangeSkillTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* AssaultSpellsSkillTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* DebuffSpellsSkillTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* RestorationSpellsSkillTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* BuffSpellsSkillTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* DefendSkillTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* PersuasionSkillTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* MeleeAttackTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* RangeAttackTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* RangeAmmoTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* ArmorTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* EvasionChanceTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* TargetingChanceTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* FireResistanceTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* WaterResistanceTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* WindResistanceTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* EarthResistanceTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* LightningResistanceTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* HolyResistanceTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* DarkResistanceTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* BloodResistanceTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* MultielementalResistanceTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* SlashingResistanceTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* CrushingResistanceTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	class UTextBlock* PiercingResistanceTextBlock;

	bool MoreInfoShowed = false;

	UFUNCTION()
	void BackButtonOnHovered();
	UFUNCTION()
	void AbilitiesButtonOnClicked();
	UFUNCTION()
	void AbilitiesButtonOnHovered();
	UFUNCTION()
	void ToggleInfoButtonOnClicked();
	UFUNCTION()
	void ToggleInfoButtonOnHovered();

	void ButtonOnHoveredActions(const UButton* const HoveredButton, const uint8 Index);
};
