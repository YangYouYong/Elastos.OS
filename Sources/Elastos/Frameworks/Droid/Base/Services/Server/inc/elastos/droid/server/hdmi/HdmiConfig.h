//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#ifndef __ELASTOS_DROID_SERVER_HDMI_HDMICONFIG_H__
#define __ELASTOS_DROID_SERVER_HDMI_HDMICONFIG_H__

#include "_Elastos.Droid.Server.h"
#include <elastos/droid/ext/frameworkext.h>
#include <elastos/core/Object.h>

namespace Elastos {
namespace Droid {
namespace Server {
namespace Hdmi {

/**
 * Class that holds together the constants that may require per-product configuration.
 */
class HdmiConfig
    : public Object
{
public:
    // Default timeout for the incoming command to arrive in response to a request.
    static const Int32 TIMEOUT_MS;

    // from the adjacent one so as not to place unnecessarily heavy load on the CEC line.
    static const Int32 IRT_MS;

    // or HDMI control is enabled.
    static const Int32 DEVICE_POLLING_RETRY;

    // Number of retries for polling each device in periodic check (hotplug detection).
    static const Int32 HOTPLUG_DETECTION_RETRY;

    // Number of retries for polling each device in address allocation mechanism.
    static const Int32 ADDRESS_ALLOCATION_RETRY;

    // action. They will have their own retransmission count.
    static const Int32 RETRANSMISSION_COUNT;

    // switch since they won't be under control from TV.
    static const Boolean HIDE_DEVICES_BEHIND_LEGACY_SWITCH;

private:
    HdmiConfig();
};

} // namespace Hdmi
} // namespace Server
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_SERVER_HDMI_HDMICONFIG_H__
