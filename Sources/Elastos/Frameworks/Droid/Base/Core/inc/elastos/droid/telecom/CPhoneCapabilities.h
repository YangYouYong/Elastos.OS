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

#ifndef __ELASTOS_DROID_TELECOM_CPHONECAPABILITIES_H__
#define __ELASTOS_DROID_TELECOM_CPHONECAPABILITIES_H__

#include "_Elastos_Droid_Telecom_CPhoneCapabilities.h"
#include <elastos/core/Singleton.h>

using Elastos::Core::Singleton;

namespace Elastos {
namespace Droid {
namespace Telecom {

/**
 * Defines capabilities a phone call can support, such as conference calling and video telephony.
 * Also defines properties of a phone call, such as whether it is using VoLTE technology.
 * @hide
 */
CarClass(CPhoneCapabilities)
    , public Singleton
    , public IPhoneCapabilities
{
public:
    CAR_SINGLETON_DECL()

    CAR_INTERFACE_DECL()

    using Singleton::ToString;

    CARAPI ToString(
        /* [in] */ Int32 capabilities,
        /* [out] */ String* result);
};

} // namespace Telecom
} // namespace Droid
} // namespace Elastos

#endif //__ELASTOS_DROID_TELECOM_CPHONECAPABILITIES_H__