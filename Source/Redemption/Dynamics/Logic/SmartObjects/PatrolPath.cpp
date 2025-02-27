// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPath.h"
#include "Components/SplineComponent.h"

APatrolPath::APatrolPath()
{
	PrimaryActorTick.bCanEverTick = false;

	Path = CreateDefaultSubobject<USplineComponent>(TEXT("Path"));
	Path->SetupAttachment(GetRootComponent());
	Path->bDrawDebug = true;
}

void APatrolPath::BeginPlay()
{
	Super::BeginPlay();
	GetSplinePoints();
}

void APatrolPath::GetSplinePoints()
{
	for (int i = 0; i <= Path->GetNumberOfSplinePoints(); ++i)
		Locations.Add(Path->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World));
}

TArray<FVector> APatrolPath::GetLocations()
{
	return Locations;
}
