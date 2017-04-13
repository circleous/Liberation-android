#include <mutex>
#include <vector>

#if defined(__i386__)
#  define PATCHSIZE 6
#elif defined(__aarch64__)
#  define PATCHSIZE 6
#elif defined(__arm__)
#  define PATCHSIZE 12
#endif

using bytes = std::vector<uint8_t>;

inline namespace Liberation
{
	
class Hook
{
public:
	static Hook *getInstance();
	void unhook();
	void hook(void *func, void *newaddr, void **origFunc);
	void doHook(void *func, void *newaddr, void **origFunc);
	void doUnHook(void *func, void *newaddr, void **origFunc);

protected:
	void safemepls(void *f, void *n, void **o);
	void *func; void *newAddr; void **origFunc;
	bytes _origBytes;

private:
	Hook();
	~Hook();
	static std::mutex lock;
	static bool instanceFlag;
	static Hook *instance;
};

} //Liberation