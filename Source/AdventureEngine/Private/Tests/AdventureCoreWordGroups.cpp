#include "Misc/AutomationTest.h"
#include "WordGroups.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAdventureCoreWordGroups, "Adventure.Core.WordGroups", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FAdventureCoreWordGroups::RunTest(const FString& params)
{
	UWordGroups* wordGroups = NewObject<UWordGroups>();
	TArray<FString> words;
	words.Add(TEXT("put"));
	wordGroups->AddWordGroup(1, WordClass::ImperativeVerb, words);

	auto actual = wordGroups->Lookup(TEXT("put"));
	auto expected = FWordResult(WordClass::ImperativeVerb, 1);

	if (actual != expected)
		AddError(TEXT("Failed to lookup word in vocabulary"));
	
	return true;
}

#endif