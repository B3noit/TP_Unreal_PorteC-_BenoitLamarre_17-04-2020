// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "SwingDoor.generated.h"

UCLASS()
class PROJET_UE4_BACHELORS_API ASwingDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwingDoor();

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
		FVector TargetLocation;

	UPROPERTY(EditAnywhere)
		float speed = 120;



	void SetIsActive();// Set IsActive true
	void SetIsDesactivated();//Set is active false


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Door;

	FVector GlobalTargetLocation;//Location of the target where the door should slide will change during the game

	FVector GlobalStartLocation;//Location where the door start sliding will change during the game

	FVector InitialTargetLocation;//Location of the target where the door should slide will NOT change during the game

	FVector InitialStartLocation;//Location where the door start sliding will NOT change during the game

	UPROPERTY(EditAnywhere, Category = "DoorState")
		bool IsActive; //state if the triggerBoxDoor is currently interracting with the Door

	UPROPERTY(EditAnywhere, Category = "DoorState")
		bool isFullOpen;//state if the door is fully open

	UPROPERTY(EditAnywhere, Category = "DoorState")
		bool isClosed;//state if the door is completly closed

	UPROPERTY(EditAnywhere, Category = "DoorState")
		bool isOpening;//state if the door is opening

	UPROPERTY(EditAnywhere, Category = "DoorState")
		bool isClosing;//State if the door is closing
			


};
