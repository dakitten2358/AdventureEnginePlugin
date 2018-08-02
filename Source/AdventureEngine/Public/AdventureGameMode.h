// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AdventureGameMode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ADVENTUREENGINE_API AAdventureGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure")
	void PlayerCommand(const FString& playerCommand);
	
	
};
