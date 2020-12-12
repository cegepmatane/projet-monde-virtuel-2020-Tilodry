// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDrone.h"
#include "Kismet/KismetMathLibrary.h"

AMyDrone::AMyDrone() {
	coneDeRecherche = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone"));
	coneDeRecherche->SetupAttachment(GetRootComponent()); // On cr�e un composant cone
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	coneDeRecherche->SetStaticMesh(SphereMeshAsset.Object);  // On donne un mesh de cone a ce composant
	static ConstructorHelpers::FObjectFinder<UMaterial>materialCone(TEXT("Material'/Game/MaterielRecherche.MaterielRecherche'"));
	coneDeRecherche->SetMaterial(0,materialCone.Object); // On lui attribue le materiel qui lui fera ressembler a un projecteur
	coneDeRecherche->SetWorldScale3D(FVector(5, 5, 5)); // On lui donne une taille 5x plus grande qu'un cone basique
	coneDeRecherche->SetWorldRotation(FVector(-90, 0, 0).ToOrientationQuat());

	coneDeRecherche->OnComponentBeginOverlap.AddDynamic(this, &AMyDrone::BeginOverlap); // On lie l'�v�nement Begin Overlap a notre fonction
	coneDeRecherche->OnComponentEndOverlap.AddDynamic(this, &AMyDrone::OnOverlapEnd); // On lie l'�v�nement End Overlap a notre fonction
}
void AMyDrone::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Cr�ation d'un drone"))
}

void AMyDrone::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ // Quand une cible rentre dans la lumi�re on la d�signe comme nouvelle cible
	positionInitiale = coneDeRecherche->GetRelativeTransform(); // On enregistre notre position initiale pour pouvoir s'y remettre une fois la cible perdue
	cible = OtherActor; // On actualise notre membre cible avec la nouvelle cible
	possedeCible = true; // On indique qu'on poss�de d�sormais une cible
	FString touche = "Quelqu'un rentre dans mon champs de vision, c'est : " + OtherActor->GetName() + " a la position : " + OtherActor->GetTargetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *touche);
}

void AMyDrone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{ // Lorsque la cible quitte la lumi�re on supprime notre cible
	coneDeRecherche->SetRelativeTransform(positionInitiale); // On retourne a la position initiale
	possedeCible = false; // On indique qu'un ne poss�de plus de cible
	FString touche = "Quelqu'un a quitt� mon champs de vision, c'est : " + OtherActor->GetName() + " a la position : " + OtherActor->GetTargetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *touche);
}

void AMyDrone::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	coneDeRecherche->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // On fait en sorte de ne pas pouvori avoir de collision physique avec la lumi�re
}

void AMyDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!possedeCible) // Si on ne poss�de pas de cible la lumi�re tourne en rond a la recherche d'une cible
	{
		FRotator NewRotation = FRotator(0.5*DeltaTime, 0, 0); // On tourne de 0.5�xDeltaTime par tick
		FQuat QuatRotation = FQuat(NewRotation);
		coneDeRecherche->AddLocalRotation(QuatRotation, false, 0, ETeleportType::None); // On applique la rotation a notre cone de recherche
	}
	else { // Si on poss�de une cible on fait en sorte que la lumi�re regarde la cible
		FRotator lookAtRotator = UKismetMathLibrary::FindLookAtRotation(coneDeRecherche->GetRelativeLocation(), cible->GetTargetLocation());
		lookAtRotator.Pitch += 90; // +90 en Pitch permet d'adapter le "Lookat" aux propri�t�s du Cone pour le faire regarder avec sa partie ronde, -90 pour regarder avec la pointe
		FQuat QuatRotation = FQuat(lookAtRotator);
		coneDeRecherche->SetRelativeRotation(QuatRotation, false, 0, ETeleportType::None); // On applique la rotation a notre cone de recherche
	}
	
}