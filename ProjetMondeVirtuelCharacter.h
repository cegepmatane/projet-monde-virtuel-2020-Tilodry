// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Drone.h"
#include "ProjetMondeVirtuelCharacter.generated.h"

UCLASS(Blueprintable)
class AProjetMondeVirtuelCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AProjetMondeVirtuelCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	class USphereComponent* sphereCollision;

	class ADrone* droneSelectionne;

	UFUNCTION(BlueprintCallable)
		void setDroneSelectionne(ADrone* drone);

	UFUNCTION(BlueprintCallable)
		ADrone* getDroneSelectionne() const;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		int getViePersonnage() const;
	UFUNCTION(BlueprintCallable)
		void setViePersonnage(int v);
	UFUNCTION(BlueprintCallable)
		int getMunitions() const;
	UFUNCTION(BlueprintCallable)
		void setMunitions(int v);
	UFUNCTION(BlueprintCallable)
		int getPoints() const;
	UFUNCTION(BlueprintCallable)
		void setPoints(int v);


private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	int viePersonnage;
	int munitions;
	int points;

	void recupererPickups();

	


};

