// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backwards input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	* Called via input to turn at a given rate.
	* @param Rate  This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to look up/down at a given rate.
	* @param Rate  This is a normalized rate, i.e. 1.0 means 100% of desired rate
	*/
	void LookUpAtRate(float Rate);

	/**
	* Rotate controller based on mouse x movement
	* @param Value  The input value from mousemovement
	*/
	void Turn(float Value);

	/**
	* Rotate controller based on mouse y movement
	* @param Value  The input value from mousemovement
	*/
	void LookUp(float Value);


	/** Called when the Fire Button is pressed */
	void FireWeapon();

	//*** Renew FireWeapon
	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

	//*** Set bAiming to true or false with button pressed
	void AimingButtonPressed();
	void AimingButtonRelessed();

	void CameraInterpZoom(float DeltaTime);

	//*** Set Base Turn Rate and Base Look up rate based on aiming
	void SetLookRates();

	void CalculateCrosshairSpread(float DeltaTime);

	void StartCrosshairBulletFire();

	UFUNCTION()
	void FinishCrosshairBulletFire();

	//*** Set bAutomaticFire to true or false
	void FireButtonPressed();
	void FireButtonRelessed();

	void StartFireTimer();

	UFUNCTION()
	void AutoFireReset();

	//*** Line Trace for items under crosshairs
	bool TraceUnderCrosshairs(FHitResult& OutHitResult, FVector& OutHitLocation);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Camera that follows the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	//**Base turn rate, in deg / sec.Other scaling may affect final turn rate * /
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final turn rate */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float BaseLookUpRate;
	
	
	//*** Turn rate while not aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float HipTurnRate;
	//*** Look up rate while not aimng
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float HipLookUpRate;
	//*** Turn rate when aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float AimingTurnRate;
	//*** Look up rate when aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float AimingLookUpRate;
	//*** Scale factor for mouse look sensitivity Turn rate when not aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float MouseHipTurnRate;
	//*** Scale factor for mouse look sensitivity Look up rate when not aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float MouseHipLookUpRate;
	//*** Scale factor for mouse look sensitivity Turn rate when aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float MouseAimingTurnRate;
	//*** Scale factor for mouse look sensitivity Look up rate when aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float MouseAimingLookUpRate;

	//** Randomize Gunshot SoundCue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		class USoundCue* FireSound;

	//*** Flash spawned at BarrelSocket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* MuzzleFlash;

	//*** Montage for weapon firing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* HipFireMontage;

	//*** Particles spwaned up on bullet inpact
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		UParticleSystem* ImpactParticles;

	//***Smoke trail for bullets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		UParticleSystem* BeamParticles;

	//*** True when Aiming
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		bool bAiming;

	//*** Default camera field of view value
	float CameraDefaultFOV;

	//*** FOV value when zoomed in
	float CameraZoomedFOV;

	//** Current FOV this frame
	float CameraCurrentFOV;

	//*** Interp speed for zooming aiming
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float ZoomInterpSpeed;

	//*** Determines the spread of crosshairs 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairSpreadMultiplier;
	//*** Velocity component for crosshairs spread
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairVelocityFactor;
	//*** In Air component for crosshairs spread
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairInAirFactor;
	//*** Aim component for crosshairs spread
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairAimFactor;
	//*** Shooting component for crosshairs spread
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairShootingFactor;

	float ShootTimeDuration;
	bool bFiringBullet;
	FTimerHandle CrosshairShootTimer;

	//*** Left mouse button pressed
	bool bFireButtonPressed;

	//*** True when we can fire, false when waiting for timer
	bool bShouldFire;

	//*** Rate of automatic gun fire 
	float AutomaticFireRate;

	//*** Sets a timer between gunshots
	FTimerHandle AutoFireTimer;

	

public:


	/** Returns CameraBoom subobject */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject */
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool GetAiming() const { return bAiming; }

	UFUNCTION(BlueprintCallable)
	float GetCrosshairSpreadMultiplier() const;
};
