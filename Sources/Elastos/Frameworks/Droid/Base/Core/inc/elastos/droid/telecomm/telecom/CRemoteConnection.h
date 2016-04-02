#ifndef __ELASTOS_DROID_TELECOMM_TELECOM_CREMOTECONNECTION_H__
#define __ELASTOS_DROID_TELECOMM_TELECOM_CREMOTECONNECTION_H__

#include "_Elastos_Droid_Telecomm_Telecom_CRemoteConnection.h"
#include "elastos/droid/telecomm/telecom/RemoteConnection.h"

namespace Elastos {
namespace Droid {
namespace Telecomm {
namespace Telecom {

CarClass(CRemoteConnection)
    , public RemoteConnection
{
public:
    CAR_OBJECT_DECL()
};

} // namespace Telecom
} // namespace Telecomm
} // namespace Droid
} // namespace Elastos

#endif //__ELASTOS_DROID_TELECOMM_TELECOM_CREMOTECONNECTION_H__