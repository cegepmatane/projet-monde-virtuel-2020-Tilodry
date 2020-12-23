// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Drone.generated.h"

UCLASS()
class PROJETMONDEVIRTUEL_API ADrone : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADrone();
	class UStaticMeshComponent* meshDrone;
	class UStaticMeshComponent* coneDeRecherche;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* comportement;

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

	UFUNCTION(BlueprintImplementableEvent)
		void CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caractéristiques")
		class AActor* cible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caractéristiques")
		bool possedeCible = false;

	bool envoyerRaycast(FVector positionPotentielleCible);

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	float tickDegat = 0;


};
