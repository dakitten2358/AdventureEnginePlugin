// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WordClasses.h"
#include "UObject/NoExportTypes.h"
#include "Suffixes.generated.h"

struct FSuffix
{
	FString InputString;
	WordClass InputType;
	FString OutputString;
	WordClass OutputType;
};

/**
 * 
 */
UCLASS()
class ADVENTUREENGINE_API USuffixes : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FontFace)
	FString SourceFilename;

	virtual void Serialize(FArchive& Ar) override;

	void AddSuffix(const FString& InputString, WordClass InputType, const FString& OutputString, WordClass OutputType);

	TArray<FSuffix> Rules;
};
