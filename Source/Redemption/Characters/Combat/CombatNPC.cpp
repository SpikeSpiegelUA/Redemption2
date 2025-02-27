// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatNPC.h"
#include "..\Miscellaneous\SkillsSpellsAndEffectsActions.h"
#include "..\Characters\Player\PlayerCharacter.h"
#include "..\Miscellaneous\ElementsActions.h"
#include "Redemption/Miscellaneous/RedemptionGameModeBase.h"
#include "..\Dynamics\Gameplay\Perks\NumericalPerk.h"
#include "Kismet/GameplayStatics.h"

ACombatNPC::ACombatNPC()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create ComponentWidget for FloatingHealthBar
	FloatingHealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
	FloatingHealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	FloatingHealthBarWidgetComponent->SetupAttachment(RootComponent);

	//Create ComponentWidget for Crosshair
	CrosshairWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Crosshair"));
	CrosshairWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	CrosshairWidgetComponent->SetupAttachment(RootComponent);

	InitializeSkills();
	InitializeStats();
}

// Called when the game starts or when spawned
void ACombatNPC::BeginPlay()
{
	Super::BeginPlay();
	//Can put it into the CombatEnemyNPC class, but it doesn't look pretty, so here we are.
	if (IsValid(Cast<ACombatEnemyNPC>(this))) {
		MaxHP += GetStat(ECharacterStats::ENDURANCE) * 10;
		MaxMana += GetStat(ECharacterStats::WILL) * 10;
		CurrentHP = MaxHP;
		CurrentMana = MaxMana;
	}
	//Set up properties for FloatingHealthBar
	FloatingHealthBarWidget = Cast<UFloatingHealthBarWidget>(FloatingHealthBarWidgetComponent->GetWidget());
	if (IsValid(FloatingHealthBarWidget)) {
		FloatingHealthBarWidget->HP = CurrentHP;
		FloatingHealthBarWidget->MaxHP = MaxHP;
	}
	SkillsSpellsAndEffectsActions::InitializeElementalResistances(ElementalResistances);
	SkillsSpellsAndEffectsActions::InitializePhysicalResistances(PhysicalResistances);
}

void ACombatNPC::InitializeStats()
{
	StatsMap.Add(ECharacterStats::STRENGTH, 1);
	StatsMap.Add(ECharacterStats::PERCEPTION, 1);
	StatsMap.Add(ECharacterStats::ENDURANCE, 1);
	StatsMap.Add(ECharacterStats::CHARISMA, 1);
	StatsMap.Add(ECharacterStats::INTELLIGENCE, 1);
	StatsMap.Add(ECharacterStats::WILL, 1);
	StatsMap.Add(ECharacterStats::AGILITY, 1);
	StatsMap.Add(ECharacterStats::LUCK, 1);
}

void ACombatNPC::InitializeSkills()
{
	SkillsMap.Add(ECharacterSkills::MELEE, 1);
	SkillsMap.Add(ECharacterSkills::RANGE, 1);
	SkillsMap.Add(ECharacterSkills::ASSAULTSPELLS, 1);
	SkillsMap.Add(ECharacterSkills::DEBUFFSPELLS, 1);
	SkillsMap.Add(ECharacterSkills::RESTORATIONSPELLS, 1);
	SkillsMap.Add(ECharacterSkills::BUFFSPELLS, 1);
	SkillsMap.Add(ECharacterSkills::DEFEND, 1);
	SkillsMap.Add(ECharacterSkills::PERSUASION, 1);
}

