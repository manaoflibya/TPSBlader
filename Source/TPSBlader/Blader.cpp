// Fill out your copyright notice in the Description page of Project Settings.


#include "Blader.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
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


	bladerInfo = new BladerInfo();

	bladerInfo->attackCount = 0;
	bladerInfo->specialAttackCount = 0;

	bladerInfo->comboAttackAnimPlayRateTime = 1.0f;

	bladerInfo->firstAttackAnimPlayRateTime = 0.5f;
	bladerInfo->attackAnimPlayRateTime = 0.7f;
	bladerInfo->lastAttackAnimPlayRateTime = 1.3f;

	bladerInfo->dashPlayRateTime = 1.0f;
	bladerInfo->dashPlayAnimRateTime = 0.35f;
	bladerInfo->dashSpeed = 4500.0f;

	bladerInfo->isDuringAttack = false;
	bladerInfo->isDuringSpecialAttack = false;
	bladerInfo->isDuringDash = false;

	bladerWeaponInfo = new BladerWeaponInfo();
	
	bladerWeaponInfo->activeWeapon = false;

	LeftWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Weapon Collusion"));
	LeftWeaponCollision->SetupAttachment(GetMesh(), FName("LeftWeaponBone"));

	RightWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Weapon Collusion"));
	RightWeaponCollision->SetupAttachment(GetMesh(), FName("RightWeaponBone"));

}

void ABlader::BeginPlay()
{
	Super::BeginPlay();

	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LeftWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
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
	if (bladerInfo->isDuringAttack == true || bladerInfo->isDuringSpecialAttack == true)
	{
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, TEXT("is During Attack"));
		
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Character FName :: %s"), isDuringAttack ? TEXT("true") : TEXT("false"));

	if (bladerInfo->attackCount >= bladerInfo->attackCount)
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
				playRateTime = bladerInfo->lastAttackAnimPlayRateTime;

			}
		}
		break;
	}

	bladerInfo->isDuringAttack = true;
	GetWorldTimerManager().SetTimer(TH_Attack_End, this, &ABlader::Attack_End, playRateTime, false);
}

void ABlader::SpecialAttack()
{
	if (bladerInfo->isDuringAttack == true || bladerInfo->isDuringSpecialAttack == true)
	{
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, TEXT("is During Special Attack"));

		return;
	}

	
	if (bladerInfo->specialAttackCount >= bladerInfo->specialAttackCount)
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
	if (IsValid(Dash_AnimMontage) && !bladerInfo->isDuringDash)
	{
		const FVector ForwardDir = this->GetActorRotation().Vector();
		LaunchCharacter(ForwardDir * bladerInfo->dashSpeed, true, true);
		FTimerHandle timeHander;

		bladerInfo->isDuringDash = true;

		PlayAnimMontage(Dash_AnimMontage, bladerInfo->dashPlayRateTime);

		GetWorldTimerManager().SetTimer(timeHander, this, &ABlader::DashEnd, bladerInfo->dashPlayAnimRateTime, false);
	}
}

void ABlader::DashEnd()
{
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, TEXT("is Dash false"));

	bladerInfo->isDuringDash = false;
}

void ABlader::Attack_End()
{
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, TEXT("is Attack false"));
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


	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ABlader::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ABlader::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ABlader::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ABlader::LookUpAtRate);

}



void ABlader::MoveForward(float value)
{
	if ((Controller != nullptr) && (value != 0.0f) && !bladerInfo->isDuringAttack && !bladerInfo->isDuringSpecialAttack && !bladerInfo->isDuringDash)
	{
		//AttackCountInit();

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void ABlader::MoveRight(float value)
{
	if (((Controller != nullptr) && (value != 0.0f)) && !bladerInfo->isDuringAttack && !bladerInfo->isDuringSpecialAttack && !bladerInfo->isDuringDash)
	{
		//AttackCountInit();

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}