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
	int32 attackMaxCount;
	int32 specialAttackCount;
	int32 specialAttackMaxCount;
	float attackAnimPlayRateTime;
	float firstAttackAnimPlayRateTime;
	float lastAttackAnimPlayRateTime;
	float comboAttackAnimPlayRateTime;
	float dashPlayRateTime;
	float dashPlayAnimRateTime;
	float bladerAttackSpeed;
	float dashSpeed;
	bool isDuringDash;
	bool isDuringAttack;
	bool isDuringSpecialAttack;
};

struct BladerWeaponInfo
{
public:
	bool activeWeapon;
};

UENUM()
enum HeroAttackCount
{
	Attack_1 = 1,
	Attack_2 = 2,
	Attack_3 = 3,
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

	virtual void ActivateWeapon();
	virtual void DeactivateWeapon();

protected:
	void MoveForward(float value);

	void MoveRight(float value);

	void TurnAtRate(float rate);

	void LookUpAtRate(float rate);

	void Attack();
	void Attack_End();
	void SpecialAttack();
	void SpecialAttack_End();

	void AttackCountInit();
	void SpecialAttackCountInit();

	void DashStart();
	void DashEnd();

	void DamageEvent(float DamageAmount,FDamageEvent const& DamageEvent, AController* EventIstigator, AActor* DamageCauser);
	void LightHit();
	void LargeHit();

	void Death();

protected:
	UFUNCTION()
		void OnWeaponOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor * OtherActor,
			UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex,
			bool bFromSweep, 
			const FHitResult& SweepResult);

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
		UAnimMontage* Dash_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* LargeHit_F_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* LightHit_F_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Death_AnimMontage;

	FVector GetTargetDirection();

private:
	BladerInfo* bladerInfo;
	BladerWeaponInfo* bladerWeaponInfo;
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)override;
	virtual void BeginPlay();
public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Left Weapon Collusion")
		class UBoxComponent* LeftWeaponCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Right Weapon Collusion")
		class UBoxComponent* RightWeaponCollision;

};
