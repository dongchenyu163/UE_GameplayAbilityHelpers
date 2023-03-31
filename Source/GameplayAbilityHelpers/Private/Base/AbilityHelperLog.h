#pragma once

#pragma region Log类定义区域
DECLARE_LOG_CATEGORY_EXTERN(LogAbilityHelperLog, Log, All); // This should be at Header file.
// 可自己指定Verbosity的版本
#define ULOG_ABILITYHELPERLOG(Verbosity, FormatString, ...) \
    UE_LOG(LogAbilityHelperLog, Verbosity, TEXT("Funtion: [%s]; "##FormatString##), ANSI_TO_TCHAR(__FUNCTION__), ##__VA_ARGS__)
// Verbosity为Display的版本
#define ULOG_ABILITYHELPERLOG_NORM(FormatString, ...)\
	UE_LOG(LogAbilityHelperLog, Display, TEXT("Funtion: [%s]; "##FormatString##), ANSI_TO_TCHAR(__FUNCTION__), ##__VA_ARGS__)
// Verbosity为Display的版本
#define ULOG_ABILITYHELPERLOG_WRN(FormatString, ...)\
	UE_LOG(LogAbilityHelperLog, Warning, TEXT("Funtion: [%s]; "##FormatString##), ANSI_TO_TCHAR(__FUNCTION__), ##__VA_ARGS__)
// Verbosity为Display的版本
#define ULOG_ABILITYHELPERLOG_ERR(FormatString, ...)\
	UE_LOG(LogAbilityHelperLog, Error, TEXT("Funtion: [%s]; "##FormatString##), ANSI_TO_TCHAR(__FUNCTION__), ##__VA_ARGS__)
// 限定ULOG_ABILITYHELPERLOG的定义的范围。
// #undef ULOG_ABILITYHELPERLOG

#pragma region 条件Log定义区域
// 条件Log的主定义
// 完全自定义条件
#define UCLOG_ABILITYHELPERLOG_COND_CUSTOM(Condition, Verbosity, FormatString, ...)\
	UE_CLOG(Condition, LogAbilityHelperLog, Verbosity, TEXT("Funtion: [%s]; "##FormatString##), ANSI_TO_TCHAR(__FUNCTION__), ##__VA_ARGS__)
// Flag控制Log的条件，自定义Verbosity的版本
#define UCLOG_ABILITYHELPERLOG(MatchedCondition, Verbosity, FormatString, ...)\
	UE_CLOG((LOG_ABILITYHELPERLOG_CONDITION_VAR & (##MatchedCondition##)) != 0, LogAbilityHelperLog, Verbosity, TEXT("Funtion: [%s]; "##FormatString##), ANSI_TO_TCHAR(__FUNCTION__), ##__VA_ARGS__)
// Flag控制Log的条件，Verbosity为Display的版本
#define UCLOG_ABILITYHELPERLOG_NORM(MatchedCondition, FormatString, ...)\
	UE_CLOG((LOG_ABILITYHELPERLOG_CONDITION_VAR & (##MatchedCondition##)) != 0, LogAbilityHelperLog, Display, TEXT("Funtion: [%s]; "##FormatString##), ANSI_TO_TCHAR(__FUNCTION__), ##__VA_ARGS__)
// Flag控制Log的条件，Verbosity为Warning的版本
#define UCLOG_ABILITYHELPERLOG_WRN(MatchedCondition, FormatString, ...)\
	UE_CLOG((LOG_ABILITYHELPERLOG_CONDITION_VAR & (##MatchedCondition##)) != 0, LogAbilityHelperLog, Warning, TEXT("Funtion: [%s]; "##FormatString##), ANSI_TO_TCHAR(__FUNCTION__), ##__VA_ARGS__)
// Flag控制Log的条件，Verbosity为Error的版本
#define UCLOG_ABILITYHELPERLOG_ERR(MatchedCondition, FormatString, ...)\
	UE_CLOG((LOG_ABILITYHELPERLOG_CONDITION_VAR & (##MatchedCondition##)) != 0, LogAbilityHelperLog, Error, TEXT("Funtion: [%s]; "##FormatString##), ANSI_TO_TCHAR(__FUNCTION__), ##__VA_ARGS__)

// 条件的定义，以Flag的形式开启或关闭某个Log
constexpr uint_fast64_t __LOG_ABILITYHELPERLOG_AUTOCOUNTER_START__ = __COUNTER__ + 1; // 加1 是为了消除本句的影响（只要使用就会自增1）
// 自定义该Flag的Bit位置（注意不要和自动的产生冲突）。
#define __DEFINE_LOG_ABILITYHELPERLOG_CONDITION_CUSTOM_POS(FLAG_NAME, BIT_POSITION) constexpr uint_fast64_t LOG_ABILITYHELPERLOG_##FLAG_NAME## = 1 << ##BIT_POSITION
#define __DEFINE_LOG_ABILITYHELPERLOG_CONDITION(FLAG_NAME) constexpr uint_fast64_t LOG_ABILITYHELPERLOG_##FLAG_NAME## = 1 << (__COUNTER__ - __LOG_ABILITYHELPERLOG_AUTOCOUNTER_START__)

// 需要根据自己的Log需求来定义会使用的Log的Flag 
__DEFINE_LOG_ABILITYHELPERLOG_CONDITION(TEMP);

// 判断Log条件的全局变量
static uint_fast64_t LOG_ABILITYHELPERLOG_CONDITION_VAR =
	LOG_ABILITYHELPERLOG_TEMP |
	0; // 本行只是为了方便注释掉上面任意行，而不报编译错误。

#pragma endregion 条件Log定义区域
#pragma endregion Log类定义区域

