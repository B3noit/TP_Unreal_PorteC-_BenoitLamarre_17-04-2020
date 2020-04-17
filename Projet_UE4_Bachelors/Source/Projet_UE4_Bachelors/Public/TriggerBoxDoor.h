// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"//So we can use the class UBoxCompenent
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerBoxDoor.generated.h"

UCLASS()
class PROJET_UE4_BACHELORS_API ATriggerBoxDoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATriggerBoxDoor();


	UPROPERTY(EditAnywhere)
		float TotalMassToTrigger; //The Minimum Mass required to open the Swing Door associated.

	UPROPERTY(BlueprintReadOnly)
		bool IsTriggered;	// Bool stating if the volume is triggered


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		class UBoxComponent* TriggerVolume;

	UPROPERTY(EditAnywhere)
		TArray<class ASwingDoor*> DoorToTrigger;
	
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		float GetTotalMass();

	float CurrentMass;
};
