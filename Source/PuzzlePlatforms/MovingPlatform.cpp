// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::AddActiveTrigger()
{
    ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
    if (ActiveTriggers > 0)
    {
        ActiveTriggers--;
    }
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
    GlobalStartLocation = GetActorLocation();
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}



void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (ActiveTriggers > 0) 
    {
        if (HasAuthority())
        {        
            FVector Location = GetActorLocation();
            float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
            float JourneyTravelled = (Location - GlobalStartLocation).Size();

            if (JourneyTravelled >= JourneyLength)
            {
                FVector Swap = GlobalStartLocation;
                GlobalStartLocation = GlobalTargetLocation;
                GlobalTargetLocation = Swap;
            }
            FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
            Location += Direction * DeltaTime * SpeedScale;
            SetActorLocation(Location);
        }
    }
}

/* This works mostly, but when rotating cube it doesnt seem to go ok...

Start:
//GlobalTargetLocation = (GlobalStartLocation + TargetLocation);
//CurrentTargetLocation = GlobalTargetLocation;

Tick:
 FVector InterpLocation = FMath::VInterpConstantTo(GetActorLocation(), CurrentTargetLocation, DeltaTime, SpeedScale);
    SetActorLocation(InterpLocation);
    if (FVector::Distance(InterpLocation,GlobalTargetLocation) <= 5)
    {
        CurrentTargetLocation = GlobalStartLocation;
    }
    else if (FVector::Distance(InterpLocation, GlobalStartLocation) <= 5)
    {
        CurrentTargetLocation = GlobalTargetLocation;
    }
*/