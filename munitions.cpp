// Fill out your copyright notice in the Description page of Project Settings.


#include "munitions.h"

Amunitions::Amunitions()
{
	this->pickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("POINT"));
	SetRootComponent(this->pickupMesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ConeMeshAsset(TEXT("StaticMesh'/Game/Mesh/flashdrive.flashdrive'"));
	this->pickupMesh->SetStaticMesh(ConeMeshAsset.Object);
	this->pickupMesh->SetWorldScale3D(FVector(20, 20, 20));

}
void Amunitions::ramasser()
{
	//this->getControlleur()->pointRecupere();
	detruire();
}