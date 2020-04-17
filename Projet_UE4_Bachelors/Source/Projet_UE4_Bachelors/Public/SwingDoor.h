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
		float speed = 20;

	void ActiveTrigger();
	void NonActiveTrigger();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Door;

	FVector GlobalTargetLocation;

	FVector GlobalStartLocation;

			


};
