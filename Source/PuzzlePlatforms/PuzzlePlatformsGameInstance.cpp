// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/GameEngine.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("Puzzle platforns constructor"));

}

void UPuzzlePlatformsGameInstance::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("Puzzle platforns init"));
}

void UPuzzlePlatformsGameInstance::Host()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, TEXT("Hosting"));
    }

    UWorld* World = GetWorld();
    if (!World) return;
    World->ServerTravel("/Game/PuzzlePlatforms/ThirdPersonMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
    }

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!PlayerController) return;

    PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