// Called every frame
void ACombatNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACombatNPC::GetHitWithBuffOrDebuff_Implementation(const TArray<class AEffect*>& HitEffects, const TArray<FElementAndItsPercentageStruct>& ContainedElements, int ValueOfSkill, int ValueOfStat, const ACombatNPC* const Attacker, const ESpellType BuffOrDebuff)
{
	if (const auto* RedemptionGameModeBase = Cast<ARedemptionGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())); IsValid(RedemptionGameModeBase))
 		if (ABattleManager* BattleManager = RedemptionGameModeBase->GetBattleManager(); IsValid(BattleManager)) {
			ACombatFloatingInformationActor* CombatFloatingInformationActor = GetWorld()->SpawnActor<ACombatFloatingInformationActor>(BattleManager->GetCombatFloatingInformationActorClass(),
				GetActorLocation(), GetActorRotation());
			FString TextForCombatFloatingInformationActor = FString();
			uint8 EvasionRandomNumber = FMath::RandRange(0, 100);
			int ChanceOfEvasion{};
			if(BuffOrDebuff == ESpellType::DEBUFF)
				ChanceOfEvasion = SkillsSpellsAndEffectsActions::GetBuffOrDebuffEvasionChanceAfterResistances(SkillsSpellsAndEffectsActions::GetEvasionValueAfterStatsSkillsPerksAndEffects
				(EvasionChance, Attacker->GetStat(ECharacterStats::PERCEPTION), GetStat(ECharacterStats::PERCEPTION),
				Effects, EEffectArea::EVASION), Effects, ElementalResistances, ContainedElements);
			else
				ChanceOfEvasion = SkillsSpellsAndEffectsActions::GetBuffOrDebuffEvasionChanceAfterResistances(SkillsSpellsAndEffectsActions::GetEvasionValueAfterStatsSkillsPerksAndEffects
				(0, Attacker->GetStat(ECharacterStats::PERCEPTION), GetStat(ECharacterStats::PERCEPTION),
					Effects, EEffectArea::EVASION), Effects, ElementalResistances, ContainedElements);
			if (EvasionRandomNumber <= ChanceOfEvasion) {
				if(BuffOrDebuff == ESpellType::BUFF)
					TextForCombatFloatingInformationActor.Append("Buff missed!");
				else if(BuffOrDebuff == ESpellType::DEBUFF)
					TextForCombatFloatingInformationActor.Append("Debuff missed!");
				else
					TextForCombatFloatingInformationActor.Append("Miss!");
				CombatFloatingInformationActor->SetCombatFloatingInformationText(FText::FromString(TextForCombatFloatingInformationActor));
				return false;
			}
			else {
				if (BuffOrDebuff == ESpellType::BUFF)
					TextForCombatFloatingInformationActor.Append("Buff hit!");
				else if (BuffOrDebuff == ESpellType::DEBUFF)
					TextForCombatFloatingInformationActor.Append("Debuff hit!");
				else
					TextForCombatFloatingInformationActor.Append("Hit!");
				CombatFloatingInformationActor->SetCombatFloatingInformationText(FText::FromString(TextForCombatFloatingInformationActor));
				for (AEffect* Effect : HitEffects)
					Effects.Add(Effect);
				return true;
			}
		}
	return false;
}

