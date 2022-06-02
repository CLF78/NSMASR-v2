namespace nw4r {
namespace ut {
namespace detail {

inline void Lock(OSMutex& mutex) {
    OSLockMutex(&mutex);
}

inline void Unlock(OSMutex& mutex) {
    OSUnlockMutex(&mutex);
}

template<typename Type>
class AutoLock {
    public:
        AutoLock(Type& lockObj) : mLockObj(lockObj) {
            Lock(lockObj);
        }

        ~AutoLock() {
            Unlock(mLockObj);
        }

        Type& mLockObj;
};

} // namespace detail
} // namespace ut
} // namespace nw4r
