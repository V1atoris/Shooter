// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (ShooterCharacter == nullptr)
	{
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}
	if (ShooterCharacter)
	{
		// Get the lateral speed of the character from velocity
		FVector Velocity{ ShooterCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		// Is the character in the air?
		bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

		// Is the character accelerating?
		if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

		FRotator AimRotation = ShooterCharacter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ShooterCharacter->GetVelocity());

		MovementOffSetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		if (bIsAccelerating)
		{
			LastMovementOffSetYaw = MovementOffSetYaw;
		}
		
		bAiming = ShooterCharacter->GetAiming();

		/*FString RotationMassage = FString::Printf(TEXT("Base Aim Rotetion: %f"), AimRotation.Yaw);*/
		
		
		/*FString MovementRotationMassage = FString::Printf(TEXT("Movement Rotation: %f"), MovementRotation.Yaw);*/

		/*FString OffsetMessege = FString::Printf(TEXT("Movement Offset Yaw: %f"), MovementOffSetYaw);*/
		
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, OffsetMessege);
		}
		*/

	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}

