#include "BasePlayerController.h"
#include "GameFramework/Character.h"


ABasePlayerController::ABasePlayerController(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{

}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	this->InputComponent->BindAxis(TEXT("MoveForward"), this, &ABasePlayerController::MoveForward);
	this->InputComponent->BindAxis(TEXT("MoveRight"), this, &ABasePlayerController::MoveRight);
}

void ABasePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (this->MoveInput.IsNearlyZero()) {
		return;
	}

	const FRotator Rot = this->GetControlRotation();
	const FRotator YawRot(0, Rot.Yaw, 0);// YawRot就是控制器yaw的欧拉角
	ACharacter* InCharacter = this->GetCharacter();
	if (InCharacter == nullptr) {
		return;
	}
	const FVector DirX = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	InCharacter->AddMovementInput(DirX, MoveInput.X);
	const FVector DirY = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
	InCharacter->AddMovementInput(DirY, MoveInput.Y);
}

void ABasePlayerController::MoveForward(float Value)
{
	this->MoveInput.X = Value;
}

void ABasePlayerController::MoveRight(float Value)
{
	this->MoveInput.Y = Value;
}
