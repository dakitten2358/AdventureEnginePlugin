// Fill out your copyright notice in the Description page of Project Settings.

#include "VocabularyFactory.h"
#include "Vocabulary.h"
#include "AssetTypeCategories.h"
#include "Engine/Engine.h"

UVocabularyFactory::UVocabularyFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	//Configure the class that this factory creates
	SupportedClass = UVocabulary::StaticClass();
}

UObject* UVocabularyFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	//Create the editor asset 
	UVocabulary* Vocabulary = NewObject<UVocabulary>(InParent, InClass, InName, Flags);
	return Vocabulary;
}