#include "AdventureAssetTypeActions.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "EditorStyleSet.h"
#include "EditorReimportHandler.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_Adventure"

void FAssetTypeActions_WordGroups::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	auto WordGroupDefinitions = GetTypedWeakObjectPtrs<UWordGroups>(InObjects);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("ReimportWordGroupsLabel", "Reimport"),
		LOCTEXT("ReimportWordGroupsTooltip", "Reimport the selected word group definition(s)."),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "ContentBrowser.AssetActions.ReimportAsset"),
		FUIAction(
			FExecuteAction::CreateSP(this, &FAssetTypeActions_WordGroups::ExecuteReimport, WordGroupDefinitions),
			FCanExecuteAction::CreateSP(this, &FAssetTypeActions_WordGroups::CanExecuteReimport, WordGroupDefinitions)
		)
	);
}

bool FAssetTypeActions_WordGroups::CanExecuteReimport(const TArray<TWeakObjectPtr<UWordGroups>> Objects) const
{
	for (auto ObjIt = Objects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Object = (*ObjIt).Get();
		if (Object)
		{
			// check for caching type?
			return true;
		}
	}

	return false;
}

void FAssetTypeActions_WordGroups::ExecuteReimport(const TArray<TWeakObjectPtr<UWordGroups>> Objects) const
{
	for (auto ObjIt = Objects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Object = (*ObjIt).Get();
		if (Object)
		{
			// It's OK to ask for a new file
			FReimportManager::Instance()->Reimport(Object, /*bAskForNewFileIfMissing=*/true);
		}
	}
}

void FAssetTypeActions_Suffixes::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	auto Suffixes = GetTypedWeakObjectPtrs<USuffixes>(InObjects);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("ReimportWordGroupsLabel", "Reimport"),
		LOCTEXT("ReimportWordGroupsTooltip", "Reimport the selected word group definition(s)."),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "ContentBrowser.AssetActions.ReimportAsset"),
		FUIAction(
			FExecuteAction::CreateSP(this, &FAssetTypeActions_Suffixes::ExecuteReimport, Suffixes),
			FCanExecuteAction::CreateSP(this, &FAssetTypeActions_Suffixes::CanExecuteReimport, Suffixes)
		)
	);
}

bool FAssetTypeActions_Suffixes::CanExecuteReimport(const TArray<TWeakObjectPtr<USuffixes>> Objects) const
{
	for (auto ObjIt = Objects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Object = (*ObjIt).Get();
		if (Object)
		{
			// check for caching type?
			return true;
		}
	}

	return false;
}

void FAssetTypeActions_Suffixes::ExecuteReimport(const TArray<TWeakObjectPtr<USuffixes>> Objects) const
{
	for (auto ObjIt = Objects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Object = (*ObjIt).Get();
		if (Object)
		{
			// It's OK to ask for a new file
			FReimportManager::Instance()->Reimport(Object, /*bAskForNewFileIfMissing=*/true);
		}
	}
}

#undef LOCTEXT_NAMESPACE