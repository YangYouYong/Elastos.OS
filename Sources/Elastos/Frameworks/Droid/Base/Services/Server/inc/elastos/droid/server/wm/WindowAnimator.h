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

#ifndef __ELASTOS_DROID_SERVER_WM_WINDOWANIMATOR_H__
#define __ELASTOS_DROID_SERVER_WM_WINDOWANIMATOR_H__

#include "_Elastos.Droid.Server.h"
#include "elastos/droid/server/wm/WindowState.h"
#include "elastos/droid/server/wm/WindowToken.h"
#include "elastos/droid/server/wm/ScreenRotationAnimation.h"
#include <elastos/core/Runnable.h>
#include <elastos/utility/etl/HashMap.h>
#include <elastos/utility/etl/List.h>

using Elastos::Droid::Content::IContext;
using Elastos::Core::Runnable;
using Elastos::Droid::View::IWindowManagerPolicy;
using Elastos::Utility::Etl::List;
using Elastos::Utility::Etl::HashMap;

namespace Elastos {
namespace Droid {
namespace Server {
namespace Wm {

class CWindowManagerService;
class AppWindowAnimator;
class WindowStateAnimator;

/**
 * Singleton class that carries out the animations and Surface operations in a separate task
 * on behalf of WindowManagerService.
 */
class WindowAnimator : public Object
{
private:
    class AnimationRunnable : public Runnable
    {
    public:
        AnimationRunnable(
            /* [in] */ WindowAnimator* host)
            : mHost(host)

        {}

        CARAPI Run();

    private:
        WindowAnimator* mHost;
    };

    class DisplayContentsAnimator : public Object
    {
    public:
        DisplayContentsAnimator() {}

    public:
        AutoPtr<ScreenRotationAnimation> mScreenRotationAnimation;
    };

public:
    WindowAnimator(
        /* [in] */ CWindowManagerService* service);

    CARAPI_(void) AddDisplayLocked(
        /* [in] */ Int32 displayId);

    CARAPI_(void) RemoveDisplayLocked(
        /* [in] */ Int32 displayId);

    CARAPI_(void) HideWallpapersLocked(
        /* [in] */ WindowState* w);

    static CARAPI_(String) BulkUpdateParamsToString(
        /* [in] */ Int32 bulkUpdateParams);

    // void dumpLocked(PrintWriter pw, String prefix, boolean dumpAll);

    CARAPI_(Int32) GetPendingLayoutChanges(
        /* [in] */ Int32 displayId);

    CARAPI_(void) SetPendingLayoutChanges(
        /* [in] */ Int32 displayId,
        /* [in] */ Int32 changes);

    CARAPI_(void) SetAppLayoutChanges(
        /* [in] */ AppWindowAnimator* appAnimator,
        /* [in] */ Int32 changes,
        /* [in] */ const String& s);

    CARAPI_(void) SetScreenRotationAnimationLocked(
        /* [in] */ Int32 displayId,
        /* [in] */ ScreenRotationAnimation* animation);

    CARAPI_(AutoPtr<ScreenRotationAnimation>) GetScreenRotationAnimationLocked(
        /* [in] */ Int32 displayId);

    CARAPI_(AutoPtr<WindowStateAnimator>) GetUniverseBackground();

    CARAPI_(void) SetUniverseBackground(
        /* [in] */ WindowStateAnimator* animator);

private:
    CARAPI_(String) ForceHidingToString();

    CARAPI_(void) UpdateAppWindowsLocked(
        /* [in] */ Int32 displayId);

    CARAPI_(void) UpdateWindowsLocked(
        /* [in] */ Int32 displayId);

    CARAPI_(void) UpdateWallpaperLocked(
        /* [in] */ Int32 displayId);

    /** See if any windows have been drawn, so they (and others associated with them) can now be
     *  shown. */
    CARAPI_(void) TestTokenMayBeDrawnLocked(
        /* [in] */ Int32 displayId);

    CARAPI_(void) PerformAnimationsLocked(
        /* [in] */ Int32 displayId);

    /** Locked on mService.mWindowMap. */
    CARAPI_(void) AnimateLocked();

    CARAPI_(AutoPtr<DisplayContentsAnimator>) GetDisplayContentsAnimatorLocked(
        /* [in] */ Int32 displayId);

public:
    // forceHiding states.
    static const Int32 KEYGUARD_NOT_SHOWN = 0;
    static const Int32 KEYGUARD_ANIMATING_IN = 1;
    static const Int32 KEYGUARD_SHOWN = 2;
    static const Int32 KEYGUARD_ANIMATING_OUT = 3;

    Object mSelfLock;

    CWindowManagerService* mService;
    IContext* mContext;
    IWindowManagerPolicy* mPolicy;

    Boolean mAnimating;

    AutoPtr<AnimationRunnable> mAnimationRunnable;

    /** Time of current animation step. Reset on each iteration */
    Int64 mCurrentTime;

    /** Window currently running an animation that has requested it be detached
     * from the wallpaper.  This means we need to ensure the wallpaper is
     * visible behind it in case it animates in a way that would allow it to be
     * seen. If multiple windows satisfy this, use the lowest window. */
    WindowState* mWindowDetachedWallpaper;  // weak-ref WindowState->WindowStateAnimator->AppWindowAnimator->WindowAnimator

    AutoPtr<IWeakReference> mUniverseBackground;    // weak-ref WindowStateAnimator>AppWindowAnimator->WindowAnimator
    Int32 mAboveUniverseLayer;

    Int32 mBulkUpdateParams;
    AutoPtr<IObject> mLastWindowFreezeSource;

    HashMap<Int32, AutoPtr<DisplayContentsAnimator> > mDisplayContentsAnimators;

    Boolean mInitialized;

    Boolean mKeyguardGoingAway;
    Boolean mKeyguardGoingAwayToNotificationShade;
    Boolean mKeyguardGoingAwayDisableWindowAnimations;
    Boolean mKeyguardGoingAwayShowingMedia;

    Int32 mForceHiding;

private:
    static const String TAG;

    /** How long to give statusbar to clear the private keyguard flag when animating out */
    static const Int64 KEYGUARD_ANIM_TIMEOUT_MS = 1000;

    /** Skip repeated AppWindowTokens initialization. Note that AppWindowsToken's version of this
     * is a long initialized to Long.MIN_VALUE so that it doesn't match this value on startup. */
    Int32 mAnimTransactionSequence;

    Boolean mBlurUiEnabled;

    friend class AnimationRunnable;
};

} // Wm
} // Server
} // Droid
} // Elastos

#endif //__ELASTOS_DROID_SERVER_WM_WINDOWANIMATOR_H__
