// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BladerCharacter.h"
#include "Blader.generated.h"

/**
 * 
 */
struct BladerInfo
{
public:
	int32 attackCount;
	int32 specialAttackCount;
	float attackAnimPlayRateTime;
	float firstAttackAnimPlayRateTime;
	float lastAttackAnimPlayRateTime;
	float comboAttackAnimPlayRateTime;
	float dashPlayRateTime;
	float bladerAttackSpeed;
	float dashSpeed;
	bool isDuringDash;
	bool isDuringAttack;
	bool isDuringSpecialAttack;
};

UENUM()
enum HeroAttackCount
{
	Attack_1 = 1,
	Attack_2 = 2,
	Attack_3 = 3,
	Attack_4 = 4,

};
UCLASS()
class TPSBLADER_API ABlader : public ABladerCharacter
{
	GENERATED_BODY()
	
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

public:
	ABlader();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:
	void MoveForward(float value);

	void MoveRight(float value);

	void TurnAtRate(float rate);

	void LookUpAtRate(float rate);

	void Attack();
	void SpecialAttack();

	void AttackCountInit();
	void SpecialAttackCountInit();

	void DashStart();
	void DashEnd();

	void Attack_End();
	void SpecialAttack_End();
private:
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Attack_AnimMontage_1;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Attack_AnimMontage_2;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Attack_AnimMontage_3;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Attack_AnimMontage_4;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Special_Attack_AnimMontage_1;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Special_Attack_AnimMontage_2;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Special_Attack_AnimMontage_3;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Special_Attack_AnimMontage_4;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Rolling_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* BeHit_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Death_AnimMontage;

	FVector GetTargetDirection();

private:
	BladerInfo* bladerInfo;
	int32 attackMaxCount;
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)override;
public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
