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
	isOpening = false;
	isClosing = false;

}



// Called when the game starts or when spawned
void ASwingDoor::BeginPlay()
{
	Super::BeginPlay();
	//initialisation bloc

	GlobalStartLocation = GetActorLocation(); 
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	InitialStartLocation = GlobalStartLocation;//Save the initial StartLocation in "InitialStartLocation"
	InitialTargetLocation = GlobalTargetLocation;//Save the initial TargetLocation in "InitialTargetLocation"

}

// Called every frame
void ASwingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsActive == true)
	{//When active the door should open itself

		FVector Location = GetActorLocation();//The "Location" variable is used to set the location of the door in the next tick
			float journeyLength = (GlobalTargetLocation - GlobalStartLocation).Size();//Total length since the begining of the slide
			float journeyTravel = (Location - GlobalStartLocation).Size();//Current length of the slide
			
			if (isClosed == true)//When the door is activated while it's completely closed
			{
				speed = 100;
				isClosed = false;
				isOpening = true;
				isClosing = false;
				isFullOpen = false;

			}

			if (journeyTravel >= journeyLength)//When the door is fully open so the total lenght is at least equal to the current length
			{//When fully open the door doesn't mode so the speed is set to 0
				speed = 0;
				isFullOpen = true;
				isClosed = false;
				isOpening = false;
				isClosing = false;
			}

			FVector DirectionOpen = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location += speed * DeltaTime * DirectionOpen;
			SetActorLocation(Location);
	}
	if(IsActive == false)
	{//When active the door should close itself

		FVector Location = GetActorLocation();
		float journeyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float journeyTravel = (Location - GlobalStartLocation).Size();

		if (isOpening == true)//When the door is desactivated while it's opening itself
		{//Swap the direction of the slide of the door
			speed = 100;
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
			isFullOpen = false;
			isClosing = true;
			isOpening = false;			
			isClosed = false;

		}
		if (isClosed == true)//When the door is desactivated and it's already closed 
		{//Swap the direction of the slide of the door because the only thing that can happen is the opening of the door
			speed = 0;//When closed the door doesn't mode so the speed is set to 0
			GlobalStartLocation = InitialStartLocation;
			GlobalTargetLocation = InitialTargetLocation;
			isOpening = false;
			isFullOpen = false;
			isClosing = false;

		}


		if (journeyTravel >= journeyLength && isFullOpen ==false)//When the door is closed 
		{//When closed, the door doesn't move so the speed is set to 0
			speed = 0;
			isOpening = false;
			isFullOpen = false;
			isClosing = false;
			isClosed = true;
		}

		if (isFullOpen == true)//When the door is desactivated and it's fully open
		{//Swap the direction of the slide of the door
			speed = 100;
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
			isFullOpen = false;
			isClosing = true;
			isOpening = false;
			isClosed = false;
		}

		FVector DirectionClose = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += speed * DeltaTime * DirectionClose;//Set the new location according to the differnets states of the door.
		SetActorLocation(Location);//Set the new location of the "actor" so the door for the next tick so the door moves.

	}

}


/****GetTotalMass
Description: Called when the triggerBoxDoor associated state the mass of the meshes can activate the door

Input:	

Output: Set the boolean IsActive to "true"

Note: -
****************/
void ASwingDoor::SetIsActive()
{
	IsActive = true;
}

/****GetTotalMass
Description: Called when the triggerBoxDoor associated state the mass of the meshes can't activate the door

Input:

Output: Set the boolean IsActive to "false"

Note: -
****************/
void ASwingDoor::SetIsDesactivated()
{
	IsActive = false;
}


