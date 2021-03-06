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

#ifndef __ELASTOS_DROID_SERVER_AM_COMPATMODEDIALOG_H__
#define __ELASTOS_DROID_SERVER_AM_COMPATMODEDIALOG_H__

#include "Elastos.Droid.Widget.h"
#include "elastos/droid/ext/frameworkext.h"
#include "elastos/droid/server/am/CActivityManagerService.h"
#include "elastos/droid/app/Dialog.h"

using Elastos::Droid::App::Dialog;
using Elastos::Droid::App::IDialog;
using Elastos::Droid::View::IWindowCallback;
using Elastos::Droid::View::IKeyEventCallback;
using Elastos::Droid::View::IViewOnCreateContextMenuListener;
using Elastos::Droid::Widget::ISwitch;
using Elastos::Droid::Widget::ICheckBox;
using Elastos::Droid::Widget::ICompoundButton;
using Elastos::Droid::Widget::ICompoundButtonOnCheckedChangeListener;
using Elastos::Droid::Content::Pm::IApplicationInfo;

namespace Elastos {
namespace Droid {
namespace Server {
namespace Am {

class CompatModeDialog
    : public Dialog
{
private:
    class CompatEnabledListener
        : public Object
        , public ICompoundButtonOnCheckedChangeListener
    {
    public:
        CompatEnabledListener(
            /* [in] */ CompatModeDialog* host)
            : mHost(host)
        {}

        CAR_INTERFACE_DECL()

        CARAPI OnCheckedChanged(
            /* [in] */ ICompoundButton* buttonView,
            /* [in] */ Boolean isChecked);

    private:
        CompatModeDialog* mHost;
    };

    class AlwaysShowListener
        : public Object
        , public ICompoundButtonOnCheckedChangeListener
    {
    public:
        AlwaysShowListener(
            /* [in] */ CompatModeDialog* host)
            : mHost(host)
        {}

        CAR_INTERFACE_DECL()

        CARAPI OnCheckedChanged(
            /* [in] */ ICompoundButton* buttonView,
            /* [in] */ Boolean isChecked);

    private:
        CompatModeDialog* mHost;
    };

public:
    CompatModeDialog(
        /* [in] */ CActivityManagerService* service,
        /* [in] */ IContext* context,
        /* [in] */ IApplicationInfo* appInfo);

    CARAPI OnKeyDown(
        /* [in] */ Int32 keyCode,
        /* [in] */ IKeyEvent* event,
        /* [out] */ Boolean* result);

    CARAPI OnKeyLongPress(
        /* [in] */ Int32 keyCode,
        /* [in] */ IKeyEvent* event,
        /* [out] */ Boolean* result);

    CARAPI OnKeyUp(
        /* [in] */ Int32 keyCode,
        /* [in] */ IKeyEvent* event,
        /* [out] */ Boolean* result);

    CARAPI OnKeyMultiple(
        /* [in] */ Int32 keyCode,
        /* [in] */ Int32 count,
        /* [in] */ IKeyEvent* event,
        /* [out] */ Boolean* result);

    CARAPI OnCreateContextMenu(
        /* [in] */ IContextMenu* menu,
        /* [in] */ IView* v,
        /* [in] */ IContextMenuInfo* menuInfo);

    CARAPI_(void) UpdateControls();

public:
    CActivityManagerService* mService;
    AutoPtr<IApplicationInfo> mAppInfo;

    AutoPtr<ISwitch> mCompatEnabled;
    AutoPtr<ICheckBox> mAlwaysShow;
    AutoPtr<IView> mHint;
};

} // namespace Am
} // namespace Server
} // namespace Droid
} // namespace Elastos

#endif //__ELASTOS_DROID_SERVER_AM_COMPATMODEDIALOG_H__
