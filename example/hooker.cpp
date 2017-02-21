#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include "Liberation.h"

char const *getMoney = "giveMeMoneyRealFast";

void doHook()
{
    void *imagehandle = dlopen("libebelac.so", RTLD_GLOBAL | RTLD_NOW);
    void *pGetMoney = dlsym(imagehandle, getMoney);

    Patch *gold = Patch::Setup(pGetMoney, "38467047"); // MOV R0, R7; BX LR;
    gold->Apply();
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    jint result = -1;

    doHook();

    result = JNI_VERSION_1_4;
bail:
    return result;
}
