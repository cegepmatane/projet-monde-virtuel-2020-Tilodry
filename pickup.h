// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "controleurApparition.h"
#include "pickup.generated.h"

UCLASS()

class PROJETMONDEVIRTUEL_API Apickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Apickup();
	void detruire();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* pickupMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
		class AcontroleurApparition* controleurLocal;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void setControlleur(AcontroleurApparition* controleur) { this->controleurLocal = controleur; }
	FORCEINLINE AcontroleurApparition* getControlleur() const { return this->controleurLocal; }


	


};
