// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (mShooterCharacter == nullptr)
	{
		mShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}

	if (mShooterCharacter)
	{
		FVector velocity{ mShooterCharacter->GetVelocity() };
		velocity.Z = 0;
		mSpeed = velocity.Size();

		mbIsInAir = mShooterCharacter->GetCharacterMovement()->IsFalling();

		if (mShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			mbIsAccelerating = true;
		}
		else
		{
			mbIsAccelerating = false;
		}
	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	mShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}
