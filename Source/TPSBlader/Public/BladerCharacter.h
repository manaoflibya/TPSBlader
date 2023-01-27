// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BladerCharacter.generated.h"

UCLASS()
class TPSBLADER_API ABladerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABladerCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float maxHealth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

	void DeathAnimationEnd();

	void RotateTo(FVector TargetDir);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//UPROPERTY(EditDefaultsOnly, Category = Pawn)
	//	UAnimMontage* Attack_AnimMontage;

	//UPROPERTY(EditDefaultsOnly, Category = Pawn)
	//	UAnimMontage* BeHit_AnimMontage;

	//UPROPERTY(EditDefaultsOnly, Category = Pawn)
	//	UAnimMontage* Death_AnimMontage;

	void Attack_Melee();
	void Attack_Melee_End();
	void ShowFX();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;

	bool isDuringAttack = true;
	int32 ComboAttack_Num;

	UPROPERTY(EditDefaultsOnly, Category = "MyFX")
		UParticleSystem* HitFX;

};
