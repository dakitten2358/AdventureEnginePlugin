// Fill out your copyright notice in the Description page of Project Settings.

#include "WordGroupsFactory.h"
#include "WordGroups.h"
#include "XmlParser/Public/FastXml.h"
#include "XmlParser/Public/XmlFile.h"
#include "XmlParser/Public/XmlNode.h"
#include "Paths.h"
#include "Editor.h"
#include "WordClasses.h"


UWordGroupsFactory::UWordGroupsFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = false;
	bEditAfterNew = true;
	bEditorImport = true;
	bText = true;
	SupportedClass = UWordGroups::StaticClass();

	Formats.Add("vocab;Adventure Vocabulary File");
}


UObject* UWordGroupsFactory::FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn)
{
	FEditorDelegates::OnAssetPreImport.Broadcast(this, InClass, InParent, InName, Type);

	auto vocab = NewObject<UWordGroups>(InParent, InClass, InName, Flags);
	vocab->SourceFilename = GetCurrentFilename();

	FXmlFile xmlFile(GetCurrentFilename());
	FXmlNode* rootNode = xmlFile.GetRootNode();
	auto childNodes = rootNode->GetChildrenNodes();
	for (auto childNode : childNodes)
	{
		auto id = FCString::Atoi(*(childNode->GetAttribute("ID")));
		auto type = (WordClass)FCString::Atoi(*(childNode->GetAttribute("Type")));
		auto content = childNode->GetContent();

		TArray<FString> words;
		content.ParseIntoArray(words, TEXT(","));
		vocab->AddWordGroup(id, type, words);
	}

	FEditorDelegates::OnAssetPostImport.Broadcast(this, vocab);

	return vocab;
}

bool UWordGroupsFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	UWordGroups* wordGroupsToReimport = Cast<UWordGroups>(Obj);
	if (wordGroupsToReimport)
	{
		OutFilenames.Add(wordGroupsToReimport->SourceFilename);
		return true;
	}
	return false;
}

void UWordGroupsFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
	UWordGroups* wordGroupsToReimport = Cast<UWordGroups>(Obj);
	if (wordGroupsToReimport && ensure(NewReimportPaths.Num() == 1))
	{
		wordGroupsToReimport->SourceFilename = NewReimportPaths[0];
	}
}

EReimportResult::Type UWordGroupsFactory::Reimport(UObject* InObject)
{
	UWordGroups* wordGroupsToReimport = Cast<UWordGroups>(InObject);

	if (!wordGroupsToReimport)
	{
		return EReimportResult::Failed;
	}

	if (wordGroupsToReimport->SourceFilename.IsEmpty() || !FPaths::FileExists(wordGroupsToReimport->SourceFilename))
	{
		return EReimportResult::Failed;
	}

	bool OutCanceled = false;
	if (ImportObject(InObject->GetClass(), InObject->GetOuter(), *InObject->GetName(), RF_Public | RF_Standalone, wordGroupsToReimport->SourceFilename, nullptr, OutCanceled))
	{
		return EReimportResult::Succeeded;
	}

	return EReimportResult::Failed;
}
