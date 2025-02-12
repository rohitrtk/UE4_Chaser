// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ChaserCharacter.generated.h"

UCLASS(config=Game)
class AChaserCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AChaserCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Players score **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int Score;

	/** Increments the players score by parameter increment
	 * @param increment   This is the increment to add to the players score
	**/
	FORCEINLINE void IncrementScore(const int32& increment) { this->Score += increment; }

	/* Sets the movement speed for the character based on current score */
	void SetMoveSpeed(const int32& score);

protected:

	/** The rate at which the zoom zoom's in/out **/
	const float ZoomScale = 50.f;

	/** Maximum zoom in the players camera arm can be **/
	const float MaxZoomIn = 300.f;

	/**  Maximum zoom out the players camera arm can be **/
	const float MaxZoomOut = 1400.f;

	/* Characters starting max move speed */
	const float StartingMoveSpeed = 600.f;

	/* Characters movement multiplier */
	const float MovementMultiplier = 25.f;

	/** Called via input action to zoom in **/
	void ZoomIn();

	/** Called via input action to zoom out**/
	void ZoomOut();
};

