// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "BehaviorTree/BTService.h"
#include "GameFramework/PlayerController.h"
#include "DroneAI.h"
#include "ProjetMondeVirtuelCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "ServiceChercherJoueur.generated.h"

/**
 * 
 */
UCLASS()
class PROJETMONDEVIRTUEL_API UServiceChercherJoueur : public UBTService
{
	GENERATED_BODY()
public:
	UServiceChercherJoueur();
	TArray<AActor*> listeCheckpoint;
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	int8 recupererListeCheckpoint();
	int8 indexDeCheckpoint = 0;
	
};