bool ACombatNPC::GetHit_Implementation(int ValueOfAttack, const ACombatNPC* const Attacker, const TArray<FElementAndItsPercentageStruct>& AttackerContainedElements, const EPhysicalType ContainedPhysicalType, int ValueOfSkill, int ValueOfStat, bool ForcedMiss)
{
	if (const auto* RedemptionGameModeBase = Cast<ARedemptionGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())); IsValid(RedemptionGameModeBase))
		if (ABattleManager* BattleManager = RedemptionGameModeBase->GetBattleManager(); IsValid(BattleManager)) {
			ACombatFloatingInformationActor* CombatFloatingInformationActor = GetWorld()->SpawnActor<ACombatFloatingInformationActor>(BattleManager->GetCombatFloatingInformationActorClass(), GetActorLocation(), GetActorRotation());
			FString TextForCombatFloatingInformationActor = FString();
			uint8 EvasionRandomNumber = FMath::RandRange(0, 100);
			int ChanceOfEvasion = SkillsSpellsAndEffectsActions::GetEvasionValueAfterStatsSkillsPerksAndEffects(EvasionChance,
				Attacker->GetStat(ECharacterStats::PERCEPTION), GetStat(ECharacterStats::PERCEPTION), Effects,
				EEffectArea::EVASION);
			if (EvasionRandomNumber <= ChanceOfEvasion || ForcedMiss) {
				TextForCombatFloatingInformationActor.Append("Miss!");
				CombatFloatingInformationActor->SetCombatFloatingInformationText(FText::FromString(TextForCombatFloatingInformationActor));
				return false;
			}
			else {
				int ValueOfArmor = SkillsSpellsAndEffectsActions::GetNonEvasionValueAfterStatsSkillsPerksAndEffects(ArmorValue, GetStat(ECharacterStats::ENDURANCE) * 10,
				1, Effects, EEffectArea::ARMOR);
				int ValueOfAttackWithResistances = SkillsSpellsAndEffectsActions::GetAttackValueAfterResistances(SkillsSpellsAndEffectsActions::GetNonEvasionValueAfterStatsSkillsPerksAndEffects(
					ValueOfAttack, ValueOfStat, ValueOfSkill, Attacker->GetEffects(), EEffectArea::DAMAGE), Effects, ElementalResistances,
					AttackerContainedElements, PhysicalResistances, ContainedPhysicalType);
				int FinalValueOfAttack{};
				if (ValueOfAttackWithResistances <= 0)
					FinalValueOfAttack = ValueOfAttackWithResistances;
				else {
					FinalValueOfAttack = ValueOfAttackWithResistances - ValueOfArmor / 10;
					if (FinalValueOfAttack < 5)
						FinalValueOfAttack = 5;
				}
				if (CurrentHP - FinalValueOfAttack < 0) {
					CurrentHP = 0;
					if (IsValid(DizzyEmitterComponent)) {
						DizzyEmitterComponent->DeactivateSystem();
						DizzyEmitterComponent->DestroyComponent();
					}
					if (IsValid(FlamesEmitterComponent)) {
						FlamesEmitterComponent->Deactivate();
						FlamesEmitterComponent->DestroyComponent();
					}
				}
				else {
					CurrentHP -= FinalValueOfAttack;
				}
				if (IsValid(FloatingHealthBarWidget))
					FloatingHealthBarWidget->HP = CurrentHP;
				if(FinalValueOfAttack < 0)
					TextForCombatFloatingInformationActor.Append("+");
				else
					TextForCombatFloatingInformationActor.Append("-");
				TextForCombatFloatingInformationActor.AppendInt(FMath::Abs(FinalValueOfAttack));
				CombatFloatingInformationActor->SetCombatFloatingInformationText(FText::FromString(TextForCombatFloatingInformationActor));
				UCombatCharacterAnimInstance* AnimInstance = Cast<UCombatCharacterAnimInstance>(GetMesh()->GetAnimInstance());
				if (IsValid(AnimInstance)) {
					if (CurrentHP <= 0) {
						AnimInstance->ToggleCombatCharacterIsDead(true);
					}
					if (!GetMesh()->bPauseAnims) {
						if (UCombatAlliesAnimInstance* CombatAlliesAnimInstance = Cast<UCombatAlliesAnimInstance>(GetMesh()->GetAnimInstance()); IsValid(CombatAlliesAnimInstance)) {
							if (CurrentHP > 0 && !CombatAlliesAnimInstance->GetCombatAlliesIsBlocking())
								AnimInstance->ToggleCombatCharacterGotHit(true);
						}
						else {
							if (CurrentHP > 0)
								AnimInstance->ToggleCombatCharacterGotHit(true);
						}
					}
				}
				return true;
			}
		}
	return false;
}

AEffect* ACombatNPC::ConvertActivatedPerkToEffect(const APerk* const ActivatedPerk)
{
	AEffect* NewEffect = NewObject<AEffect>();
	NewEffect->SetEffectArea(ActivatedPerk->GetEffectArea());
	if (const ANumericalPerk* const NumericalPerk = Cast<ANumericalPerk>(const_cast<APerk*>(ActivatedPerk)); IsValid(NumericalPerk)) {
		switch (NumericalPerk->GetPerkValueType()) {
		case EPerkValueType::STANDARD:
			NewEffect->SetEffectType(EEffectType::BUFF);
			break;
		case EPerkValueType::PLAIN:
			NewEffect->SetEffectType(EEffectType::PLAINBUFF);
			break;
		case EPerkValueType::PERCENTAGE:
			NewEffect->SetEffectType(EEffectType::PERCENTBUFF);
			break;
		}
		NewEffect->SetEffectStat(NumericalPerk->GetPerkValue());
	}
	NewEffect->SetEffectName(FText::FromName(ActivatedPerk->GetPerkName()));
	NewEffect->SetDuration(1000);
	NewEffect->SetEffectDescription(ActivatedPerk->GetPerkDescription());
	return NewEffect;
}

