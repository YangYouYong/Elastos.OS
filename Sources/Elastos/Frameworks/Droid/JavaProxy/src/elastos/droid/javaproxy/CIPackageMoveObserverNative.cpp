
#include "elastos/droid/javaproxy/CIPackageMoveObserverNative.h"
#include <elastos/utility/logging/Logger.h>
#include "elastos/droid/javaproxy/Util.h"

using Elastos::Droid::Content::Pm::EIID_IIPackageMoveObserver;
using Elastos::Droid::Os::EIID_IBinder;
using Elastos::Utility::Logging::Logger;

namespace Elastos {
namespace Droid {
namespace JavaProxy {

const String CIPackageMoveObserverNative::TAG("CIPackageMoveObserverNative");

CAR_INTERFACE_IMPL_2(CIPackageMoveObserverNative, Object, IIPackageMoveObserver, IBinder)

CAR_OBJECT_IMPL(CIPackageMoveObserverNative)

CIPackageMoveObserverNative::~CIPackageMoveObserverNative()
{
    JNIEnv* env;
    mJVM->AttachCurrentThread(&env, NULL);
    env->DeleteGlobalRef(mJInstance);
}

ECode CIPackageMoveObserverNative::constructor(
    /* [in] */ Handle64 jVM,
    /* [in] */ Handle64 jInstance)
{
    mJVM = (JavaVM*)jVM;
    mJInstance = (jobject)jInstance;
    return NOERROR;
}

ECode CIPackageMoveObserverNative::PackageMoved(
    /* [in] */ const String& packageName,
    /* [in] */ Int32 returnCode)
{
    // LOGGERD(TAG, "+ CIPackageMoveObserverNative::PackageMoved()");

    JNIEnv* env;
    mJVM->AttachCurrentThread(&env, NULL);

    jstring jpackageName = Util::ToJavaString(env, packageName);

    jclass c = env->FindClass("android/content/pm/IPackageMoveObserver");
    Util::CheckErrorAndLog(env, TAG, "FindClass: IPackageMoveObserver %d", __LINE__);

    jmethodID m = env->GetMethodID(c, "packageMoved", "(Ljava/lang/String;I)V");
    Util::CheckErrorAndLog(env, TAG, "GetMethodID: packageMoved %d", __LINE__);

    env->CallVoidMethod(mJInstance, m, jpackageName, (jint)returnCode);
    Util::CheckErrorAndLog(env, TAG, "CallVoidMethod: packageMoved %d", __LINE__);

    env->DeleteLocalRef(c);
    env->DeleteLocalRef(jpackageName);

    // LOGGERD(TAG, "- CIPackageMoveObserverNative::PackageMoved()");
    return NOERROR;
}

ECode CIPackageMoveObserverNative::ToString(
    /* [out] */ String* str)
{
    // LOGGERD(TAG, "+ CIPackageMoveObserverNative::ToString()");
    JNIEnv* env;
    mJVM->AttachCurrentThread(&env, NULL);

    jclass c = env->FindClass("java/lang/Object");
    Util::CheckErrorAndLog(env, "ToString", "FindClass: Object", __LINE__);

    jmethodID m = env->GetMethodID(c, "toString", "()Ljava/lang/String;");
    Util::CheckErrorAndLog(env, TAG, "GetMethodID: toString", __LINE__);

    jstring jstr = (jstring)env->CallObjectMethod(mJInstance, m);
    Util::CheckErrorAndLog(env, TAG, "CallVoidMethod: toString", __LINE__);

    *str = Util::GetElString(env, jstr);

    env->DeleteLocalRef(c);
    env->DeleteLocalRef(jstr);

    // LOGGERD(TAG, "- CIPackageMoveObserverNative::ToString()");
    return NOERROR;
}

}
}
}

