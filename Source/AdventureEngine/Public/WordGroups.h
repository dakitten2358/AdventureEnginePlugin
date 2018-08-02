// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WordClasses.h"
#include "UObject/NoExportTypes.h"
#include "WordGroups.generated.h"


struct FWordGroup
{
	WordClass wordClass;
	TArray<FString> strings;
};

/**
 * 
 */
UCLASS(BlueprintType)
class ADVENTUREENGINE_API UWordGroups : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FontFace)
	FString SourceFilename;

	virtual void Serialize(FArchive& Ar) override;
	
	void AddWordGroup(int id, WordClass wordClass, const TArray<FString>& words);

	int Lookup(const FString& word);

private:
	TMap<int32, FWordGroup> groups;
};
