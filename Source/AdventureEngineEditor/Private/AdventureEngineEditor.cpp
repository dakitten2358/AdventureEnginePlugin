// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AdventureEngineEditor.h"
#include "AssetToolsModule.h"
#include "AdventureAssetTypeActions.h"
#include "SharedPointer.h"

#define LOCTEXT_NAMESPACE "FAdventureEngineEditorModule"

void FAdventureEngineEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	RegisterAssetTools();
}

void FAdventureEngineEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UnregisterAssetTools();
}

void FAdventureEngineEditorModule::RegisterAssetTools()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	AdventureAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName("AdventureEngine"), LOCTEXT("AdventureEngineCategory", "Adventure Engine"));

	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_WordGroups(AdventureAssetCategoryBit)));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_Suffixes(AdventureAssetCategoryBit)));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_Vocabulary(AdventureAssetCategoryBit)));
}

void FAdventureEngineEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	RegisteredAssetTypeActions.Add(Action);
}

void FAdventureEngineEditorModule::UnregisterAssetTools()
{
	FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");

	if (AssetToolsModule != nullptr)
	{
		IAssetTools& AssetTools = AssetToolsModule->Get();

		for (auto Action : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAdventureEngineEditorModule, AdventureEngineEditor)