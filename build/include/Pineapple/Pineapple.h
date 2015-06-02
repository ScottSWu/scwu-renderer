#include <map>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILD_DLL
#define ADDAPI __declspec(dllexport)
#else
#define ADDAPI __declspec(dllimport)
#endif

typedef std::map<std::string, std::string> StringMap;

class ADDAPI Pineapple {
    protected:
        int width, height;
    public:
        Pineapple();
        Pineapple(const StringMap & options);

        int getWidth() { return width; };
        int getHeight() { return height; };
};

#ifdef __cplusplus
}
#endif
