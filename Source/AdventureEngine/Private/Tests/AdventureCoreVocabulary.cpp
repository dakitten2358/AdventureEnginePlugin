#include "Misc/AutomationTest.h"
#include "Vocabulary.h"
#include "WordGroups.h"
#include "Suffixes.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAdventureCoreVocabulary, "Adventure.Core.Vocabulary", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FAdventureCoreVocabulary::RunTest(const FString& params)
{
	// create a word group for us to use
	UWordGroups* wordGroups = NewObject<UWordGroups>();
	TArray<FString> words;
	words.Add(TEXT("put"));
	wordGroups->AddWordGroup(1, WordClass::ImperativeVerb, words);

	// create an empty suffix
	USuffixes* suffixes = NewObject<USuffixes>();
	suffixes->AddSuffix("s", WordClass::ImperativeVerb, "", WordClass::ImperativeVerb);

	// finally, let's create a vocab object we can test with
	UVocabulary* vocab = NewObject<UVocabulary>();
	vocab->WordGroups.Add(wordGroups);
	vocab->Suffixes = suffixes;

	// start by testing a simple lookup
	{
		auto actual = vocab->LookupWord(TEXT("put"));
		auto expected = FWordResult(WordClass::ImperativeVerb, 1);
		if (actual != expected)
			AddError(TEXT("Failed to lookup word in vocabulary"));
	}
	// and a failure case
	{
		auto actual = vocab->LookupWord(TEXT("dog"));
		if (actual != FWordResult::NoWord)
			AddError(TEXT("Found a word not in the vocabulary"));
	}
	// simple suffix test
	{
		auto actual = vocab->LookupWord(TEXT("puts"));
		auto expected = FWordResult(WordClass::ImperativeVerb, 1);
		if (actual != expected)
			AddError(TEXT("Failed to lookup word with suffix"));
	}

	return true;
}

#endif