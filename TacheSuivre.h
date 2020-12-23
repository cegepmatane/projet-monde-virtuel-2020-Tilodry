// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DroneAI.h"
#include "ProjetMondeVirtuelCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "TacheSuivre.generated.h"

/**
 * 
 */
UCLASS()
class PROJETMONDEVIRTUEL_API UTacheSuivre : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& proprietaire, uint8* noeudMemoire) override;

	
};
