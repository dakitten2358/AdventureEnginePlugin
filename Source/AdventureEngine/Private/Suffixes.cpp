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

