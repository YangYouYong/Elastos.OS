
#ifndef __ELASTOS_DROID_JAVAPROXY_CMOUNTSERVICELISTENER_H__
#define __ELASTOS_DROID_JAVAPROXY_CMOUNTSERVICELISTENER_H__

#include "_Elastos_Droid_JavaProxy_CMountServiceListener.h"
#include <elastos/core/Object.h>
#include <jni.h>

using Elastos::Droid::Os::IBinder;
using Elastos::Droid::Os::Storage::IIMountServiceListener;

namespace Elastos {
namespace Droid {
namespace JavaProxy {

CarClass(CMountServiceListener)
    , public Object
    , public IIMountServiceListener
    , public IBinder
{
public:
    ~CMountServiceListener();

    CAR_INTERFACE_DECL()

    CAR_OBJECT_DECL()

    CARAPI constructor(
        /* [in] */ Handle64 jVM,
        /* [in] */ Handle64 jInstance);

    CARAPI OnUsbMassStorageConnectionChanged(
        /* [in] */ Boolean connected);

    CARAPI OnStorageStateChanged(
        /* [in] */ const String& path,
        /* [in] */ const String& oldState,
        /* [in] */ const String& newState);

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

#endif // __ELASTOS_DROID_JAVAPROXY_CMOUNTSERVICELISTENER_H__
