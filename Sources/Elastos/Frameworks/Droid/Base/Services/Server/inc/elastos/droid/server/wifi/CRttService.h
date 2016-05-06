#ifndef __ELASTOS_DROID_SERVER_WIFI_CRTTSERVICE_H__
#define __ELASTOS_DROID_SERVER_WIFI_CRTTSERVICE_H__

#include "_Elastos_Droid_Server_Wifi_CRttService.h"
#include "elastos/droid/server/wifi/RttService.h"

namespace Elastos {
namespace Droid {
namespace Server {
namespace Wifi {

CarClass(CRttService)
    , public RttService
{
public:
    CAR_OBJECT_DECL()
};

} // namespace Wifi
} // namespace Server
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_SERVER_WIFI_CRTTSERVICE_H__