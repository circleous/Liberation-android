#include "Hook.h"
#include "Memory.h"

inline namespace Liberation
{

Hook *Hook::instance = nullptr;
bool Hook::instanceFlag = false;
std::mutex Hook::lock;

Hook::Hook()
{
}

Hook::~Hook()
{
	instanceFlag = false;
}

Hook *Hook::getInstance()
{
	if (!instanceFlag) {
		std::lock_guard<std::mutex> l(lock);
		instance = new Hook();
		instanceFlag = true;
		return instance;
	}
	else {
		return instance;
	}
}

void Hook::hook(void *f, void *n, void **o)
{
	safemepls(f, n, o);
	doHook(f, n, o);
}

void Hook::unhook()
{
	doUnHook(func, newAddr, origFunc);
}

void Hook::doHook(void *func, void *newAddr, void **origFunc)
{
	// Trampoline
	void *trampoline = 
	mmap( *origFunc, sysconf(_SC_PAGESIZE), PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);	

	char *trampoline_inst = (char*)trampoline;

#if defined(__i386__)
	memcpy(trampoline_inst, _origBytes.data(), PATCHSIZE);
	trampoline_inst[PATCHSIZE] = 0x68; // push
	*(unsigned long*)&trampoline_inst[PATCHSIZE+1] = (unsigned long)func+PATCHSIZE;
	trampoline_inst[PATCHSIZE+5] = 0xC3; // ret
#elif defined(__arm__)
	memcpy(trampoline_inst, _origBytes.data(), PATCHSIZE);
	*(unsigned long*)&trampoline_inst[PATCHSIZE] = 0xE59FF000; // BX LR
	*(unsigned long*)&trampoline_inst[PATCHSIZE+4] = 0xE12FFF1E; // LDR PC, [PC]
	*(unsigned long*)&trampoline_inst[PATCHSIZE+8] = (unsigned long)func+PATCHSIZE;
#endif

	// Hook
	unsigned char hook_inst[PATCHSIZE];
	memcpy(hook_inst, "\x00\xf0\x9f\xe5\x1e\xff\x2f\xe1\x00\x00\x00\x00", 12); // push addr; ret
	*(unsigned long *)&hook_inst[8] = (unsigned long)newAddr;

	Memory::UnProtect(func, PATCHSIZE);
	Memory::Write(func, hook_inst, PATCHSIZE);
	Memory::Protect(func, PATCHSIZE);
}

void Hook::doUnHook(void *f, void *n, void **o)
{
	munmap(*o, sysconf(_SC_PAGESIZE));
	Memory::UnProtect(func, PATCHSIZE);
	Memory::Write(func, _origBytes.data(), PATCHSIZE);
	Memory::Protect(func, PATCHSIZE);
}

void Hook::safemepls(void *f, void *n, void **o)
{
	func = reinterpret_cast<void*>((unsigned long)f & (-1));
	newAddr = reinterpret_cast<void*>((unsigned long)n & (-1));
	origFunc = reinterpret_cast<void**>((unsigned long)o & (-1));
	
	uint8_t *orig = new uint8_t[PATCHSIZE];
	Memory::Read(func, orig, PATCHSIZE);
	this->_origBytes.assign(orig, orig + PATCHSIZE);
	delete[] orig;
}

} // Liberation