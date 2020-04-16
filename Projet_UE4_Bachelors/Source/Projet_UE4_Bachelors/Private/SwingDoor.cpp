// Fill out your copyright notice in the Description page of Project Settings.


#include "SwingDoor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASwingDoor::ASwingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsOpen = false;
	IsReady = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	RootComponent = DoorFrame;


	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASwingDoor::BeginPlay()
{
	Super::BeginPlay();

	RotateValue = 1.0f;

	if (OpenDoorCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("ControlDoor"));
		TimelineFinishedCallback.BindUFunction(this, FName("SetDoorState"));

		MyTimeline.AddInterpFloat(OpenDoorCurve, TimelineCallback);
		MyTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
}

// Called every frame
void ASwingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MyTimeline.TickTimeline(DeltaTime);

}

void ASwingDoor::ControlDoor()
{
	TimelineValue = MyTimeline.GetPlaybackPosition();
	CurveFloatValue = RotateValue*OpenDoorCurve->GetFloatValue(TimelineValue);

	FQuat NewRotation = FQuat(FRotator(0.0f, CurveFloatValue, 0.0f));

	Door->SetRelativeRotation(NewRotation);
}

void ASwingDoor::ToggleDoor()
{
	if (IsReady)
	{
		IsOpen = !IsOpen;

		APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
		FVector PawnLocation = MyPawn->GetActorLocation();
		FVector Direction = GetActorLocation() - PawnLocation;
		Direction = UKismetMathLibrary::LessLess_VectorRotator(Direction, GetActorRotation());


		if (IsOpen)
		{
			if (Direction.X > 0.0f)
			{
				RotateValue = 1.0f;
			}
			else
			{
				RotateValue = -1.0f;
			}
			IsReady = false;
			MyTimeline.PlayFromStart();
		}
		else
		{
			IsReady = false;
		}
	}
}

void ASwingDoor::setDoorState()
{
	IsReady = true;
}

