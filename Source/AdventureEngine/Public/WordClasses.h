#pragma once

#include "CoreMinimal.h"

enum class WordClass : uint32
{
	Number = 0x001, //(not found in the vocabulary, set internally)
	Special1 = 0x002,
	Conjunction = 0x004,
	Special3 = 0x008,
	Preposition = 0x010,
	Article = 0x020,
	QualifyingAdjective = 0x040,
	RelativePronoun = 0x080,
	Noun = 0x100,
	IndicativeVerb = 0x200, //(such as "is","went" as opposed to _do_ this or that, which is imperative)
	Adverb = 0x400,
	ImperativeVerb = 0x800, 

	NoWord = 0x0,
	Anyword = 0x4FF,
};

struct FWordResult
{
	WordClass Type;
	uint32 WordGroup;

	FWordResult(WordClass InType, uint32 InWordGroup) : Type(InType), WordGroup(InWordGroup) {}

	bool operator==(const FWordResult& WordResult) const
	{
		return Match(WordResult);
	}

	bool operator!=(const FWordResult& WordResult) const
	{
		return !Match(WordResult);
	}

	bool Match(const FWordResult& WordResult) const
	{
		// no words always match up, even if the groups are different
		if (Type == WordClass::NoWord && WordResult.Type == WordClass::NoWord)
			return true;

		// different word groups is an immediate fail
		if (WordGroup != WordResult.WordGroup)
			return false;

		// but as long as one bit is set, we're good
		return static_cast<WordClass>(static_cast<uint32>(Type) & static_cast<uint32>(WordResult.Type)) != WordClass::NoWord;
	}

	bool ExactMatch(const FWordResult& WordResult) const
	{
		if (WordGroup != WordResult.WordGroup)
			return false;

		return Type == WordResult.Type;
	}

	static FWordResult NoWord;
};
