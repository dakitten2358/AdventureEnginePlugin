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
	IndicativeVerb = 0x200,
	Adverb = 0x400,
	ImperativeVerb = 0x800, //(such as "is","went" as opposed to _do_ this or that, which is imperative)

	NoWord = 0x0,
	Anyword = 0x4FF,
};
