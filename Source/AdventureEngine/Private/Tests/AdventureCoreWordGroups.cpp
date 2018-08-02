#include "Misc/AutomationTest.h"
#include "WordGroups.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAdventureCoreWordGroups, "Adventure.Core.WordGroups", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FAdventureCoreWordGroups::RunTest(const FString& params)
{
	UWordGroups* wordGroups = NewObject<UWordGroups>();
	TArray<FString> words;
	words.Add(TEXT("put"));
	wordGroups->AddWordGroup(1, WordClass::NoWord, words);
	int id = wordGroups->Lookup(TEXT("put"));
	if (id != 1)
		AddError(TEXT("Failed to lookup word in vocabulary"));
	return true;
}

#endif