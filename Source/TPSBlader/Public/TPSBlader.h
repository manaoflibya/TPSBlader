// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(TPSBlader, Log, All);
#define TPSLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define TPSLOG_S(Verbosity) UE_LOG(ActionRPG, Verbosity, TEXT("%s"), *RPGLOG_CALLINFO)
#define TPSLOG(Verbosity, Format, ...) UE_LOG(ActionRPG, Verbosity, TEXT("%s%s"), *RPGLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define TPSCHECK(Expr, ...) { if (!(Expr)) { RPGLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; } }