// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ennemi.h"
#include "MyDrone.generated.h"

/**
 * 
 */
UCLASS()
class MONDEVIRTUEL_API AMyDrone : public AEnnemi
{
	GENERATED_BODY()
public:
	AMyDrone();
	FORCEINLINE class UStaticMeshComponent* getConeDeRecherche() const { return this->coneDeRecherche; }

	UPROPERTY(VisibleAnywhere, Category = "Caracteristiques")
	class UStaticMeshComponent* coneDeRecherche;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caractéristiques")
	class AActor* cible;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caractéristiques")
	bool possedeCible = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caractéristiques")
	FTransform positionInitiale;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, 
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
