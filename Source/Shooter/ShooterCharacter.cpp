// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
:mBaseTurnRate(45.f), mBaseLookUpRate(45.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("mCameraBoom"));
	mCameraBoom->SetupAttachment(RootComponent);
	mCameraBoom->TargetArmLength = 300.f;
	mCameraBoom->bUsePawnControlRotation = true;

	mFollowCamera = CreateDefaultSubobject <UCameraComponent>(TEXT("mFollowCamera"));
	mFollowCamera->SetupAttachment(mCameraBoom, USpringArmComponent::SocketName);
	mFollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*UE_LOG(LogTemp, Warning, TEXT("BeginPlay called"));
	int myint{ 42 };
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay called %d"), myint);

	FString fstrTemp{ TEXT("my string!!") };

	UE_LOG(LogTemp, Warning, TEXT("%s"), *fstrTemp);

	UE_LOG(LogTemp, Warning, TEXT("ThisName: %s"), *GetName());*/
}

void AShooterCharacter::MoveForward(float fValue)
{
	if (Controller != nullptr && fValue != 0.f)
	{
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		AddMovementInput(Direction, fValue);
	}
}

void AShooterCharacter::MoveRight(float fValue)
{
	if (Controller != nullptr && fValue != 0.f)
	{
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		AddMovementInput(Direction, fValue);
	}
}

void AShooterCharacter::TurnAtRate(float fValue)
{
	AddControllerYawInput(fValue * mBaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookUpAtRate(float fValue)
{
	AddControllerPitchInput(fValue * mBaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnRate", this, &AShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterCharacter::LookUpAtRate);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

