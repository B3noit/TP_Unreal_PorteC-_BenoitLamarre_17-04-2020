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

}



// Called when the game starts or when spawned
void ASwingDoor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASwingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ASwingDoor::ActiveTrigger()
{
}

void ASwingDoor::NonActiveTrigger()
{
}





