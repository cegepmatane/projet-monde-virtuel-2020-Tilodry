// Fill out your copyright notice in the Description page of Project Settings.


#include "TacheSuivre.h"
#include "Engine/TargetPoint.h"


EBTNodeResult::Type UTacheSuivre::ExecuteTask(UBehaviorTreeComponent& proprietaire, uint8* noeudMemoire) 
{
	ADroneAI* droneAI = Cast<ADroneAI>(proprietaire.GetAIOwner());
	AProjetMondeVirtuelCharacter* cible = Cast<AProjetMondeVirtuelCharacter>(proprietaire.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(droneAI->ennemiCle));
	if (cible) 
	{
		droneAI->MoveToActor(cible, 5.f, true, true, true, 0, true);
		return EBTNodeResult::Succeeded;
	}
	else if (ATargetPoint* checkpoint = Cast<ATargetPoint>(proprietaire.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(droneAI->ennemiCle)))
	{
		if (FVector::Dist(droneAI->GetPawn()->GetActorLocation(), checkpoint->GetTargetLocation()) < 100)
		{
			//UE_LOG(LogTemp, Warning, TEXT("La distance match, on change de checkpoint"))
			if (!proprietaire.GetBlackboardComponent()->GetValueAsBool(FName("aRejointCible")))
			{
				proprietaire.GetBlackboardComponent()->SetValueAsBool(FName("aRejointCible"), true);
			}
		} 
		droneAI->MoveToActor(checkpoint, 5.f, true, true, true, 0, true);
		return EBTNodeResult::Succeeded;	
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
