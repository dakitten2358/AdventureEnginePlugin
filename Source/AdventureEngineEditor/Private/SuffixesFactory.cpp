// Fill out your copyright notice in the Description page of Project Settings.

#include "SuffixesFactory.h"
#include "Suffixes.h"
#include "XmlParser/Public/FastXml.h"
#include "XmlParser/Public/XmlFile.h"
#include "XmlParser/Public/XmlNode.h"
#include "Paths.h"
#include "Editor.h"
#include "WordClasses.h"


USuffixesFactory::USuffixesFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = false;
	bEditAfterNew = true;
	bEditorImport = true;
	bText = true;
	SupportedClass = USuffixes::StaticClass();

	Formats.Add("suffix;Adventure Suffix File");
}

UObject* USuffixesFactory::FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn)
{
	FEditorDelegates::OnAssetPreImport.Broadcast(this, InClass, InParent, InName, Type);

	auto suffixes = NewObject<USuffixes>(InParent, InClass, InName, Flags);
	suffixes->SourceFilename = GetCurrentFilename();

	FXmlFile xmlFile(GetCurrentFilename());
	FXmlNode* rootNode = xmlFile.GetRootNode();
	auto childNodes = rootNode->GetChildrenNodes();
	for (auto childNode : childNodes)
	{
		auto inputString = childNode->GetAttribute("InputString");
		auto inputType = (WordClass)(FCString::Atoi(*(childNode->GetAttribute("InputType"))) << 4);
		auto outputString = childNode->GetAttribute("OutputString");
		auto outputType = inputType;
		if (!childNode->GetAttribute("OutputType").IsEmpty())
		{
			outputType = (WordClass)(FCString::Atoi(*(childNode->GetAttribute("OutputType"))) << 4);
		}

		// strip off the * from the strings
		if (inputString.StartsWith(TEXT("*")))
			inputString = inputString.RightChop(1);
		if (outputString.StartsWith(TEXT("*")))
			outputString = outputString.RightChop(1);

		suffixes->AddSuffix(inputString, inputType, outputString, outputType);
	}

	FEditorDelegates::OnAssetPostImport.Broadcast(this, suffixes);

	return suffixes;
}

bool USuffixesFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	USuffixes* suffixesToReimport = Cast<USuffixes>(Obj);
	if (suffixesToReimport)
	{
		OutFilenames.Add(suffixesToReimport->SourceFilename);
		return true;
	}
	return false;
}

void USuffixesFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
	USuffixes* suffixesToReimport = Cast<USuffixes>(Obj);
	if (suffixesToReimport && ensure(NewReimportPaths.Num() == 1))
	{
		suffixesToReimport->SourceFilename = NewReimportPaths[0];
	}
}

EReimportResult::Type USuffixesFactory::Reimport(UObject* InObject)
{
	USuffixes* suffixesToReimport = Cast<USuffixes>(InObject);

	if (!suffixesToReimport)
	{
		return EReimportResult::Failed;
	}

	if (suffixesToReimport->SourceFilename.IsEmpty() || !FPaths::FileExists(suffixesToReimport->SourceFilename))
	{
		return EReimportResult::Failed;
	}

	bool OutCanceled = false;
	if (ImportObject(InObject->GetClass(), InObject->GetOuter(), *InObject->GetName(), RF_Public | RF_Standalone, suffixesToReimport->SourceFilename, nullptr, OutCanceled))
	{
		return EReimportResult::Succeeded;
	}

	return EReimportResult::Failed;
}
