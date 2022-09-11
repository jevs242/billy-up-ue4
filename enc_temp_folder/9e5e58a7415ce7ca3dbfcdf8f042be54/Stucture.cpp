// Fill out your copyright notice in the Description page of Project Settings.


#include "Stucture.h"
#include "PlayerCube.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#define print(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

// Sets default values
AStucture::AStucture()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = GetRootComponent();

	WallRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Right"));
	WallRight->SetupAttachment(RootComponent);

	WallLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Left"));
	WallLeft->SetupAttachment(RootComponent);

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	Floor->SetupAttachment(RootComponent);

	FloorBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Floor Box Component"));
	FloorBoxComponent->SetupAttachment(Floor);
	FloorBoxComponent->SetBoxExtent(FVector(48, 48, 32));
	FloorBoxComponent->SetGenerateOverlapEvents(true);

	BelowFloorBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Below Floor Box Component"));
	BelowFloorBoxComponent->SetupAttachment(Floor);
	BelowFloorBoxComponent->SetBoxExtent(FVector(150, 500, 100));
	BelowFloorBoxComponent->SetGenerateOverlapEvents(true);

	AboveFloorBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Above Floor Box Component"));
	AboveFloorBoxComponent->SetupAttachment(Floor);
	AboveFloorBoxComponent->SetBoxExtent(FVector(150, 500, 100));
	BelowFloorBoxComponent->SetGenerateOverlapEvents(true);

	FloorBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AStucture::OnBeginOverlap);
	BelowFloorBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AStucture::OnBeginOverlap);
	AboveFloorBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AStucture::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AStucture::BeginPlay()
{
	Super::BeginPlay();


	FVector FloorLoc = Floor->GetComponentLocation();
	float RandomX = FloorLoc.Y + FMath::RandRange(-350, 350);

	Floor->SetWorldLocation(FVector(FloorLoc.X, RandomX ,FloorLoc.Z));

	TArray<AActor*> ReturnedActors;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerCube::StaticClass(), ReturnedActors);
	PlayerCube = nullptr;
	if (ReturnedActors.Num() > 0) 
	{
		PlayerCube = Cast<APlayerCube>(ReturnedActors[0]);
	}

}

// Called every frame
void AStucture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStucture::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComponent == FloorBoxComponent)
	{
		APlayerCube* Player = Cast<APlayerCube>(OtherActor);
		if (Player)
		{
			if (!IsUsedFloor || IsUsedFloor && Player->TryJump != 0)
			{
				if (Player)
				{
					IsUsedFloor = true;
					if (IsUsedFloor)
					{
						PlayerCube->Score++;
						Spawn();
					}
					Player->TryJump = 0;
				}
			}
		}
	}
	else if (OverlappedComponent == BelowFloorBoxComponent)
	{
		APlayerCube* Player = Cast<APlayerCube>(OtherActor);
		if (IsUsedFloor)
		{
			if (Player)
			{
				Player->Destroy();
			}
		}
	}
	else if (OverlappedComponent == AboveFloorBoxComponent)
	{
		APlayerCube* Player = Cast<APlayerCube>(OtherActor);
		if (Player)
		{
			Destroy();
		}
	}
}

void AStucture::Spawn()
{
	FVector Location = PlayerCube->FirstStuctureLoc;
	if (PlayerCube)
	{
		Location.Z += 725.0f * PlayerCube->HowManyStucture;
		PlayerCube->HowManyStucture++;
		AStucture* Stucture = GetWorld()->SpawnActor<AStucture>(BP_Stucture, FTransform(FRotator(0,0,0), Location, FVector(1, 1, 1)));
	}
}


