// Fill out your copyright notice in the Description page of Project Settings.


#include "BladerNotifyStateNomalAttack.h"

void UBladerNotifyStateNomalAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		Blader = Cast<ABlader>(MeshComp->GetOwner());
		if (Blader)
		{
			Blader->ActivateWeapon();
		}
	}
}

void UBladerNotifyStateNomalAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		Blader = Cast<ABlader>(MeshComp->GetOwner());

		if (Blader)
		{
			Blader->DeactivateWeapon();
		}
	}
}
