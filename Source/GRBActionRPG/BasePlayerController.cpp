#include "BasePlayerController.h"
#include "GameFramework/Character.h"


ABasePlayerController::ABasePlayerController(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{
	TouchLocation = FVector::ZeroVector;
	BaseTurnRate = 8.f;
	BaseLookupRate = 4.f;
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	this->InputComponent->BindAxis(TEXT("MoveForward"), this, &ABasePlayerController::MoveForward);
	this->InputComponent->BindAxis(TEXT("MoveRight"), this, &ABasePlayerController::MoveRight);
	this->InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ABasePlayerController::TouchStarted);
	this->InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ABasePlayerController::TouchMoved);
	this->InputComponent->BindTouch(EInputEvent::IE_Released, this, &ABasePlayerController::TouchStopped);
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

void ABasePlayerController::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchLocation = Location;// 缓存一次press的起始位置
}

void ABasePlayerController::TouchMoved(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (TouchLocation.IsNearlyZero()) {
		return;
	}
	FVector Offset = Location - TouchLocation;// 两次差值
	ACharacter* InCharacter = this->GetCharacter();
	if (InCharacter == nullptr) {
		return;
	}
	float YawVal = Offset.X * BaseTurnRate * GetWorld()->GetDeltaSeconds();
	float PitchVal = Offset.Y * BaseLookupRate * GetWorld()->GetDeltaSeconds();
	this->AddYawInput(YawVal);
	this->AddPitchInput(PitchVal);

	TouchLocation = Location;// 缓存一次Drag位置
}

void ABasePlayerController::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchLocation = FVector::ZeroVector;// 复位缓存位置
}
