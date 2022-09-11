// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCube.h"
#include "Components/PrimitiveComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCube::APlayerCube()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Component"));

	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 900.f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	CameraComponent->SetupAttachment(CameraBoom);
	CameraComponent->bUsePawnControlRotation = false;


	RootComponent = GetRootComponent();
	
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(true);
}

// Called to bind functionality to input
void APlayerCube::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCube::Jump);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &APlayerCube::MoveRight);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &APlayerCube::MoveLeft);

}


// Called when the game starts or when spawned
void APlayerCube::BeginPlay()
{

	Super::BeginPlay();
	
}

// Called every frame
void APlayerCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Mesh->SetRelativeLocation(FVector(0, Mesh->GetRelativeLocation().Y, Mesh->GetRelativeLocation().Z));
	RootComponent->SetRelativeLocation(Mesh->GetRelativeLocation());
}


void APlayerCube::Jump()
{
	if (TryJump < LimitTryJump)
	{
		Mesh->AddForce(FVector(0,0 , Speed));
		++TryJump;
	}
}

void APlayerCube::MoveRight()
{
	Mesh->AddForce(FVector(0, -Speed / 1.5, 0));
}

void APlayerCube::MoveLeft()
{
	Mesh->AddForce(FVector(0, Speed / 1.5,0));
}
