#include "Misc/AutomationTest.h"
#include "Vocabulary.h"
#include "WordGroups.h"
#include "Suffixes.h"
#include "Tokenizer.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAdventureCoreTokenizer, "Adventure.Core.Tokenizer", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FAdventureCoreTokenizer::RunTest(const FString& params)
{
	// create a word group for us to use
	UWordGroups* wordGroups = NewObject<UWordGroups>();
	TArray<FString> words;
	words.Add(TEXT("put"));
	wordGroups->AddWordGroup(1, WordClass::ImperativeVerb, words);

	// create an empty suffix
	USuffixes* suffixes = NewObject<USuffixes>();
	
	// finally, let's create a vocab object we can test with
	UVocabulary* vocab = NewObject<UVocabulary>();
	vocab->WordGroups.Add(wordGroups);
	vocab->Suffixes = suffixes;

	Tokenizer tokenizer(vocab);

	{
		TArray<FToken> tokens;
		tokenizer.Parse(TEXT("put"), tokens);
		if (tokens.Num() == 1)
		{
			if (tokens[0].Type != ETokenType::Word)
				AddError("Incorrect token type!");
		}
		else
			AddError("Unexpected number of tokens!");
	}

	{
		TArray<FToken> tokens;
		tokenizer.Parse(TEXT("(put,put)"), tokens);
		if (tokens.Num() == 4)
		{
			if (tokens[0].Type != ETokenType::BeginEither)
				AddError("Unexpected token type!");
			if (tokens[1].Type != ETokenType::Word)
				AddError("Unexpected token type!");
			if (tokens[2].Type != ETokenType::Word)
				AddError("Unexpected token type!");
			if (tokens[3].Type != ETokenType::EndEither)
				AddError("Unexpected token type!");
		}
		else
			AddError("Unexpected number of tokens!");
	}

	{
		TArray<FToken> tokens;
		tokenizer.Parse(TEXT("put(put,put)put"), tokens);
		if (tokens.Num() == 6)
		{
			if (tokens[0].Type != ETokenType::Word)
				AddError("Unexpected token type!");
			if (tokens[1].Type != ETokenType::BeginEither)
				AddError("Unexpected token type!");
			if (tokens[2].Type != ETokenType::Word)
				AddError("Unexpected token type!");
			if (tokens[3].Type != ETokenType::Word)
				AddError("Unexpected token type!");
			if (tokens[4].Type != ETokenType::EndEither)
				AddError("Unexpected token type!");
			if (tokens[5].Type != ETokenType::Word)
				AddError("Unexpected token type!");
		}
		else
			AddError("Unexpected number of tokens!");
	}

	return true;
}

#endif