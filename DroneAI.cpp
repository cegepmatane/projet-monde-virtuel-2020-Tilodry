// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneAI.h"
#include "GameFramework/CharacterMovementComponent.h"


ADroneAI::ADroneAI() {
	this->tableauNoir = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Tableau noir"));
	this->comportement = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Comportement"));
}

void ADroneAI::OnPossess(APawn* pion) {
	Super::OnPossess(pion);
	ADrone* drone = Cast<ADrone>(pion);
	if (drone)
	{
		this->droneLocal = drone;
		drone->GetCharacterMovement()->MaxWalkSpeed *= 0.75;
		drone->GetCharacterMovement()->MaxAcceleration *= 0.75;
		this->tableauNoir->InitializeBlackboard(*(drone->comportement->BlackboardAsset));
		this->ennemiCle = this->tableauNoir->GetKeyID(TEXT("cible"));
		this->aRejointCle = this->tableauNoir->GetKeyID(TEXT("aRejointCible"));
		this->comportement->StartTree(*(drone->comportement));
		this->tableauNoir->SetValueAsBool(FName("aRejointCible"), true);
	}

}