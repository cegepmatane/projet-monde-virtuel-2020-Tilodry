// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDrone.h"
#include "Kismet/KismetMathLibrary.h"

AMyDrone::AMyDrone() {
	coneDeRecherche = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone"));
	coneDeRecherche->SetupAttachment(GetRootComponent()); // On crée un composant cone
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	coneDeRecherche->SetStaticMesh(SphereMeshAsset.Object);  // On donne un mesh de cone a ce composant
	static ConstructorHelpers::FObjectFinder<UMaterial>materialCone(TEXT("Material'/Game/MaterielRecherche.MaterielRecherche'"));
	coneDeRecherche->SetMaterial(0,materialCone.Object); // On lui attribue le materiel qui lui fera ressembler a un projecteur
	coneDeRecherche->SetWorldScale3D(FVector(5, 5, 5)); // On lui donne une taille 5x plus grande qu'un cone basique
	coneDeRecherche->SetWorldRotation(FVector(-90, 0, 0).ToOrientationQuat());

	coneDeRecherche->OnComponentBeginOverlap.AddDynamic(this, &AMyDrone::BeginOverlap); // On lie l'évènement Begin Overlap a notre fonction
	coneDeRecherche->OnComponentEndOverlap.AddDynamic(this, &AMyDrone::OnOverlapEnd); // On lie l'évènement End Overlap a notre fonction
}
void AMyDrone::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Création d'un drone"))
}

void AMyDrone::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ // Quand une cible rentre dans la lumière on la désigne comme nouvelle cible
	positionInitiale = coneDeRecherche->GetRelativeTransform(); // On enregistre notre position initiale pour pouvoir s'y remettre une fois la cible perdue
	cible = OtherActor; // On actualise notre membre cible avec la nouvelle cible
	possedeCible = true; // On indique qu'on possède désormais une cible
	FString touche = "Quelqu'un rentre dans mon champs de vision, c'est : " + OtherActor->GetName() + " a la position : " + OtherActor->GetTargetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *touche);
}

void AMyDrone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{ // Lorsque la cible quitte la lumière on supprime notre cible
	coneDeRecherche->SetRelativeTransform(positionInitiale); // On retourne a la position initiale
	possedeCible = false; // On indique qu'un ne possède plus de cible
	FString touche = "Quelqu'un a quitté mon champs de vision, c'est : " + OtherActor->GetName() + " a la position : " + OtherActor->GetTargetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *touche);
}

void AMyDrone::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	coneDeRecherche->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // On fait en sorte de ne pas pouvori avoir de collision physique avec la lumière
}

void AMyDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!possedeCible) // Si on ne possède pas de cible la lumière tourne en rond a la recherche d'une cible
	{
		FRotator NewRotation = FRotator(0.5*DeltaTime, 0, 0); // On tourne de 0.5°xDeltaTime par tick
		FQuat QuatRotation = FQuat(NewRotation);
		coneDeRecherche->AddLocalRotation(QuatRotation, false, 0, ETeleportType::None); // On applique la rotation a notre cone de recherche
	}
	else { // Si on possède une cible on fait en sorte que la lumière regarde la cible
		FRotator lookAtRotator = UKismetMathLibrary::FindLookAtRotation(coneDeRecherche->GetRelativeLocation(), cible->GetTargetLocation());
		lookAtRotator.Pitch += 90; // +90 en Pitch permet d'adapter le "Lookat" aux propriétés du Cone pour le faire regarder avec sa partie ronde, -90 pour regarder avec la pointe
		FQuat QuatRotation = FQuat(lookAtRotator);
		coneDeRecherche->SetRelativeRotation(QuatRotation, false, 0, ETeleportType::None); // On applique la rotation a notre cone de recherche
	}
	
}