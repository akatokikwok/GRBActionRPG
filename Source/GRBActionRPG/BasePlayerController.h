#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"


/**
 *
 */
UCLASS()
class GRBACTIONRPG_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	/** Default Constructor */
	ABasePlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

protected:
	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

private:
	FVector MoveInput;
};