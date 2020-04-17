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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Total mass C++volume = %f"),CurrentMass));
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
//Not Used
void ATriggerBoxDoor::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

}
//Not Used
void ATriggerBoxDoor::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
}


/****GetTotalMass
Description: Called every tick, store all the actor in an array then add the mass of each actor which have a mmesh component

Input:	All the actor overlapping the trigger volume

Output: return the total mass in a float

Note: -
****************/
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

