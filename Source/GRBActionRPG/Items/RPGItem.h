#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "RPGItem.generated.h"


/**
 * 所有Item资产的基类, 抽象基类,不可用于蓝图实例化.
 */
UCLASS(Abstract, BlueprintType)
class GRBACTIONRPG_API URPGItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Constructor */
	URPGItem()
		: Price(0)
		, MaxCount(1)
		, MaxLevel(1)
		, AbilityLevel(1)
	{}

	/** 核验本Item资产是否负担得起数量消耗; Returns if the item is consumable (MaxCount <= 0)*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Max")
		bool IsConsumable() const;

	/** Returns the logical name, equivalent to the primary asset id */
	UFUNCTION(BlueprintCallable, Category = "Item")
		FString GetIdentifierString() const;

	/** 拿取Item的 PrimaryAssetId */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

protected:
	/** Type of this item, set in native parent class */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
		FPrimaryAssetType ItemType;

	/** User-visible short name */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FText ItemName;

	/** User-visible long description */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FText ItemDescription;

	/** Icon to display */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FSlateBrush ItemIcon;

	/** Price in game */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		int32 Price;

	/** Maximum number of instances that can be in inventory at once, <= 0 means infinite */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Max")
		int32 MaxCount;

	/** Maximum level this item can be, <= 0 means infinite */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Max")
		int32 MaxLevel;

	/** Ability level this item grants. <= 0 means the character level */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
		int32 AbilityLevel;
};


