// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FDuplicatorModule : public IModuleInterface, public FSelfRegisteringExec
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool Exec(UWorld* InWorld, const TCHAR* CMD, FOutputDevice& AR) override;

};
