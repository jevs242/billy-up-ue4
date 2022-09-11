// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCube.generated.h"

UCLASS()
class CUBEUP_API APlayerCube : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCube();

	UPROPERTY(EditAnywhere , Category = Component)
		class UStaticMeshComponent* Mesh;

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class USpringArmComponent* CameraBoom;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:

	void Jump();
	void MoveRight();
	void MoveLeft();

	UPROPERTY(EditAnywhere, Category = Property)
		float Speed;
public:
	UPROPERTY(EditAnywhere , Category = Rules)
		int LimitTryJump = 3;
	int TryJump = 0;
	int CounterStucture = 0;
	int HowManyStucture = 2;
	int Score = 0;
	
	FVector FirstStuctureLoc = FVector(80 , 850 , 470); //(X=80.000000,Y=850.000000,Z=470.000000)

};
