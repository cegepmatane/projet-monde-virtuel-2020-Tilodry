// Fill out your copyright notice in the Description page of Project Settings.


#include "point.h"

Apoint::Apoint()
{
	this->pickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("POINT"));
	SetRootComponent(this->pickupMesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ConeMeshAsset(TEXT("StaticMesh'/Game/Mesh/source/moneta_low_poly.moneta_low_poly'"));
	this->pickupMesh->SetStaticMesh(ConeMeshAsset.Object);
}
void Apoint::ramasser()
{
	if (this->getControlleur()->pointRecupere())
	{
		detruire();
	}
}