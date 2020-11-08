// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "LowPolyLink.generated.h"

#define ECC_POWER ECollisionChannel::ECC_GameTraceChannel1

UCLASS()
class BOTWMECHANICS_API ALowPolyLink : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALowPolyLink();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Lets the class know if the power can be used when releasing left click
	bool UsePower;

	// Holds the location of the hit actor
	FVector HitLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// FPS camera.
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ThirdCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* PowerHere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	TSubclassOf<class AActor> Ice;

	//Property for power in use.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PowerInUse;

	// Handles input for moving forward and backward.
	UFUNCTION()
	void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
	void MoveRight(float Value);

	// Sets jump flag when key is pressed.
	UFUNCTION()
	void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
	void StopJump();

	// Sets jump flag when key is pressed.
	UFUNCTION()
	void StartPower();

	// Clears jump flag when key is released.
	UFUNCTION()
	void StopPower();

	// Clears jump flag when key is released.
	UFUNCTION()
	void AimPower();

};
