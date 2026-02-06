#pragma once

#include "Core/Log.h"

#if !defined(UE_BUILD_SHIPPING) || defined(WITH_EDITOR)
#define PW_ASSERT(condition, category, ...) if (!ensureMsgf(condition, __VA_ARGS__)) { PW_LOG_ERROR(category, __VA_ARGS__); }
#else
#define PW_ASSERT(condition, category, ...)
#endif