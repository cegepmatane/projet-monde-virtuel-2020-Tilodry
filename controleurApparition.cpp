// Fill out your copyright notice in the Description page of Project Settings.


#include "controleurApparition.h"
#include "Kismet/KismetMathLibrary.h"
#include "pickup.h"
#include "munitions.h"
#include "point.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"



// Sets default values
AcontroleurApparition::AcontroleurApparition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boiteApparition = CreateDefaultSubobject<UBoxComponent>(TEXT("Boite apparition"));
	//RootComponent = boiteApparition;

}

// Called when the game starts or when spawned
void AcontroleurApparition::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < 40; i++)
	{
		pointRecupere();
	}
	
}

// Called every frame
void AcontroleurApparition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AcontroleurApparition::recupererPointDApparition()
{
	FVector SpawnOrigin = this->boiteApparition->Bounds.Origin;
	FVector SpawnExtent = this->boiteApparition->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

bool AcontroleurApparition::munitionRecuperee()
{
	FActorSpawnParameters parametres;
	parametres.Owner = this;
	parametres.Instigator = GetInstigator();
	FVector spawnLocation = recupererPointDApparition();
	FRotator spawnRotation(0, 0, 0);

	Amunitions* const munitionSpawn = GetWorld()->SpawnActor<Amunitions>(Amunitions::StaticClass(), spawnLocation, spawnRotation, parametres);
	if (munitionSpawn)
	{
		munitionSpawn->setControlleur(this);
		while (!munitionSpawn->getControlleur())
		{
			munitionSpawn->setControlleur(this);
		}
	}

	return true;
	
	/*TArray<UPrimitiveComponent*> tableau;
	munitionSpawn->GetOverlappingComponents(tableau);
	while (tableau.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Munition Overlap, changement"));
		munitionSpawn->SetActorLocation(recupererPointDApparition());
	}*/
}

bool AcontroleurApparition::pointRecupere()
{
	FActorSpawnParameters parametres;
	//parametres.Owner = this;
	//parametres.Instigator = GetInstigator();
	FVector spawnLocation = recupererPointDApparition();
	FRotator spawnRotation(0, 0, 0);

	Apoint* const pointSpawn = GetWorld()->SpawnActor<Apoint>(Apoint::StaticClass(), spawnLocation, spawnRotation, parametres);
	pointSpawn->setControlleur(this);
	float chance = FMath::RandRange(0.f, 10.f);
	if (chance > 9)
	{
		UE_LOG(LogTemp, Warning, TEXT("Munition spawn !"));
		munitionRecuperee();
	}
	while (!pointSpawn->getControlleur())
	{
			pointSpawn->setControlleur(this);
	}

	return true;
	
	/*TArray<UPrimitiveComponent*> tableau;
	pointSpawn->GetOverlappingComponents(tableau);
	while (tableau.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("point Overlap, changement"));
		pointSpawn->SetActorLocation(recupererPointDApparition());
	}*/
}
