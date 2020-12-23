// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Drone.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DroneAI.generated.h"

/**
 * 
 */
UCLASS()
class PROJETMONDEVIRTUEL_API ADroneAI : public AAIController
{
	GENERATED_BODY()
public:
	ADroneAI();
	void OnPossess(APawn* pion) override;
	uint8 ennemiCle;
	uint8 aRejointCle;
	class ADrone* droneLocal;
	FORCEINLINE ADrone* getDrone() const { return this->droneLocal; }

private:
	UPROPERTY(transient)
	class UBlackboardComponent* tableauNoir;
	UPROPERTY(transient)
	class UBehaviorTreeComponent* comportement;
};
