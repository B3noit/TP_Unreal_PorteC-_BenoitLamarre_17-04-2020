// Fill out your copyright notice in the Description page of Project Settings.

#include "SwingDoor.h"
#include "Engine/Engine.h"
#include "Components/MeshComponent.h"//So we can use the class UMeshComponent
#include "TriggerBoxDoor.h"
#include "Containers/UnrealString.h"

// Sets default values
ATriggerBoxDoor::ATriggerBoxDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (!ensure(TriggerVolume != nullptr)) return;

	RootComponent = TriggerVolume;

}

// Called when the game starts or when spawned
void ATriggerBoxDoor::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ATriggerBoxDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentMass = GetTotalMass();
	if (CurrentMass) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Overlapped Actor = %f"),CurrentMass));
	}

	if (CurrentMass >= TotalMassToTrigger)
	{
		for (ASwingDoor* Door : DoorToTrigger)
		{
			Door->SetIsActive();
		}
	}
	else
	{
		for (ASwingDoor* Door : DoorToTrigger)
		{
			Door->SetIsDesactivated();
		}
	}
}

void ATriggerBoxDoor::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

}

void ATriggerBoxDoor::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
}

float ATriggerBoxDoor::GetTotalMass()
{
	float TotalMass = 0.0f;

	TArray<AActor*> OverlappingActors;//Array of actor to store all the overlapping actors in the volume

	TSubclassOf<UMeshComponent> MeshClass;

	TArray<UActorComponent*> children;

	UMeshComponent* mesh;

	if (TriggerVolume != NULL) 
	{
		TriggerVolume->GetOverlappingActors(OverlappingActors);	//get all overlapping actors in the volume
		for (int i = 0; i < OverlappingActors.Num(); i++) 
		{
			OverlappingActors[i]->GetComponents(children);
			for (auto& actorComp : children) 
			{
				mesh = Cast<UMeshComponent>(actorComp);
				if (mesh != NULL) 
				{
					TotalMass += mesh->GetMass(); //add the mass of the meshcomponent to  TotalMass
				}
			}
		}
	}

	return TotalMass;
}

