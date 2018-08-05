// Fill out your copyright notice in the Description page of Project Settings.

#include "Vocabulary.h"
#include "WordGroups.h"
#include "Suffixes.h"

FWordResult UVocabulary::LookupWord(const FString& inputText) const
{
	auto result = LookupExactWord(inputText);
	if (result == FWordResult::NoWord)
	{
		TArray<FWordResult> suffixWords;
		if (FindSuffixesFor(inputText, suffixWords) == 0)
			return FWordResult::NoWord;

		return suffixWords[0];
	}
	return result;
}

FWordResult UVocabulary::LookupExactWord(const FString& inputText) const
{
	for (auto wordGroups : WordGroups)
	{
		auto result = wordGroups->Lookup(inputText);
		if (result != FWordResult::NoWord)
			return result;
	}

	return FWordResult::NoWord;
}

int32 UVocabulary::FindSuffixesFor(const FString& inputText, TArray<FWordResult>& results) const
{
	for (const auto& suffix : Suffixes->Rules)
	{
		// matches, try and lookup the word
		if (inputText.Right(suffix.InputString.Len()) == suffix.InputString)
		{
			auto result = LookupExactWord(inputText.LeftChop(suffix.InputString.Len()) + suffix.OutputString);
			if ((static_cast<uint32>(result.Type) & static_cast<uint32>(suffix.InputType)) != 0)
			{
				results.Emplace(suffix.OutputType, result.WordGroup);
			}
		}
	}
	return results.Num();
}