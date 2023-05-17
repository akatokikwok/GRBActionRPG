#pragma once
#include "UObject/PrimaryAssetId.h"
#include "RPGTypes.generated.h"

/**
 * 代表1个Item的插槽,可显示在UI内
 */
USTRUCT(BlueprintType)
struct GRBACTIONRPG_API FRPGItemSlot
{
	GENERATED_USTRUCT_BODY()
public:
	/** Constructor, -1 means an invalid slot */
	FRPGItemSlot()
		: SlotNumber(-1)
	{}

	FRPGItemSlot(const FPrimaryAssetType& InItemType, int32 InSlotNumber)
		: ItemType(InItemType)
		, SlotNumber(InSlotNumber)
	{}

	/** 物品的类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FPrimaryAssetType ItemType;

	/** 槽的索引号 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int32 SlotNumber;

	/** 重载操作符 */
	bool operator==(const FRPGItemSlot& Other) const
	{
		return ItemType == Other.ItemType && SlotNumber == Other.SlotNumber;
	}
	bool operator!=(const FRPGItemSlot& Other) const
	{
		return !(*this == Other);
	}

	/** 为了在诸如Map的容器内使用,所以设立1个哈希方法; Implemented so it can be used in Maps/Sets */
	friend inline uint32 GetTypeHash(const FRPGItemSlot& Key)
	{
		uint32 Hash = 0;
		Hash = HashCombine(Hash, GetTypeHash(Key.ItemType));
		Hash = HashCombine(Hash, (uint32)Key.SlotNumber);
		return Hash;
	}

	/** Returns true if slot is valid */
	bool IsValid() const
	{
		return ItemType.IsValid() && SlotNumber >= 0;
	}
};


/** Extra information about a URPGItem that is in a player's inventory */
USTRUCT(BlueprintType)
struct GRBACTIONRPG_API FRPGItemData
{
	GENERATED_USTRUCT_BODY()
public:
	/** Constructor, default to count/level 1 so declaring them in blueprints gives you the expected behavior */
	FRPGItemData()
		: ItemCount(1)
		, ItemLevel(1)
	{}

	FRPGItemData(int32 InItemCount, int32 InItemLevel)
		: ItemCount(InItemCount)
		, ItemLevel(InItemLevel)
	{}

	/** The number of instances of this item in the inventory, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int32 ItemCount;

	/** The level of this item. This level is shared for all instances, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int32 ItemLevel;

	/** Equality operators */
	bool operator==(const FRPGItemData& Other) const
	{
		return ItemCount == Other.ItemCount && ItemLevel == Other.ItemLevel;
	}
	bool operator!=(const FRPGItemData& Other) const
	{
		return !(*this == Other);
	}

	/** Returns true if count is greater than 0 */
	bool IsValid() const
	{
		return ItemCount > 0;
	}

	/** Append an item data, this adds the count and overrides everything else */
	void UpdateItemData(const FRPGItemData& Other, int32 MaxCount, int32 MaxLevel)
	{
		if (MaxCount <= 0) {
			MaxCount = MAX_int32;
		}

		if (MaxLevel <= 0) {
			MaxLevel = MAX_int32;
		}

		ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 1, MaxCount);
		ItemLevel = FMath::Clamp(Other.ItemLevel, 1, MaxLevel);
	}
};