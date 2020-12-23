// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "pickup.h"
#include "munitions.generated.h"

/**
 * 
 */
UCLASS()
class PROJETMONDEVIRTUEL_API Amunitions : public Apickup
{
	GENERATED_BODY()

public:
	Amunitions();
	void ramasser();
	
};
