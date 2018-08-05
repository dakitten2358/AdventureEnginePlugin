// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WordClasses.h"
#include "Vocabulary.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREENGINE_API UVocabulary : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adventure")
	TArray<class UWordGroups*> WordGroups;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adventure")
	class USuffixes* Suffixes;

	FWordResult LookupWord(const FString& inputText) const;

private:
	FWordResult LookupExactWord(const FString& inputText) const;
	int32 FindSuffixesFor(const FString& inputText, TArray<FWordResult>& results) const;
	
	
};
