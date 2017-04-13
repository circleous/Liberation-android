#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include "Liberation.h"

char const *getMoney = "_ZNK8LKPlayer8getMoneyEv";

int (*orig_getmunny)();
int getmunny()
{
	__android_log_print(ANDROID_LOG_INFO, "HOOK", "call from hooked!");
	return orig_getmunny();
}

void patchmeuppls()
{
	void *imagehandle = dlopen("libcocos2dlua.so", RTLD_GLOBAL | RTLD_NOW);
	void *pGetMoney = dlsym(imagehandle, getMoney);

	Patch *gold = Patch::Setup(pGetMoney, "38467047"); // MOV R0, R7; BX LR;
	gold->Apply();
}

void hookmeuppls()
{
	Hook *hooker;
	hooker = Hook::getInstance();

	void *imagehandle = dlopen("libcocos2dlua.so", RTLD_GLOBAL | RTLD_NOW);
	void *pGetMoney = dlsym(imagehandle, getMoney);

	hooker->hook(pGetMoney, reinterpret_cast<void*>(getmunny), reinterpret_cast<void**>(orig_getmunny));
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	jint result = -1;

	hookmeuppls();

	result = JNI_VERSION_1_4;
bail:
	return result;
}
