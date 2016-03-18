
#include "elastos/droid/javaproxy/CIAudioRoutesObserver.h"
#include "elastos/droid/javaproxy/Util.h"

using Elastos::Droid::Media::EIID_IIAudioRoutesObserver;
using Elastos::Droid::Os::EIID_IBinder;

namespace Elastos {
namespace Droid {
namespace JavaProxy {

const String CIAudioRoutesObserver::TAG("CIAudioRoutesObserver");

CAR_INTERFACE_IMPL_2(CIAudioRoutesObserver, Object, IIAudioRoutesObserver, IBinder)

CAR_OBJECT_IMPL(CIAudioRoutesObserver)

CIAudioRoutesObserver::~CIAudioRoutesObserver()
{
    JNIEnv* env;
    mJVM->AttachCurrentThread(&env, NULL);
    env->DeleteGlobalRef(mJInstance);
}

ECode CIAudioRoutesObserver::constructor(
    /* [in] */ Handle64 jVM,
    /* [in] */ Handle64 jInstance)
{
    mJVM = (JavaVM*)jVM;
    mJInstance = (jobject)jInstance;
    return NOERROR;
}

ECode CIAudioRoutesObserver::DispatchAudioRoutesChanged(
    /* [in] */ IAudioRoutesInfo* newRoutes)
{
    JNIEnv* env;
    mJVM->AttachCurrentThread(&env, NULL);

    jobject jnewRoutes = Util::ToJavaAudioRoutesInfo(env, newRoutes);

    jclass c = env->FindClass("android/media/IAudioRoutesObserver");
    Util::CheckErrorAndLog(env, TAG, "Fail FindClass: IRemoteVolumeObserver %d", __LINE__);

    jmethodID m = env->GetMethodID(c, "dispatchAudioRoutesChanged", "(Landroid/media/AudioRoutesInfo;)V");
    Util::CheckErrorAndLog(env, TAG, "GetMethodID: dispatchAudioRoutesChanged %d", __LINE__);

    env->CallVoidMethod(mJInstance, m, jnewRoutes);
    Util::CheckErrorAndLog(env, TAG, "CallVoidMethod: dispatchAudioRoutesChanged %d", __LINE__);

    env->DeleteLocalRef(c);
    env->DeleteLocalRef(jnewRoutes);
    return NOERROR;
}

ECode CIAudioRoutesObserver::ToString(
    /* [out] */ String* str)
{
    JNIEnv* env;
    mJVM->AttachCurrentThread(&env, NULL);
    *str = Util::GetJavaToStringResult(env, mJInstance);
    return NOERROR;
}

}
}
}

