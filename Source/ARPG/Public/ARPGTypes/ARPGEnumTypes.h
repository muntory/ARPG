#pragma once

UENUM()
enum class EARPGConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EARPGValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EARPGSuccessType : uint8
{
	Successful,
	Failed
};