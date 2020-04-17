// Fill out your copyright notice in the Description page of Project Settings.


#include "SwingDoor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASwingDoor::ASwingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	RootComponent = Door;
	IsActive = false;
	isFullOpen = false;
	isClosed = true;

}



// Called when the game starts or when spawned
void ASwingDoor::BeginPlay()
{
	Super::BeginPlay();
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	InitialStartLocation = GlobalStartLocation;
	InitialTargetLocation = GlobalTargetLocation;

}

// Called every frame
void ASwingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsActive == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("La porte doit s'ouvir "));
		FVector Location = GetActorLocation();
			float journeyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float journeyTravel = (Location - GlobalStartLocation).Size();
			
			if (isClosed == true)
			{
				speed = 100;

			}

			if (journeyTravel >= journeyLength)
			{
				speed = 0;
				isFullOpen = true;
				isClosed = false;
			}

			FVector DirectionOpen = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location += speed * DeltaTime * DirectionOpen;
			SetActorLocation(Location);
	}
	if(IsActive == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("La porte doit se fermer "));
		FVector Location = GetActorLocation();
		float journeyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float journeyTravel = (Location - GlobalStartLocation).Size();

		if (isClosed == true)
		{
			speed = 0;
			GlobalStartLocation = InitialStartLocation;
			GlobalTargetLocation = InitialTargetLocation;

		}


		if (journeyTravel >= journeyLength && isFullOpen ==false)
		{
			speed = 0;
			isFullOpen = false;
			isClosed = true;
		}

		if (isFullOpen == true)
		{
			speed = 100;
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
			isFullOpen = false;
		}

		FVector DirectionClose = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += speed * DeltaTime * DirectionClose;
		SetActorLocation(Location);

	}

}

void ASwingDoor::SetIsActive()
{
	IsActive = true;
}


void ASwingDoor::SetIsDesactivated()
{
	IsActive = false;
}


