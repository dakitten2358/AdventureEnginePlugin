#pragma once

#include "WordClasses.h"
#include "UniquePtr.h"

enum class ParseType
{
	Required,
	Either,
	Optional,
};

enum class ParseResult
{
	Success,
	Fail,
};

struct ParseNode
{
	ParseType Type;
	FWordResult Value;
	TUniquePtr<ParseNode> Left;
	TUniquePtr<ParseNode> Right;

private:
	ParseNode(ParseType t) : Type(t), Value(FWordResult::NoWord) {}

public:
	static TUniquePtr<ParseNode> Required()
	{
		ParseNode* p = new ParseNode(ParseType::Required);
		return TUniquePtr<ParseNode>(p);
	}

	static TUniquePtr<ParseNode> Either()
	{
		ParseNode* p = new ParseNode(ParseType::Either);
		return TUniquePtr<ParseNode>(p);
	}

	static TUniquePtr<ParseNode> Optional()
	{
		ParseNode* p = new ParseNode(ParseType::Optional);
		return TUniquePtr<ParseNode>(p);
	}

	static TUniquePtr<ParseNode> Text(FWordResult value)
	{
		ParseNode* p = new ParseNode(ParseType::Required);
		p->Value = value;
		return TUniquePtr<ParseNode>(p);
	}
};

class Parser
{
public:
	ParseResult Parse(class UVocabulary* Vocabulary, const TUniquePtr<ParseNode>& Root, TArray<FWordResult>& Words);
};