UFloatingHealthBarWidget* ACombatNPC::GetFloatingHealthBarWidget() const
{
	return FloatingHealthBarWidget;
}

UWidgetComponent* ACombatNPC::GetCrosshairWidgetComponent() const
{
	return CrosshairWidgetComponent;
}

TArray<FElementAndItsPercentageStruct> ACombatNPC::GetElementalResistances() const
{
	return ElementalResistances;
}

TArray<FPhysicalTypeAndItsPercentageStruct> ACombatNPC::GetPhysicalResistances() const
{
	return PhysicalResistances;
}

TArray<FElementAndItsPercentageStruct> ACombatNPC::GetMeleeWeaponElements() const
{
	return MeleeWeaponElements;
}

TArray<FElementAndItsPercentageStruct> ACombatNPC::GetRangeWeaponElements() const
{
	return RangeWeaponElements;
}

TArray<AEffect*> ACombatNPC::GetEffects() const
{
	return Effects;
}

int ACombatNPC::GetCurrentHP() const
{
	return CurrentHP;
}

int ACombatNPC::GetArmorValue() const
{
	return ArmorValue;
}

int ACombatNPC::GetMeleeAttackValue() const
{
	return MeleeAttackValue;
}

int ACombatNPC::GetRangeAttackValue() const
{
	return RangeAttackValue;
}

int ACombatNPC::GetEvasionChance() const
{
	return EvasionChance;
}

int ACombatNPC::GetRangeAmmo() const
{
	return RangeAmmo;
}

AActor* ACombatNPC::GetStartLocation() const
{
	return StartLocation;
}

const FRotator& ACombatNPC::GetStartRotation() const
{
	return StartRotation;
}

TSubclassOf<ASmartObject> ACombatNPC::GetAIClass() const
{
	return AIClass;
}

const TArray<TSubclassOf<ASpell>>& ACombatNPC::GetAvailableSpells() const
{
	return AvailableSpells;
}

const int8 ACombatNPC::GetStat(const ECharacterStats StatToGet) const
{
	return *StatsMap.Find(StatToGet);
}

const int8 ACombatNPC::GetSkill(const ECharacterSkills SkillToGet) const
{
	return *SkillsMap.Find(SkillToGet);
}

const EPhysicalType ACombatNPC::GetMeleePhysicalType() const
{
	return MeleePhysicalType;
}

const EPhysicalType ACombatNPC::GetRangePhysicalType() const
{
	return RangePhysicalType;
}

float ACombatNPC::GetHealthPercentage()
{
	return CurrentHP / MaxHP;
}

float ACombatNPC::GetManaPercentage()
{
	return CurrentMana/MaxMana;
}

void ACombatNPC::SetRangeAmmo(int8 NewRangeAmmo)
{
	RangeAmmo = NewRangeAmmo;
}

void ACombatNPC::SetStartLocation(const AActor* const NewLocation)
{
	StartLocation = const_cast<AActor*>(NewLocation);
}

void ACombatNPC::SetStartRotation(const FRotator& NewStartRotation)
{
	StartRotation = NewStartRotation;
}

void ACombatNPC::SetStat(const ECharacterStats StatToSet, const int8 NewValue)
{
	StatsMap.Emplace(StatToSet, NewValue);
}

void ACombatNPC::SetSkill(const ECharacterSkills SkillToSet, const int8 NewValue)
{
	SkillsMap.Emplace(SkillToSet, NewValue);
}

void ACombatNPC::AddAvailableSpell(const TSubclassOf<ASpell> SkillToAdd)
{
	AvailableSpells.Add(SkillToAdd);
}


