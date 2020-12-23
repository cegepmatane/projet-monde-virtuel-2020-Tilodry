// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "controleurApparition.generated.h"

UCLASS()
class PROJETMONDEVIRTUEL_API AcontroleurApparition : public AActor
{
	GENERATED_BODY()
	
public:	


	// Sets default values for this actor's properties
	AcontroleurApparition();

	FORCEINLINE class UBoxComponent* recupererBoiteApparition() const { return this->boiteApparition; }

	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector recupererPointDApparition();


	bool munitionRecuperee();
	bool pointRecupere();


	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* boiteApparition;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
