// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ennemi.generated.h"

UCLASS()
class MONDEVIRTUEL_API AEnnemi : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnnemi();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caractéristiques")
		int pourcentageDeReussitePrincipale = 40;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caractéristiques")
		int pourcentageDeReussiteSecondaire = 70;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caractéristiques")
		int delaiAvantNouveau = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caractéristiques")
		TArray<FVector> listePointDApparition;
	UFUNCTION()
		void recevoirTirPrincipale();
	UFUNCTION()
		void recevoirTirSecondaire();
	UFUNCTION()
		void demanderNouvelActeur();
	UFUNCTION()
		void faireApparaitreNouvelActeur();
	UFUNCTION()
		void recupererListePointDApparition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
