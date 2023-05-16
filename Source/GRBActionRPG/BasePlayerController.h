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

	UFUNCTION()
		void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	UFUNCTION()
		void TouchMoved(ETouchIndex::Type FingerIndex, FVector Location);
	UFUNCTION()
		void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

private:
	FVector MoveInput;
	FVector TouchLocation;
	float BaseLookupRate;
	float BaseTurnRate;
};