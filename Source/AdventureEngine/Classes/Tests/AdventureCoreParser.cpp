#include "Misc/AutomationTest.h"
#include "Vocabulary.h"
#include "WordGroups.h"
#include "Suffixes.h"
#include "Tokenizer.h"
#include "Parser.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAdventureCoreParserCompare, "Adventure.Core.Parser.Compare", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAdventureCoreParserEvaluate, "Adventure.Core.Parser.Evaluate", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool CompareNodes(const TUniquePtr<ParseNode>& expected, const TUniquePtr<ParseNode>& actual);
UVocabulary* CreateVocabulary();

bool FAdventureCoreParserCompare::RunTest(const FString& params)
{
	auto V = CreateVocabulary();
	
	// simple check
	{
		auto expected = ParseNode::Required();
		expected->Left = ParseNode::Text(V->LookupWord(TEXT("put")));
		expected->Right = ParseNode::Required();
		expected->Right->Left = ParseNode::Text(V->LookupWord(TEXT("key")));
		expected->Right->Right = ParseNode::Required();
		expected->Right->Right->Left = ParseNode::Text(V->LookupWord(TEXT("table")));

		if (!CompareNodes(expected, expected))
			AddError(TEXT("Simple tree compare failed!"));
	}

	// intentional failure
	{
		auto expected = ParseNode::Required();
		expected->Left = ParseNode::Text(V->LookupWord(TEXT("put")));
		expected->Right = ParseNode::Required();
		expected->Right->Left = ParseNode::Text(V->LookupWord(TEXT("key")));
		expected->Right->Right = ParseNode::Required();
		expected->Right->Right->Left = ParseNode::Text(V->LookupWord(TEXT("table")));

		auto actual = ParseNode::Required();
		actual->Left = ParseNode::Text(V->LookupWord(TEXT("put")));
		actual->Right = ParseNode::Required();
		actual->Right->Left = ParseNode::Text(V->LookupWord(TEXT("key")));
		actual->Right->Right = ParseNode::Required();
		actual->Right->Right->Left = ParseNode::Text(V->LookupWord(TEXT("asd")));

		if (CompareNodes(expected, actual))
			AddError(TEXT("Different trees compared equally!"));
	}

	// slightly more complex tree
	{
		auto expected = ParseNode::Required();
		expected->Left = ParseNode::Text(V->LookupWord(TEXT("step")));
		expected->Right = ParseNode::Either();
		expected->Right->Left = ParseNode::Optional();
		expected->Right->Left->Left = ParseNode::Text(V->LookupWord(TEXT("on")));
		expected->Right->Left->Right = ParseNode::Text(V->LookupWord(TEXT("over")));
		expected->Right->Right = ParseNode::Text(V->LookupWord(TEXT("table")));

		if (!CompareNodes(expected, expected))
			AddError(TEXT("Complex tree compare failed!"));
	}
	
	return true;
}

bool FAdventureCoreParserEvaluate::RunTest(const FString& params)
{
	auto V = CreateVocabulary();
	Tokenizer tokenizer(V);

	auto Tree = ParseNode::Required();
	Tree->Left = ParseNode::Text(V->LookupWord(TEXT("put")));
	Tree->Right = ParseNode::Required();
	Tree->Right->Left = ParseNode::Text(V->LookupWord(TEXT("key")));
	Tree->Right->Right = ParseNode::Required();
	Tree->Right->Right->Left = ParseNode::Text(V->LookupWord(TEXT("table")));

	Parser p;

	{
		TArray<FWordResult> words;
		tokenizer.Parse(TEXT("put key table"), words);

		if (ParseResult::Fail == p.Parse(V, Tree, words))
			AddError(TEXT("Failed to match simple tree"));

		words.Reset();
		tokenizer.Parse(TEXT("put dog table"), words);
		if (ParseResult::Success == p.Parse(V, Tree, words))
			AddError(TEXT("Successful match on incorrect simple tree"));

		words.Reset();
		tokenizer.Parse(TEXT("put key"), words);
		if (ParseResult::Success == p.Parse(V, Tree, words))
			AddError(TEXT("Successful match on incorrect simple tree"));
	}
	return true;
}

// helpers
bool CompareNodes(const TUniquePtr<ParseNode>& expected, const TUniquePtr<ParseNode>& actual)
{
	if (actual == nullptr)
		return false;

	if (expected->Value != actual->Value)
		return false;

	if (expected->Type != actual->Type)
		return false;

	if (expected->Left != nullptr)
	{
		auto left = CompareNodes(expected->Left, actual->Left);
		if (left == false)
			return false;
	}

	if (expected->Left == nullptr && actual->Left != nullptr)
		return false;

	if (expected->Right != nullptr)
	{
		auto right = CompareNodes(expected->Right, actual->Right);
		if (right == false)
			return false;
	}

	if (expected->Right == nullptr && actual->Right != nullptr)
		return false;

	return true;
}

UVocabulary* CreateVocabulary()
{
	// create a word group for us to use
	UWordGroups* wordGroups = NewObject<UWordGroups>();
	TArray<FString> words;
	words.Add(TEXT("put"));
	wordGroups->AddWordGroup(1, WordClass::ImperativeVerb, words);
	words.Reset(); words.Add(TEXT("key"));
	wordGroups->AddWordGroup(2, WordClass::Noun, words);
	words.Reset(); words.Add(TEXT("table"));
	wordGroups->AddWordGroup(3, WordClass::Noun, words);
	words.Reset(); words.Add(TEXT("asd"));
	wordGroups->AddWordGroup(4, WordClass::Special1, words);
	words.Reset(); words.Add(TEXT("step"));
	wordGroups->AddWordGroup(5, WordClass::ImperativeVerb, words);
	words.Reset(); words.Add(TEXT("on"));
	wordGroups->AddWordGroup(6, WordClass::Conjunction, words);
	words.Reset(); words.Add(TEXT("over"));
	wordGroups->AddWordGroup(7, WordClass::Conjunction, words);
	words.Reset(); words.Add(TEXT("dog"));
	wordGroups->AddWordGroup(8, WordClass::Noun, words);

	// create an empty suffix
	USuffixes* suffixes = NewObject<USuffixes>();

	// and a vocab object we can test with
	UVocabulary* vocab = NewObject<UVocabulary>();
	vocab->WordGroups.Add(wordGroups);
	vocab->Suffixes = suffixes;

	return vocab;
}

#endif