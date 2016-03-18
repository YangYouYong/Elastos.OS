
#ifndef __ELASTOS_DROID_JAVAPROXY_CIPACKAGEDATAOBSERVERNATIVE_H__
#define __ELASTOS_DROID_JAVAPROXY_CIPACKAGEDATAOBSERVERNATIVE_H__

#include "_Elastos_Droid_JavaProxy_CIPackageDataObserverNative.h"
#include <elastos/core/Object.h>
#include <jni.h>

using Elastos::Droid::Content::Pm::IIPackageDataObserver;
using Elastos::Droid::Os::IBinder;

namespace Elastos {
namespace Droid {
namespace JavaProxy {

CarClass(CIPackageDataObserverNative)
    , public Object
    , public IIPackageDataObserver
    , public IBinder
{
public:
    ~CIPackageDataObserverNative();

    CAR_INTERFACE_DECL()

    CAR_OBJECT_DECL()

    CARAPI constructor(
        /* [in] */ Handle64 jVM,
        /* [in] */ Handle64 jInstance);

    CARAPI OnRemoveCompleted(
        /* [in] */ const String& packageName,
        /* [in] */ Boolean succeeded);

    CARAPI ToString(
        /* [out] */ String* str);

private:
    static const String TAG;

    JavaVM* mJVM;
    jobject mJInstance;
};

}
}
}

#endif // __ELASTOS_DROID_JAVAPROXY_CIPACKAGEDATAOBSERVERNATIVE_H__
