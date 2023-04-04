// Copyright Epic Games, Inc. All Rights Reserved.

#include "Duplicator.h"
#include "Editor.h"
#include "AssetRegistry/AssetRegistryModule.h"

#define LOCTEXT_NAMESPACE "FDuplicatorModule"

void FDuplicatorModule::StartupModule()
{
}

void FDuplicatorModule::ShutdownModule()
{
}

bool FDuplicatorModule::Exec(UWorld* InWorld, const TCHAR* CMD, FOutputDevice& AR)
{
	if (FParse::Command(&CMD, TEXT("Custom_Duplicate_Actor")))
	{
		TArray<FAssetData> AssetsData;
		GEditor->GetContentBrowserSelections(AssetsData);
		if (AssetsData.IsEmpty())
		{
			return false;
		}
		for (const FAssetData& AssetData : AssetsData)
		{
			UObject* Instance = AssetData.GetAsset();
			UClass* AssetClass = Instance->GetClass();

			if (!AssetClass->IsChildOf(UBlueprint::StaticClass()))
			{
				UE_LOG(LogTemp, Error, TEXT("My parent is not Actor"));
				continue;
			}

			AssetClass = Cast<UBlueprint>(Instance)->GeneratedClass;
			if (AssetClass->IsChildOf(AActor::StaticClass()))
			{
				UE_LOG(LogTemp, Error, TEXT("My parent is Actor"));
				UWorld* World = GEditor->GetEditorWorldContext().World();
				if (World->WorldType == EWorldType::Editor)
				{
					for (int i = 0; i < 5; ++i)
					{
						World->SpawnActor<AActor>(AssetClass, FVector(0, 0, 100), FRotator());
					}
				}
			}
		}
		return true;
	}
	return false;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDuplicatorModule, Duplicator)