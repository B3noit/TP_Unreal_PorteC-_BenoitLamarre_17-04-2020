// Fill out your copyright notice in the Description page of Project Settings.


#include "CGrabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"//GetWOrld()
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"


/****************************************************************************************************
Description : Constructor, Sets default values for this component's properties
Input : None

Output : None

Note ://

******************************************************************************************************/
UCGrabber::UCGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	fltReach=200.f;

	PhysicsHandle = NULL;

	InputComponent = NULL;

	CurrentDoor = NULL;
	// ...
}

void UCGrabber::OpenDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("PorteToggle0"));
	if (CurrentDoor)
	{
		CurrentDoor->ToggleDoor();
	}
}

/****************************************************************************************************
Description : Call when game start
Input : None

Output : None

Note ://

******************************************************************************************************/
void UCGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetInputComponent();
	
	if (InputComponent) {
			InputComponent->BindAction("Grab", IE_Pressed, this, &UCGrabber::Grab);
			InputComponent->BindAction("Grab", IE_Released, this, &UCGrabber::Release);

			InputComponent->BindAction("Action", IE_Released, this, &UCGrabber::OpenDoor);		
	}

	if (EToUse)
	{
		EToUse->AddToViewport();
	}
	// ...
	
}

/****************************************************************************************************
Description : Call every frame
Input : DeltaTime,TickType, ThisFunctionTick

Output : ThisFunctionTick

Note :Delta time is the time between two frames

******************************************************************************************************/
void UCGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FHitResult Hit ;

	FVector PlayerViewPointVector;
	FRotator PlayerViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointVector, PlayerViewPointRotator);


	FVector LineEnd = PlayerViewPointVector + PlayerViewPointRotator.Vector() * fltReach;

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	DrawDebugLine(GetWorld(), PlayerViewPointVector, LineEnd, FColor::Green, false, 1, 0, 1);

	if (GetWorld()->LineTraceSingleByChannel(Hit, PlayerViewPointVector, LineEnd, ECC_Visibility, TraceParameters))
	{
		if (Hit.bBlockingHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("colision1 %s"), *Hit.GetActor()->GetName());
			if (Hit.GetActor()->GetClass()->IsChildOf(ASwingDoor::StaticClass()))
			{
				//EToUse->GetWidgetFromName("EToUse")->SetVisibility(ESlateVisibility::Visible);
				CurrentDoor = Cast<ASwingDoor>(Hit.GetActor());
				UE_LOG(LogTemp, Warning, TEXT("colision2"));

			}
		}
	}
	else
	{
		//EToUse->GetWidgetFromName("EToUse")->SetVisibility(ESlateVisibility::Hidden);
		CurrentDoor = NULL;
		UE_LOG(LogTemp, Warning, TEXT("Pas de colision"));
	}


	
	// ...
	//Update ref PhysicsHandle component
	if (PhysicsHandle->GrabbedComponent) {

		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
	
}


/****************************************************************************************************
Description : This function return the Hit result of the component that is hit by the ray tracing in case of 
collision withe an object having as collision channel ECC:TYPE PhysicsBody

Input : None

Output : None

Note ://

******************************************************************************************************/
FHitResult UCGrabber::GetFirstPhysicsBodyInReach()
{
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	

	/*if (GetWorld()->LineTraceSingleByObjectType(Hit, GetReachLineStart(), GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters)) {
		
		DrawDebugLine(GetWorld(), GetReachLineStart(), GetReachLineEnd(), FColor::Green, false, 10.f);

	}
	else
	{
		DrawDebugLine(GetWorld(), GetReachLineStart(), GetReachLineEnd(), FColor::Red, false, 10.f);

	}*/
	GetWorld()->LineTraceSingleByObjectType(Hit, GetReachLineStart(), GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

	

	return Hit;
}


/****************************************************************************************************
Description : This function get physicsHandle component from Blueprint, if you find it! Caution!! Always 
do be carfull to secure your pointer!

Input : None

Output : None

Note ://

******************************************************************************************************/

void UCGrabber::FindPhysicsHandleComponent()
{

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (ensure(PhysicsHandle))
		UE_LOG(LogTemp, Warning, TEXT("Component PhysicsHandle Find"));


}

void UCGrabber::SetInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (ensure(InputComponent)) {
		UE_LOG(LogTemp, Warning, TEXT("Component Input Find FOR GRAB"));
	}
}

/****************************************************************************************************
Description : This function Grab component from yhe scene, if you find it! Caution!! Always
do be carfull to secure your pointer!

Input : None

Output : None

Note ://

******************************************************************************************************/

void UCGrabber::Handle()
{
	FHitResult Hit=GetFirstPhysicsBodyInReach();

	UPrimitiveComponent *ComponentToGrab = Hit.GetComponent();
	AActor *ActorHit = Hit.GetActor();

	if (ActorHit) {

		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation());
	}


}



void UCGrabber::Grab() {

	Handle();

}

/****************************************************************************************************
Description : This function set  physicsHandle (Loose Component)

Input : None

Output : None

Note ://
******************************************************************************************************/

void UCGrabber::Release()
{

	PhysicsHandle->ReleaseComponent();

}

/****************************************************************************************************
Description : This function return the position of line trace start point

Input : None

Output : None

Note :Private function

******************************************************************************************************/

FVector UCGrabber::GetReachLineStart()
{
	FVector PlayerViewPointVector;
	FRotator PlayerViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointVector, PlayerViewPointRotator);

	return PlayerViewPointVector;
}

/****************************************************************************************************
Description : This function return the position of line trace end point

Input : None

Output : None

Note :Private function

******************************************************************************************************/

FVector UCGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointVector;
	FRotator PlayerViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointVector, PlayerViewPointRotator);

	FVector LineEnd=PlayerViewPointVector + PlayerViewPointRotator.Vector()*fltReach;

	return LineEnd;
}

