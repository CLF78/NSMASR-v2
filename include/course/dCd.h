#include <course/dCdFile.h>

class dCd_c {
    public:
        static dCd_c* m_instance;

        static dCdFile_c* getFileP(int areaId);
};
