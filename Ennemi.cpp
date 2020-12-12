// Fill out your copyright notice in the Description page of Project Settings.


#include "Ennemi.h"
#include "Kismet/GameplayStatics.h"

/* Les deux ennemis du jeu auront deux pièces destructibles chacune, je fais donc une classe parent qui regroupe les fonctions qui leurs seront communes*/

// Sets default values
AEnnemi::AEnnemi()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnnemi::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Spawn d'un ennemi"))
	recupererListePointDApparition(); // On récupère tout les points d'apparition possibles du jeu de manière a pouvoir utiliser la fonction demanderNouvelActeur() par la suite
}

// Called every frame
void AEnnemi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnnemi::recevoirTirSecondaire() { // Quand un tir sur la pièce secondaire est recu il a 70% de chance de reussite
	FMath random;
	int resultat = random.RandRange(0, 100); // On récupère un nombre au hasard pour savoir si le tir est un succès
	if (resultat >= 100 - pourcentageDeReussiteSecondaire) // Si le tir est un succès 
	{
		UE_LOG(LogTemp, Warning, TEXT("TOUCHE ARME SECONDAIRE"))
		this->demanderNouvelActeur(); //L'ennemi est en imcapacité de se déplacer et va donc appeler un nouvel acteur pour le remplacer
	} 
	else UE_LOG(LogTemp, Warning, TEXT("PAS TOUCHE ARME SECONDAIRE")) // si le tir echoue rien ne se passe
}

void AEnnemi::recevoirTirPrincipale() { // Quand un tir sur la pièce secondaire est recu il a 40% de chance de reussite
	FMath random;
	int resultat = random.RandRange(0, 100); // On récupère un nombre au hasard pour savoir si le tir est un succès
	if (resultat >= 100 - pourcentageDeReussitePrincipale) // Si le tir est un succès 
	{
		UE_LOG(LogTemp, Warning, TEXT("TOUCHE ARME PRINCIPALE"))
		this->demanderNouvelActeur(); // L'ennemi ne peut plus faire son action principale, chercher ou tirer dépendant du type, il appel donc un nouvel acteur pour le remplacer
	}
	else UE_LOG(LogTemp, Warning, TEXT("PAS TOUCHE ARME PRINCIPALE"))
}

void AEnnemi::demanderNouvelActeur() { // En cas de demande de nouvel acteur
	UE_LOG(LogTemp, Warning, TEXT("DEMANDE NOUVEL ACTEUR"))
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AEnnemi::faireApparaitreNouvelActeur, delaiAvantNouveau, false); // On fait spawn un nouvel acteur dans "delaiAvantNouveau" secondes
}

void AEnnemi::faireApparaitreNouvelActeur() { // On fait spawn un nouvel acteur (a coder)
	UE_LOG(LogTemp, Warning, TEXT("SPAWN NOUVEL ACTEUR")) 
}

void AEnnemi::recupererListePointDApparition() { // On récupère la liste de tout les points d'apparitions sur le monde
	TArray<AActor*> TargetActor;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("SpawnPoint")), TargetActor); // Les points d'apparition sont tous taggé "SpawnPoint" on les cherche donc comme ca dans le monde
	for (AActor* actor : TargetActor)
	{
		listePointDApparition.Add(actor->GetActorLocation()); // On ajoute leurs positions a notre liste privées de FVector, pas besoin de l'objet en entier
	}
	UE_LOG(LogTemp, Warning, TEXT("BIEN ARRIVE ICI"));
}