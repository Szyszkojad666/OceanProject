#pragma once
#include "Engine\DataTable.h"
#include "StructsAndEnums.generated.h"

USTRUCT(BlueprintType)
struct FBoatInfo : public FTableRowBase
{
	FName Name;

};