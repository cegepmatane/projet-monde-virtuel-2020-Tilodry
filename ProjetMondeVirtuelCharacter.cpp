// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjetMondeVirtuelCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"
#include "pickup.h"
#include "munitions.h"
#include "Kismet/GameplayStatics.h"
#include "point.h"


AProjetMondeVirtuelCharacter::AProjetMondeVirtuelCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = true; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Setup Sphere Collision
	this->sphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere de collision"));
	//this->sphereCollision->SetupAttachment(RootComponent);
	this->sphereCollision->SetupAttachment(GetRootComponent());
	this->sphereCollision->SetSphereRadius(200.0f);
	this->sphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjetMondeVirtuelCharacter::BeginOverlap);

	// Setup caracteristiques
	this->viePersonnage = 100;
	this->munitions = 1;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AProjetMondeVirtuelCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
	if (this->viePersonnage <= 0)
	{
		GetMovementComponent()->Deactivate();
		this->GetMesh()->SetSimulatePhysics(true);
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			//PlayerController->SetCinematicMode(true, false, false, true, true);
		}

	}
}

void AProjetMondeVirtuelCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ // Quand une cible rentre dans la lumière on la désigne comme nouvelle cible
	this->recupererPickups();
}

void AProjetMondeVirtuelCharacter::recupererPickups()
{
	TArray<AActor*> listeObjets;
	this->sphereCollision->GetOverlappingActors(listeObjets);
	for (AActor* actor : listeObjets)
	{
		if (Amunitions* munition = Cast<Amunitions>(actor))
		{
			munition->ramasser();
			this->munitions++;
		}
		else if (Apoint* point = Cast<Apoint>(actor))
		{
			point->ramasser();
			this->points++;
		}
	}
}

void AProjetMondeVirtuelCharacter::setDroneSelectionne(ADrone* drone)
{
	this->droneSelectionne = drone; 
}

ADrone* AProjetMondeVirtuelCharacter::getDroneSelectionne() const 
{ 
	return this->droneSelectionne; 
}

int AProjetMondeVirtuelCharacter::getViePersonnage() const
{
	return this->viePersonnage;
}
void AProjetMondeVirtuelCharacter::setViePersonnage(int v)
{
	this->viePersonnage += v;
}
int AProjetMondeVirtuelCharacter::getMunitions() const
{
	return this->munitions;
}
void AProjetMondeVirtuelCharacter::setMunitions(int v)
{
	this->munitions += v;
}
int AProjetMondeVirtuelCharacter::getPoints() const
{
	return this->points;
}
void AProjetMondeVirtuelCharacter::setPoints(int v)
{
	this->points += v;
}