// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Engine/Engine.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "EchangeDonnees.generated.h"

UCLASS()
class ECHANGEDEDONNEES_API AEchangeDonnees : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEchangeDonnees();
	FHttpModule* http;

	void requestRandomFact();

	void getRandomFact(FHttpRequestPtr demande, FHttpResponsePtr reponse, bool success);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
