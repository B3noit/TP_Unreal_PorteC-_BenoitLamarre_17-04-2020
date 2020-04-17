// Fill out your copyright notice in the Description page of Project Settings.

#include "TestScriptInput.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"//GetWOrld()

// Sets default values for this component's properties
UTestScriptInput::UTestScriptInput()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTestScriptInput::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTestScriptInput::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}





