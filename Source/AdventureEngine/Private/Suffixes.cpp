// Fill out your copyright notice in the Description page of Project Settings.

#include "Suffixes.h"

FArchive &operator <<(FArchive& Ar, FSuffix& Suffix)
{
	Ar << Suffix.InputString;
	Ar << Suffix.InputType;
	Ar << Suffix.OutputString;
	Ar << Suffix.OutputType;
	return Ar;
}

void USuffixes::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	Ar << suffixes;
}

void USuffixes::AddSuffix(const FString& InputString, WordClass InputType, const FString& OutputString, WordClass OutputType)
{
	FSuffix s;
	s.InputString = InputString;
	s.InputType = InputType;
	s.OutputString = OutputString;
	s.OutputType = OutputType;

	suffixes.Add(s);
}
