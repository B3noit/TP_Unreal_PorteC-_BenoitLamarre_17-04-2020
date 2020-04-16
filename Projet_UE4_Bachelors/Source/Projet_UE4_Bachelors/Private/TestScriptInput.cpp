// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/PlayerController.h"
#include "TestScriptInput.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"//GetWOrld()

// Sets default values for this component's properties
UTestScriptInput::UTestScriptInput()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentDoor = NULL;

	fltReach = 200.f;

	// ...
}


void UTestScriptInput::SetInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (ensure(InputComponent)) {
		UE_LOG(LogTemp, Warning, TEXT("Component Input Find FOR OpenDoor"));
	}
}

// Called when the game starts
void UTestScriptInput::BeginPlay()
{
	Super::BeginPlay();
	SetInputComponent();

	if (InputComponent) {
		InputComponent->BindAction("Action", IE_Pressed, this, &UTestScriptInput::OpenDoor);
	}
	
	if (EToUse) {
		EToUse->AddToViewport();
	}

	// ...
	
}


// Called every frame
void UTestScriptInput::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	FHitResult Hit;

	FVector PlayerViewPointVector;
	FRotator PlayerViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointVector, PlayerViewPointRotator);


	FVector LineEnd = PlayerViewPointVector + PlayerViewPointRotator.Vector() * fltReach;

	FCollisionQueryParams ColisionParams;

	DrawDebugLine(GetWorld(), PlayerViewPointVector, LineEnd, FColor::Green, false, 1, 0, 1);

	//if (GetWorld()->LineTraceSingleByChannel(Hit, PlayerViewPointVector, LineEnd, ECC_Visibility, ColisionParams))
	if (GetWorld()->LineTraceSingleByChannel(Hit, PlayerViewPointVector, LineEnd, ECC_PhysicsBody,ColisionParams))
	{
		if (Hit.bBlockingHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("colision1 %s"), *Hit.GetActor()->GetName());
			if (Hit.GetActor()->GetClass()->IsChildOf(ASwingDoor::StaticClass()))
			{
				EToUse->GetWidgetFromName("EToUse")->SetVisibility(ESlateVisibility::Visible);
				CurrentDoor = Cast<ASwingDoor>(Hit.GetActor());
				UE_LOG(LogTemp, Warning, TEXT("colision2"));

			}
		}
	}
	else
	{
		EToUse->GetWidgetFromName("EToUse")->SetVisibility(ESlateVisibility::Hidden);
		CurrentDoor = NULL;	
		UE_LOG(LogTemp, Warning, TEXT("Pas de colision"));
	}

	// ...
}

void UTestScriptInput::Printlol()
{
	UE_LOG(LogTemp, Warning, TEXT("TestSucess"));
}

void UTestScriptInput::OpenDoor()
{
	if (CurrentDoor)
	{
		CurrentDoor->ToggleDoor();
	}
}

