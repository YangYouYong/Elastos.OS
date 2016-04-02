#ifndef __ELASTOS_DROID_TELECOMM_TELECOM_CCONNECTIONSERVICEADAPTERSERVANT_H__
#define __ELASTOS_DROID_TELECOMM_TELECOM_CCONNECTIONSERVICEADAPTERSERVANT_H__

#include "_Elastos_Droid_Telecomm_Telecom_CConnectionServiceAdapterServant.h"
#include "elastos/droid/telecomm/telecom/ConnectionServiceAdapterServant.h"

namespace Elastos {
namespace Droid {
namespace Telecomm {
namespace Telecom {

CarClass(CConnectionServiceAdapterServant)
    , public ConnectionServiceAdapterServant
{
public:
    CAR_OBJECT_DECL()
};

} // namespace Telecom
} // namespace Telecomm
} // namespace Droid
} // namespace Elastos

#endif //__ELASTOS_DROID_TELECOMM_TELECOM_CCONNECTIONSERVICEADAPTERSERVANT_H__