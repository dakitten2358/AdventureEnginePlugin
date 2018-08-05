#pragma once
#include "WordClasses.h"

enum class ETokenType
{
	Word,
	BeginOptional,
	EndOptional,
	BeginEither,
	EndEither,
	Invalid,
};

struct FToken
{
	ETokenType Type;
	FWordResult Value;
};

class Tokenizer
{
private:
	class UVocabulary* Vocabulary;
	
public:
	Tokenizer(class UVocabulary* InVocabulary);

	bool Parse(const FString& InText, TArray<FToken>& Tokens) const;

private:
	void TokenFromString(const FString& InText, TArray<FToken>& Tokens) const;
	ETokenType TokenTypeFromCharacter(TCHAR ch) const;
};