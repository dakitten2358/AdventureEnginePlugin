// Fill out your copyright notice in the Description page of Project Settings.

#include "WordGroups.h"
#include "Engine/Engine.h"

void UWordGroups::AddWordGroup(int id, WordClass wordClass, const TArray<FString>& words)
{
	auto& group = groups.Add(id);
	group.wordClass = wordClass;
	group.strings = words;
}

int UWordGroups::Lookup(const FString& word)
{
	for (auto v : groups)
	{
		if (v.Value.strings.Contains(word))
			return v.Key;
	}

	return 0;
}

FArchive &operator <<(FArchive& Ar, FWordGroup& WordGroup)
{
	Ar << WordGroup.wordClass;
	Ar << WordGroup.strings;
	return Ar;
}

void UWordGroups::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	if (Ar.IsLoading())
	{
		Ar << groups;

		if (GEngine)
		{
			auto debugMessage = FString::Printf(TEXT("Added %d entries"), groups.Num());
			GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, debugMessage);
		}

	}
	else
	{
		// Only save the inline data in a cooked build if we're using the inline loading policy
		Ar << groups;
	}
}