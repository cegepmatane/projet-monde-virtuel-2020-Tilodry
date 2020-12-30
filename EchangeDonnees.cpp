// Fill out your copyright notice in the Description page of Project Settings.


#include "EchangeDonnees.h"

// Sets default values
AEchangeDonnees::AEchangeDonnees()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	http = &FHttpModule::Get();

}

// Called when the game starts or when spawned
void AEchangeDonnees::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEchangeDonnees::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEchangeDonnees::requestRandomFact()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> demande = http->CreateRequest();
	demande->SetURL("https://uselessfacts.jsph.pl/random.json?language=en");
	demande->SetVerb("GET");
	demande->SetHeader("Content-Type", TEXT("application/json"));
	demande->OnProcessRequestComplete().BindUObject(this, &AEchangeDonnees::getRandomFact);
	demande->ProcessRequest();
}

void AEchangeDonnees::getRandomFact(FHttpRequestPtr demande, FHttpResponsePtr reponse, bool success)
{
	TSharedPtr<FJsonValue> json;
	TSharedRef<TJsonReader<>> lecteur = TJsonReaderFactory<>::Create(reponse->GetContentAsString());
	if (FJsonSerializer::Deserialize(lecteur, json))
	{
		FString fact = json->AsObject()->GetStringField("text");
		GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Green, fact, true);
	}
}


