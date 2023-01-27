// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blader.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "BladerNotifyStateNomalAttack.generated.h"

class Blader;
/**
 * 
 */
UCLASS()
class TPSBLADER_API UBladerNotifyStateNomalAttack : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	ABlader* Blader;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
