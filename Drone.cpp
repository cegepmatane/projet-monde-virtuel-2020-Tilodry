// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Engine/Engine.h"
#include "ProjetMondeVirtuelCharacter.h"
#include "DrawDebugHelpers.h"
#include "DroneAI.h"
#include "Engine/Engine.h"
#include "Components/CapsuleComponent.h"




// Sets default values
ADrone::ADrone()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//FString t = GetRootComponent()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("GetRootComponent()->GetName() : %s"), *t)
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, GetRootComponent()->GetName());

	//AIControllerClass = ADroneAI::StaticClass();
	//-------------------------------------------------SETUP CONE DE RECHERCHE-------------------------------------------------//
	this->coneDeRecherche = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone de recherche"));
	this->coneDeRecherche->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ConeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	this->coneDeRecherche->SetStaticMesh(ConeMeshAsset.Object);
	static ConstructorHelpers::FObjectFinder<UMaterial>materialCone(TEXT("Material'/Game/MatrixRain/MatrixRouge/MatrixRain.MatrixRain'"));
	this->coneDeRecherche->SetMaterial(0, materialCone.Object); // On lui attribue le materiel qui lui fera ressembler a un projecteur
	this->coneDeRecherche->SetWorldScale3D(FVector(6, 6, 6));
	this->coneDeRecherche->SetRelativeRotation(FRotator(90, 0, 0));
	this->coneDeRecherche->SetRelativeLocation(FVector(300, 0, 0));
	this->coneDeRecherche->OnComponentBeginOverlap.AddDynamic(this, &ADrone::BeginOverlap);
	this->coneDeRecherche->OnComponentEndOverlap.AddDynamic(this, &ADrone::OnOverlapEnd);
	this->coneDeRecherche->OnBeginCursorOver.AddDynamic(this, &ADrone::CustomOnBeginMouseOver);

	//-------------------------------------------------------------------------------------------------------------------------//

	//---------------------------------------------------SETUP MESH DE DRONE---------------------------------------------------//
	this->meshDrone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh de drone"));
	this->meshDrone->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh>DroneMeshAsset(TEXT("StaticMesh'/Game/drug-drone.drug-drone'"));
	this->meshDrone->SetStaticMesh(DroneMeshAsset.Object);
	this->meshDrone->SetWorldScale3D(FVector(0.05, 0.05, 0.05));
	this->meshDrone->SetRelativeRotation(FRotator(0, -90, 0));
	this->meshDrone->SetRelativeLocation(FVector(0, 0, 0));
	//this->meshDrone->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	GetRootComponent();
	if (UCapsuleComponent* test = Cast<UCapsuleComponent>(GetRootComponent()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast passe"));
		test->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

		test->OnBeginCursorOver.AddDynamic(this, &ADrone::CustomOnBeginMouseOver);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Cast pas passe"));
	}
	this->meshDrone->OnBeginCursorOver.AddDynamic(this, &ADrone::CustomOnBeginMouseOver);

	//-------------------------------------------------------------------------------------------------------------------------//


	//UE_LOG(LogTemp, Warning, TEXT("Rotation actuelle : %s"), *this->coneDeRecherche->GetComponentRotation().ToString());
	//this->coneDeRecherche->SetWorldRotation(FRotator(270, 0, 0));

}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	//this->coneDeRecherche->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // On fait en sorte de ne pas pouvoir avoir de collision physique avec le cone
	//this->meshDrone->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // On fait en sorte de ne pas pouvoir avoir de collision physique avec le cone
	UE_LOG(LogTemp, Warning, TEXT("Création d'un drone"))
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->tickDegat += DeltaTime;
	if (cible && possedeCible && tickDegat > 1)
	{
		AProjetMondeVirtuelCharacter* perso = Cast<AProjetMondeVirtuelCharacter>(cible);
		if (perso)
		{
			perso->setViePersonnage(-2);
			UE_LOG(LogTemp, Warning, TEXT("%d"), perso->getViePersonnage());
		}
		tickDegat = 0;
	}

}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADrone::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ // Quand une cible rentre dans la lumière on la désigne comme nouvelle cible
	if (Cast<AProjetMondeVirtuelCharacter>(OtherActor))
	{
		//FAIRE RAYCAST POUR VERIFIER QU'AUCUN OBJET NE SEPARE THIS ET CIBLE
		if (envoyerRaycast(OtherActor->GetActorLocation()))
		{
			UE_LOG(LogTemp, Warning, TEXT("PASSER ICI"));
			//positionInitiale = coneDeRecherche->GetRelativeTransform(); // On enregistre notre position initiale pour pouvoir s'y remettre une fois la cible perdue
			cible = OtherActor; // On actualise notre membre cible avec la nouvelle cible
			possedeCible = true; // On indique qu'on possède désormais une cible
			FString touche = "Quelqu'un rentre dans mon champs de vision, c'est : " + OtherActor->GetName() + " a la position : " + OtherActor->GetTargetLocation().ToString();
			UE_LOG(LogTemp, Warning, TEXT("%s"), *touche);
		}

	}
}

void ADrone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{ // Lorsque la cible quitte la lumière on supprime notre cible
	if (Cast<AProjetMondeVirtuelCharacter>(OtherActor) && possedeCible)
	{
		possedeCible = false; // On indique qu'un ne possède plus de cible
		cible = NULL;
		FString touche = "Quelqu'un a quitté mon champs de vision, c'est : " + OtherActor->GetName() + " a la position : " + OtherActor->GetTargetLocation().ToString();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *touche);
	}
}

bool ADrone::envoyerRaycast(FVector positionPotentielleCible) {
	UE_LOG(LogTemp, Warning, TEXT("J'envoie un RAYCAST"));
	FHitResult hit;
	float RayLenght = 2000;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(this);
	CollisionParameters.AddIgnoredComponent(meshDrone);
	CollisionParameters.AddIgnoredComponent(coneDeRecherche);
	GetWorld()->LineTraceSingleByChannel(hit, meshDrone->GetComponentLocation(), positionPotentielleCible, ECollisionChannel::ECC_WorldDynamic, CollisionParameters);
	//DrawDebugLine(GetWorld(), meshDrone->GetComponentLocation() + FVector(0,0,-200), positionPotentielleCible, FColor::Green, true, -1, 0, 10.f);
	AActor* ciblePotentielle = hit.GetActor();
	if (ciblePotentielle)
	{
		FString touche = "L'acteur est " + ciblePotentielle->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *touche);
		if (Cast<AProjetMondeVirtuelCharacter>(ciblePotentielle))
		{
			UE_LOG(LogTemp, Warning, TEXT("C'est bien le joueur"));
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Ce n'est pas le joueur"));
			return false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PAS D'ACTEUR"));
		return false;
	}
}

void ADrone::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	this->coneDeRecherche->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // On fait en sorte de ne pas pouvoir avoir de collision physique avec le cone
	this->meshDrone->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}
