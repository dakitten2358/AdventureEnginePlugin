#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "AssetTypeActions_Base.h"
#include "WordGroups.h"
#include "Suffixes.h"
#include "Vocabulary.h"

class FMenuBuilder;

class FAssetTypeActions_WordGroups : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_WordGroups(uint32 AdventureCategoryID) : CategoryID(AdventureCategoryID) {}

	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions_Adventure", "AssetTypeActions_WordGroups", "Word Groups"); }
	virtual FColor GetTypeColor() const override { return FColor(128, 128, 64); }
	virtual UClass* GetSupportedClass() const override { return UWordGroups::StaticClass(); }
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return true; }
	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
	//virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override { return CategoryID; }

private:
	/** Can we execute a reimport for the selected objects? */
	bool CanExecuteReimport(const TArray<TWeakObjectPtr<UWordGroups>> Objects) const;

	/** Handler for when Reimport is selected */
	void ExecuteReimport(const TArray<TWeakObjectPtr<UWordGroups>> Objects) const;

	uint32 CategoryID;
};

class FAssetTypeActions_Suffixes : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_Suffixes(uint32 AdventureCategoryID) : CategoryID(AdventureCategoryID) {}

	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions_Adventure", "AssetTypeActions_Suffixes", "Suffixes"); }
	virtual FColor GetTypeColor() const override { return FColor(128, 128, 64); }
	virtual UClass* GetSupportedClass() const override { return USuffixes::StaticClass(); }
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return true; }
	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
	//virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override { return CategoryID; }

private:
	/** Can we execute a reimport for the selected objects? */
	bool CanExecuteReimport(const TArray<TWeakObjectPtr<USuffixes>> Objects) const;

	/** Handler for when Reimport is selected */
	void ExecuteReimport(const TArray<TWeakObjectPtr<USuffixes>> Objects) const;

	uint32 CategoryID;
};

class FAssetTypeActions_Vocabulary : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_Vocabulary(uint32 AdventureCategoryID) : CategoryID(AdventureCategoryID) {}

	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions_Adventure", "AssetTypeActions_Vocabulary", "Vocabulary"); }
	virtual FColor GetTypeColor() const override { return FColor(128, 128, 64); }
	virtual UClass* GetSupportedClass() const override { return UVocabulary::StaticClass(); }
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return true; }
	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
	//virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override { return CategoryID; }

private:

	uint32 CategoryID;


};
