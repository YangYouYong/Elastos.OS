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

#ifndef __ELASTOS_DROID_SERVER_WM_FAKEWINDOWIMPL_H__
#define __ELASTOS_DROID_SERVER_WM_FAKEWINDOWIMPL_H__

#include "elastos/droid/server/wm/CWindowManagerService.h"
#include "elastos/droid/server/input/InputApplicationHandle.h"
#include "elastos/droid/server/input/InputWindowHandle.h"

using Elastos::Droid::View::IFakeWindow;
using Elastos::Droid::View::IInputEventReceiverFactory;
using Elastos::Droid::View::IInputChannel;
using Elastos::Droid::View::IInputEventReceiver;
using Elastos::Droid::Server::Input::InputWindowHandle;
using Elastos::Droid::Server::Input::InputApplicationHandle;
using Elastos::Droid::Os::ILooper;

namespace Elastos {
namespace Droid {
namespace Server {
namespace Wm {

class FakeWindowImpl
    : public Object
    , public IFakeWindow
{
public:
    FakeWindowImpl(
        /* [in] */ CWindowManagerService* service,
        /* [in] */ ILooper* looper,
        /* [in] */ IInputEventReceiverFactory* inputEventReceiverFactory,
        /* [in] */ const String& name,
        /* [in] */ Int32 windowType,
        /* [in] */ Int32 layoutParamsFlags,
        /* [in] */ Int32 layoutParamsPrivateFlags,
        /* [in] */ Boolean canReceiveKeys,
        /* [in] */ Boolean hasFocus,
        /* [in] */ Boolean touchFullscreen);

    CAR_INTERFACE_DECL()

    CARAPI_(void) Layout(
        /* [in] */ Int32 dw,
        /* [in] */ Int32 dh);

    CARAPI Dismiss();

private:
    CARAPI_(Int32) GetLayerLw(
        /* [in] */ Int32 windowType);

public:
    AutoPtr<CWindowManagerService> mService;
    AutoPtr<IInputChannel> mServerChannel;
    AutoPtr<IInputChannel> mClientChannel;
    AutoPtr<InputApplicationHandle> mApplicationHandle;
    AutoPtr<InputWindowHandle> mWindowHandle;
    AutoPtr<IInputEventReceiver> mInputEventReceiver;
    Int32 mWindowLayer;

    Boolean mTouchFullscreen;
};

} // Wm
} // Server
} // Droid
} // Elastos

#endif //__ELASTOS_DROID_SERVER_WM_FAKEWINDOWIMPL_H__
