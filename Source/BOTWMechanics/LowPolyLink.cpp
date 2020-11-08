// Fill out your copyright notice in the Description page of Project Settings.


#include "LowPolyLink.h"
#include "Math/Vector.h"

// Sets default values
ALowPolyLink::ALowPolyLink()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a third person camera component.
	ThirdCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	check(ThirdCameraComponent != nullptr);

	// Attach the camera component to our capsule component.
	ThirdCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Enable the pawn to control camera rotation.
	ThirdCameraComponent->bUsePawnControlRotation = true;
	PowerInUse = false;

}

// Called when the game starts or when spawned
void ALowPolyLink::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALowPolyLink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(PowerInUse){
		AimPower();
	}
	

}

// Called to bind functionality to input
void ALowPolyLink::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &ALowPolyLink::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALowPolyLink::MoveRight);
	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &ALowPolyLink::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ALowPolyLink::AddControllerPitchInput);
	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ALowPolyLink::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ALowPolyLink::StopJump);
	PlayerInputComponent->BindAction("Power", IE_Pressed, this, &ALowPolyLink::StartPower);
	PlayerInputComponent->BindAction("Power", IE_Released, this, &ALowPolyLink::StopPower);

}

void ALowPolyLink::MoveForward(float Value)
{
	if (!PowerInUse){
		// Find out which way is "forward" and record that the player wants to move that way.
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ALowPolyLink::MoveRight(float Value)
{
	if (!PowerInUse){
		// Find out which way is "right" and record that the player wants to move that way.
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ALowPolyLink::StartJump()
{
    bPressedJump = true;
}

void ALowPolyLink::StopJump()
{
    bPressedJump = false;
}

void ALowPolyLink::StartPower()
{
    PowerInUse = true;
}

void ALowPolyLink::StopPower()
{
    PowerInUse = false;
	if (UsePower){ 
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		GetWorld()->SpawnActor<AActor>(Ice, HitLocation, FRotator(0, 0, 0), SpawnParams);
	}
}

void ALowPolyLink::AimPower()
{
	FHitResult OutHit;
	FVector Start = ThirdCameraComponent->GetComponentLocation();
	FVector ForwardVector = ThirdCameraComponent->GetForwardVector();
	FVector End = ((ForwardVector * 3000.f) + Start);
	//FCollisionQueryParams CollisionParams;
	const FName TraceTag("MyTraceTag");
 
	GWorld->DebugDrawTraceTag = TraceTag;
	
	FCollisionQueryParams CollisionParams;
	FCollisionResponseParams ResponseParams;
	CollisionParams.TraceTag = TraceTag;
 //
	if(GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_POWER, ECC_WorldStatic, ResponseParams))
	{
		UsePower = (OutHit.GetActor()->GetName().Compare("Plane_2")==0) ? true:false;
		if(UsePower){
			HitLocation = OutHit.Location;
			UGameplayStatics::SpawnEmitterAtLocation(this, PowerHere, OutHit.Location);
		}
		
	}
}

