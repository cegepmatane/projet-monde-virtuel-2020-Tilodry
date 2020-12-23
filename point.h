// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "pickup.h"
#include "point.generated.h"

/**
 * 
 */
UCLASS()
class PROJETMONDEVIRTUEL_API Apoint : public Apickup
{
	GENERATED_BODY()

public:
	Apoint();
	void ramasser();
	
};
