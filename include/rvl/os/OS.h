// Source: RVL SDK
#ifdef __cplusplus
extern "C" {
#endif

// Round API
#define OSRoundUp32B(x) (((u32)(x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((u32)(x)) & ~(32 - 1))

// Interrupt API
s32 OSDisableInterrupts();
s32 OSEnableInterrupts();

// Debug API
void OSReport(const char* msg, ...);

#ifdef __cplusplus
}
#endif
