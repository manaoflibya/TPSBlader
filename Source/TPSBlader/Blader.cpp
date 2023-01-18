// Fill out your copyright notice in the Description page of Project Settings.


#include "Blader.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"


ABlader::ABlader()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 800.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	attackMaxCount = 4;

	bladerInfo = new BladerInfo();
	bladerInfo->attackCount = 0;
	bladerInfo->specialAttackCount = 0;
	bladerInfo->firstAttackAnimPlayRateTime = 0.5f;
	bladerInfo->attackAnimPlayRateTime = 0.7f;
	bladerInfo->lastAttackAnimPlayRateTime = 1.2f;
	bladerInfo->comboAttackAnimPlayRateTime = 1.0f;
	bladerInfo->dashPlayRateTime = 1.0f;
	bladerInfo->isDuringAttack = false;
	bladerInfo->isDuringSpecialAttack = false;
	bladerInfo->isDuringDash = false;
	bladerInfo->isDuringSpecialAttack = false;
	bladerInfo->bladerAttackSpeed = 0.4;
	bladerInfo->dashSpeed = 3000.0f;
}

void ABlader::MoveForward(float value)
{
	if ((Controller != nullptr) && (value != 0.0f) && !bladerInfo->isDuringAttack && !bladerInfo->isDuringSpecialAttack)
	{
		AttackCountInit();

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void ABlader::MoveRight(float value)
{
	if ((Controller != nullptr) && (value != 0.0f) && !bladerInfo->isDuringAttack && !bladerInfo->isDuringSpecialAttack)
	{
		AttackCountInit();

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void ABlader::TurnAtRate(float rate)
{
	AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABlader::LookUpAtRate(float rate)
{
	AddControllerPitchInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABlader::Attack()
{
	if (bladerInfo->isDuringAttack == true && bladerInfo->isDuringSpecialAttack == true)
	{
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, TEXT("is During Attack"));

		return;
	}

	if (bladerInfo->attackCount >= attackMaxCount)
	{
		bladerInfo->attackCount = 0;
	}

	bladerInfo->attackCount++;
	FTimerHandle TH_Attack_End;
	float playRateTime = 0.0f;

	switch (bladerInfo->attackCount)
	{
	case Attack_1:
	{
		if (IsValid(Attack_AnimMontage_1))
		{
			PlayAnimMontage(Attack_AnimMontage_1, bladerInfo->comboAttackAnimPlayRateTime);
			playRateTime = bladerInfo->firstAttackAnimPlayRateTime;
		}
	}
	break;
	case Attack_2:
	{
		if (IsValid(Attack_AnimMontage_2))
		{
			PlayAnimMontage(Attack_AnimMontage_2, bladerInfo->comboAttackAnimPlayRateTime);
			playRateTime = bladerInfo->attackAnimPlayRateTime;

		}
	}
	break;
	case Attack_3:
	{
		if (IsValid(Attack_AnimMontage_3))
		{
			PlayAnimMontage(Attack_AnimMontage_3, bladerInfo->comboAttackAnimPlayRateTime);
			playRateTime = bladerInfo->attackAnimPlayRateTime;

		}
	}
	break;
	case Attack_4:
	{
		if (IsValid(Attack_AnimMontage_4))
		{
			PlayAnimMontage(Attack_AnimMontage_4, bladerInfo->comboAttackAnimPlayRateTime);
			playRateTime = bladerInfo->lastAttackAnimPlayRateTime;

		}
		break;
	default:
	{
		playRateTime = 12;
	}
	break;
	}
	}

	bladerInfo->isDuringAttack = true;
	GetWorldTimerManager().SetTimer(TH_Attack_End, this, &ABlader::Attack_End, playRateTime, false);
}

void ABlader::SpecialAttack()
{
	if (bladerInfo->isDuringAttack == true && bladerInfo->isDuringSpecialAttack == true)
	{
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, TEXT("is During Special Attack"));

		return;
	}

	if (bladerInfo->specialAttackCount >= attackMaxCount)
	{
		bladerInfo->specialAttackCount = 0;
	}

	bladerInfo->specialAttackCount++;
	FTimerHandle TH_Attack_End;
	float playRateTime = 0.0f;

	switch (bladerInfo->specialAttackCount)
	{
	case Attack_1:
	{
		if (IsValid(Attack_AnimMontage_1))
		{
			PlayAnimMontage(Special_Attack_AnimMontage_1, bladerInfo->comboAttackAnimPlayRateTime);
			playRateTime = bladerInfo->firstAttackAnimPlayRateTime;
		}
	}
	break;
	case Attack_2:
	{
		if (IsValid(Attack_AnimMontage_2))
		{
			PlayAnimMontage(Special_Attack_AnimMontage_2, bladerInfo->comboAttackAnimPlayRateTime);
			playRateTime = bladerInfo->attackAnimPlayRateTime;

		}
	}
	break;
	case Attack_3:
	{
		if (IsValid(Attack_AnimMontage_3))
		{
			PlayAnimMontage(Special_Attack_AnimMontage_3, bladerInfo->comboAttackAnimPlayRateTime);
			playRateTime = bladerInfo->attackAnimPlayRateTime;

		}
	}
	break;
	case Attack_4:
	{
		if (IsValid(Attack_AnimMontage_4))
		{
			PlayAnimMontage(Special_Attack_AnimMontage_4, bladerInfo->comboAttackAnimPlayRateTime);
			playRateTime = bladerInfo->lastAttackAnimPlayRateTime;

		}
		break;
	default:
	{
		playRateTime = 12;
	}
	break;
	}
	}

	bladerInfo->isDuringSpecialAttack = true;
	GetWorldTimerManager().SetTimer(TH_Attack_End, this, &ABlader::SpecialAttack_End, playRateTime, false);

}

void ABlader::AttackCountInit()
{
	bladerInfo->attackCount = 0;
}

void ABlader::SpecialAttackCountInit()
{
	bladerInfo->specialAttackCount = 0;
}

void ABlader::DashStart()
{
	const FVector ForwardDir = this->GetActorRotation().Vector();
	LaunchCharacter(ForwardDir * bladerInfo->dashSpeed, true, true);

	if (IsValid(Rolling_AnimMontage))
	{
		bladerInfo->isDuringDash = true;

		PlayAnimMontage(Rolling_AnimMontage, bladerInfo->dashPlayRateTime);
	}

}

void ABlader::DashEnd()
{
	bladerInfo->isDuringDash = false;
}

void ABlader::Attack_End()
{
	bladerInfo->isDuringAttack = false;
}

void ABlader::SpecialAttack_End()
{
	bladerInfo->isDuringSpecialAttack = false;
}

FVector ABlader::GetTargetDirection()
{
	FVector ForwardVector = FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y);
	FVector TargetDir = FVector::ZeroVector;

	// change
	TargetDir = GetActorForwardVector();
	TargetDir.Normalize();

	return TargetDir;
}

void ABlader::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABlader::Attack);
	PlayerInputComponent->BindAction("SpecialAttack", IE_Pressed, this, &ABlader::SpecialAttack);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ABlader::DashStart);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABlader::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABlader::MoveRight);

	//추가 해야함
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABlader::TurnAtRate);
	//추가 해야함
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABlader::LookUpAtRate);

}
