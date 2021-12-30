// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
		//조준하는 방향의 각도값
		FRotator AimRotation = mShooterCharacter->GetBaseAimRotation();

		//움직이는 방향벡터(속도가 포함된). 에서 회전 각도만 가져옴
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(mShooterCharacter->GetVelocity());

		mMovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		if (GEngine)
		{
			//FString msg = FString::Printf(TEXT("x:%f,y:%f,z:%f"), mShooterCharacter->GetVelocity().X, mShooterCharacter->GetVelocity().Y, mShooterCharacter->GetVelocity().Z);
			FString msg = FString::Printf(TEXT("%f"), mMovementOffsetYaw);
			GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, msg);
		}

		
	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	mShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}
