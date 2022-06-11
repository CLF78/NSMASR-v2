#ifdef __cplusplus
extern "C" {
#endif

void* memcpy(void* destination, const void* source, size_t size);
void* memset(void* ptr, int value, size_t num);

int strcmp(const char* str1, const char* str2);
char* strstr(char* str1, const char* str2);

#ifdef __cplusplus
}
#endif
