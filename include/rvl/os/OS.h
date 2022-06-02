// Source: RVL SDK
#ifdef __cplusplus
extern "C" {
#endif

#define OSRoundUp32B(x) (((u32)(x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((u32)(x)) & ~(32 - 1))

void OSReport(const char* msg, ...);

#ifdef __cplusplus
}
#endif
