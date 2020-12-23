// Fill out your copyright notice in the Description page of Project Settings.


#include "pickup.h"

// Sets default values
Apickup::Apickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Apickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Apickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->AddActorWorldRotation(FRotator(0, 90 * DeltaTime, 0));
}

void Apickup::detruire()
{
	Destroy();
}
