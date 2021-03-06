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

#ifndef __ELASTOS_DROID_SERVER_WM_POINTEREVENTDISPATCHER_H__
#define __ELASTOS_DROID_SERVER_WM_POINTEREVENTDISPATCHER_H__

#include "elastos/droid/view/InputEventReceiver.h"
#include <elastos/utility/etl/List.h>

using Elastos::Droid::View::IPointerEventListener;
using Elastos::Droid::View::IInputChannel;
using Elastos::Droid::View::InputEventReceiver;
using Elastos::Droid::View::IInputEvent;
using Elastos::Utility::Etl::List;

namespace Elastos {
namespace Droid {
namespace Server {
namespace Wm {

class PointerEventDispatcher : public InputEventReceiver
{
public:
    PointerEventDispatcher();

    CARAPI constructor(
        /* [in] */ IInputChannel* inputChannel);

    CARAPI OnInputEvent(
        /* [in] */ IInputEvent* event);

    /**
     * Add the specified listener to the list.
     * @param listener The listener to add.
     */
    CARAPI RegisterInputEventListener(
        /* [in] */ IPointerEventListener* listener);

    /**
     * Remove the specified listener from the list.
     * @param listener The listener to remove.
     */
    CARAPI UnregisterInputEventListener(
        /* [in] */ IPointerEventListener* listener);

public:
    List<AutoPtr<IPointerEventListener> > mListeners;
    Object mListenersLock;
    AutoPtr< ArrayOf<IPointerEventListener*> > mListenersArray;
};

} // Wm
} // Server
} // Droid
} // Elastos

#endif //__ELASTOS_DROID_SERVER_WM_POINTEREVENTDISPATCHER_H__
