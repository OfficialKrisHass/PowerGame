#pragma once

#if !defined(UE_BUILD_SHIPPING) || defined(WITH_EDITOR)
#define _PW_LOG(category, severity, color, ...) UE_LOG(category, severity, __VA_ARGS__);\
												if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, color, FString::Printf(#category ": " __VA_ARGS__));
#else
#define _PW_LOG(category, severity, color, ...)
#endif

#define PW_LOG(category, ...) _PW_LOG(category, Display, FColor::White, __VA_ARGS__)
#define PW_LOG_WARN(category, ...) _PW_LOG(category, Warning, FColor::Yellow, __VA_ARGS__)
#define PW_LOG_ERROR(category, ...) _PW_LOG(category, Error, FColor::Red, __VA_ARGS__)