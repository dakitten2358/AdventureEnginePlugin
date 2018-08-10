#include "Tokenizer.h"
#include "Vocabulary.h"

Tokenizer::Tokenizer(UVocabulary* InVocabulary)
	: Vocabulary(InVocabulary)
{

}

bool Tokenizer::Parse(const FString& InText, TArray<FToken>& Tokens) const
{
	const TCHAR* delims[] = { TEXT(" "), TEXT(",") };
	// split the string up and
	TArray<FString> stringParts;
	InText.ParseIntoArray(stringParts, delims, 2, true);
	for (const auto& stringPart : stringParts)
	{
		TokenFromString(stringPart, Tokens);
	}

	return true;
}

bool Tokenizer::Parse(const FString& InText, TArray<FWordResult>& Words) const
{
	TArray<FToken> tokens;
	if (!Parse(InText, tokens))
		return false;

	for (const auto& token : tokens)
	{
		if (token.Type == ETokenType::Word)
			Words.Push(token.Value);
	}

	return tokens.Num() == Words.Num();
}

void Tokenizer::TokenFromString(const FString& InText, TArray<FToken>& Tokens) const
{
	FString currentWord;
	for (auto ch : InText)
	{
		auto type = TokenTypeFromCharacter(ch);
		switch (type)
		{
		case ETokenType::Word:
			currentWord.AppendChar(ch);
			break;
		case ETokenType::BeginEither:
		case ETokenType::BeginOptional:
		{
			if (currentWord.Len() > 0)
			{
				FToken newWordToken = { ETokenType::Word, Vocabulary->LookupWord(currentWord) };
				Tokens.Add(newWordToken);
				currentWord.Empty();
			}
			FToken newBeginToken = { type, FWordResult::NoWord };
			newBeginToken.Type = type;
			Tokens.Add(newBeginToken);
			break;
		}
		case ETokenType::EndEither:
		case ETokenType::EndOptional:
		{
			if (currentWord.Len() > 0)
			{
				FToken newWordToken = { ETokenType::Word, Vocabulary->LookupWord(currentWord) };
				Tokens.Add(newWordToken);
				currentWord.Empty();
			}
			FToken newEndToken = { type, FWordResult::NoWord };
			Tokens.Add(newEndToken);
			break;
		}
		default:
		{
			FToken invalidToken = { ETokenType::Invalid, FWordResult::NoWord };
			Tokens.Add(invalidToken);
			break;
		}
		}
	}

	// trailing word
	if (currentWord.Len() > 0)
	{
		FToken newWordToken = { ETokenType::Word, Vocabulary->LookupWord(currentWord) };
		Tokens.Add(newWordToken);
	}

	return;
}

ETokenType Tokenizer::TokenTypeFromCharacter(TCHAR ch) const
{
	if (ch == TCHAR('('))
		return ETokenType::BeginEither;
	else if (ch == TCHAR(')'))
		return ETokenType::EndEither;
	else if (ch == TCHAR('['))
		return ETokenType::BeginOptional;
	else if (ch == TCHAR(']'))
		return ETokenType::EndOptional;
	else if (FChar::IsAlnum(ch))
		return ETokenType::Word;

	return ETokenType::Invalid;
}
