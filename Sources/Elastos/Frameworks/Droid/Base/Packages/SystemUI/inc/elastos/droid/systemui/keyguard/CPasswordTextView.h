
#ifndef __ELASTOS_DROID_SYSTEMUI_KEYGUARD_CPASSWORDTEXTVIEW_H__
#define __ELASTOS_DROID_SYSTEMUI_KEYGUARD_CPASSWORDTEXTVIEW_H__

#include "_Elastos_Droid_SystemUI_Keyguard_CPasswordTextView.h"
#include <elastos/droid/widget/View.h>

using Elastos::Droid::Widget::View;

namespace Elastos {
namespace Droid {
namespace SystemUI {
namespace Keyguard {

/**
 * A View similar to a textView which contains password text and can animate when the text is
 * changed
 */
CarClass(CPasswordTextView)
    , public View
{
private:
    class CharState
        : public Object
    {
    private:
        class MyAnimatorListenerAdapter
            : public Object
        {
        public:
            TO_STRING_IMPL("CPasswordTextView::CharState::MyAnimatorListenerAdapter")

            MyAnimatorListenerAdapter(
                /* [in] */ CharState* inHost,
                /* [in] */ CPasswordTextView* outHost)
                : mCancelled(FALSE)
                , mInHost(inHost)
                , mOutHost(outHost)
            {}

            //@Override
            CARAPI OnAnimationCancel(
                /* [in] */ IAnimator* animation);

            //@Override
            CARAPI OnAnimationEnd(
                /* [in] */ IAnimator* animation);

            //@Override
            CARAPI OnAnimationStart(
                /* [in] */ IAnimator* animation);

        private:
            Boolean mCancelled;
            CharState* mInHost;
            CPasswordTextView* mOutHost;
        };

        class MyAnimatorListenerAdapter2
            : public Object
        {
        public:
            TO_STRING_IMPL("CPasswordTextView::CharState::MyAnimatorListenerAdapter2")

            MyAnimatorListenerAdapter2(
                /* [in] */ CharState* host)
                : mHost(host)
            {}

            //@Override
            CARAPI OnAnimationEnd(
                /* [in] */ IAnimator* animation);

        private:
            CharState* mHost;
        };

        class MyAnimatorListenerAdapter3
            : public Object
        {
        public:
            TO_STRING_IMPL("CPasswordTextView::CharState::MyAnimatorListenerAdapter3")

            MyAnimatorListenerAdapter3(
                /* [in] */ CharState* host)
                : mHost(host)
            {}

            //@Override
            CARAPI OnAnimationEnd(
                /* [in] */ IAnimator* animation);

        private:
            CharState* mHost;
        };

        class MyAnimatorListenerAdapter4
            : public Object
        {
        public:
            TO_STRING_IMPL("CPasswordTextView::CharState::MyAnimatorListenerAdapter4")

            MyAnimatorListenerAdapter4(
                /* [in] */ CharState* host)
                : mHost(host)
            {}

            //@Override
            CARAPI OnAnimationEnd(
                /* [in] */ IAnimator* animation);

        private:
            CharState* mHost;
        };

        class MyAnimatorListenerAdapter5
            : public Object
        {
        public:
            TO_STRING_IMPL("CPasswordTextView::CharState::MyAnimatorListenerAdapter5")

            MyAnimatorListenerAdapter5(
                /* [in] */ CharState* host)
                : mHost(host)
            {}

            //@Override
            CARAPI OnAnimationEnd(
                /* [in] */ IAnimator* animation);

        private:
            CharState* mHost;
        };

        class MyAnimatorUpdateListener
            : public Object
            , public IAnimatorUpdateListener
        {
        public:
            TO_STRING_IMPL("CPasswordTextView::CharState::MyAnimatorUpdateListener")

            CAR_INTERFACE_DECL()

            MyAnimatorUpdateListener(
                /* [in] */ CharState* inHost,
                /* [in] */ CPasswordTextView* outHost)
                , mInHost(inHost)
                , mOutHost(outHost)
            {}

            //@Override
            CARAPI OnAnimationUpdate(
                /* [in] */ IValueAnimator* animation);

        private:
            CharState* mInHost;
            CPasswordTextView* mOutHost;
        }

        class MyAnimatorUpdateListener2
            : public Object
            , public IAnimatorUpdateListener
        {
        public:
            TO_STRING_IMPL("CPasswordTextView::CharState::MyAnimatorUpdateListener2")

            CAR_INTERFACE_DECL()

            MyAnimatorUpdateListener2(
                /* [in] */ CharState* inHost,
                /* [in] */ CPasswordTextView* outHost)
                , mInHost(inHost)
                , mOutHost(outHost)
            {}

            //@Override
            CARAPI OnAnimationUpdate(
                /* [in] */ IValueAnimator* animation);

        private:
            CharState* mInHost;
            CPasswordTextView* mOutHost;
        }

        class MyAnimatorUpdateListener3
            : public Object
            , public IAnimatorUpdateListener
        {
        public:
            TO_STRING_IMPL("CPasswordTextView::CharState::MyAnimatorUpdateListener3")

            CAR_INTERFACE_DECL()

            MyAnimatorUpdateListener3(
                /* [in] */ CharState* inHost,
                /* [in] */ CPasswordTextView* outHost)
                , mInHost(inHost)
                , mOutHost(outHost)
            {}

            //@Override
            CARAPI OnAnimationUpdate(
                /* [in] */ IValueAnimator* animation);

        private:
            CharState* mInHost;
            CPasswordTextView* mOutHost;
        }

        class MyAnimatorUpdateListener4
            : public Object
            , public IAnimatorUpdateListener
        {
        public:
            TO_STRING_IMPL("CPasswordTextView::CharState::MyAnimatorUpdateListener4")

            CAR_INTERFACE_DECL()

            MyAnimatorUpdateListener4(
                /* [in] */ CharState* inHost,
                /* [in] */ CPasswordTextView* outHost)
                , mInHost(inHost)
                , mOutHost(outHost)
            {}

            //@Override
            CARAPI OnAnimationUpdate(
                /* [in] */ IValueAnimator* animation);

        private:
            CharState* mInHost;
            CPasswordTextView* mOutHost;
        }

        class MyRunnable
            : public Object
        {
        public:
            TO_STRING_IMPL("CPasswordTextView::CharState::MyRunnable")

            MyRunnable(
                /* [in] */ CharState* host)
                , mHost(host)
            {}

            //@Override
            CARAPI Run();

        private:
            CharState* mHost;
        }

    public:
        TO_STRING_IMPL("CPasswordTextView::CharState")

        CharState(
            /* [in] */ CPasswordTextView* host);

        CARAPI Reset();

        CARAPI StartRemoveAnimation(
            /* [in] */ Int64 startDelay,
            /* [in] */ Int64 widthDelay);

        CARAPI StartAppearAnimation();

        CARAPI SwapToDotWhenAppearFinished();

        /**
         * Draw this char to the canvas.
         *
         * @return The width this character contributes, including padding.
         */
        CARAPI Draw(
            /* [in] */ ICanvas* canvas,
            /* [in] */ Float currentDrawPosition,
            /* [in] */ Int32 charHeight,
            /* [in] */ Float yPosition,
            /* [in] */ Float charLength,
            /* [out] */ Float* result);

    private:
        /**
         * Posts a runnable which ensures that the text will be replaced by a dot after {@link
         * com.android.keyguard.PasswordTextView#TEXT_VISIBILITY_DURATION}.
         */
        CARAPI_(void) PostDotSwap(
            /* [in] */ Int64 delay);

        CARAPI_(void) RemoveDotSwapCallbacks();

        CARAPI_(void) PerformSwap();

        CARAPI_(void) StartWidthDisappearAnimation(
            /* [in] */ Int64 widthDelay);

        CARAPI_(void) StartTextDisappearAnimation(
            /* [in] */ Int64 startDelay);

        CARAPI_(void) StartDotDisappearAnimation(
            /* [in] */ Int64 startDelay);

        CARAPI_(void) StartWidthAppearAnimation();

        CARAPI_(void) StartTextAppearAnimation();

        CARAPI_(void) StartDotAppearAnimation(
            /* [in] */ Int64 delay);

        CARAPI_(void) CancelAnimator(
            /* [in] */ IAnimator* animator);

    public:
        Char32 mWhichChar;
        AutoPtr<IValueAnimator> mTextAnimator;
        Boolean mTextAnimationIsGrowing;
        AutoPtr<IAnimator> mDotAnimator;
        Boolean mDotAnimationIsGrowing;
        AutoPtr<IValueAnimator> mWidthAnimator;
        Boolean mWidthAnimationIsGrowing;
        Float mCurrentTextSizeFactor;
        Float mCurrentDotSizeFactor;
        Float mCurrentWidthFactor;
        Boolean mIsDotSwapPending;
        Float mCurrentTextTranslationY;
        AutoPtr<IValueAnimator> mTextTranslateAnimator;

        AutoPtr<IAnimatorListener> mRemoveEndListener;
        AutoPtr<IAnimatorListener> mDotFinishListener;
        AutoPtr<IAnimatorListener> mTextFinishListener;
        AutoPtr<IAnimatorListener> mTextTranslateFinishListener;
        AutoPtr<IAnimatorListener> mWidthFinishListener;

        AutoPtr<IAnimatorUpdateListener> mDotSizeUpdater;
        AutoPtr<IAnimatorUpdateListener> mTextSizeUpdater;
        AutoPtr<IAnimatorUpdateListener> mTextTranslationUpdater;
        AutoPtr<IAnimatorUpdateListener> mWidthUpdater;

        AutoPtr<IRunnable> mDotSwapperRunnable;

    private:
        CPasswordTextView* mHost;
    };

public:
    CAR_OBJECT_DECL()

    CPasswordTextView();

    CARAPI constructor(
        /* [in] */ IContext* context);

    CARAPI constructor(
        /* [in] */ IContext* context,
        /* [in] */ IAttributeSet* attrs);

    CARAPI constructor(
        /* [in] */ IContext* context,
        /* [in] */ IAttributeSet* attrs,
        /* [in] */ Int32 defStyleAttr);

    CARAPI constructor(
        /* [in] */ IContext* context,
        /* [in] */ IAttributeSet* attrs,
        /* [in] */ Int32 defStyleAttr,
        /* [in] */ Int32 defStyleRes);

    //@Override
    CARAPI HasOverlappingRendering(
        /* [out] */ Boolean* result);

    CARAPI Append(
        /* [in] */ Char32 c);

    CARAPI DeleteLastChar();

    CARAPI GetText(
        /* [out] */ String* test);

    CARAPI Reset(
        /* [in] */ Boolean animated);

protected:
    //@Override
    CARAPI_(void) OnDraw(
        /* [in] */ ICanvas* canvas);

private:
    CARAPI_(AutoPtr<IRect>) GetCharBounds();

    CARAPI_(Float) GetDrawingWidth();

    CARAPI_(void) UserActivity();

    CARAPI_(AutoPtr<CharState>) ObtainCharState(
        /* [in] */ Char32 c);

private:
    static const Float DOT_OVERSHOOT_FACTOR;
    static const Int64 DOT_APPEAR_DURATION_OVERSHOOT;
    static const Int64 APPEAR_DURATION;
    static const Int64 DISAPPEAR_DURATION;
    static const Int64 RESET_DELAY_PER_ELEMENT;
    static const Int64 RESET_MAX_DELAY;

    /**
     * The overlap between the text disappearing and the dot appearing animation
     */
    static const Int64 DOT_APPEAR_TEXT_DISAPPEAR_OVERLAP_DURATION;

    /**
     * The duration the text needs to stay there at least before it can morph into a dot
     */
    static const Int64 TEXT_REST_DURATION_AFTER_APPEAR;

    /**
     * The duration the text should be visible, starting with the appear animation
     */
    static const Int64 TEXT_VISIBILITY_DURATION;

    /**
     * The position in time from [0,1] where the overshoot should be finished and the settle back
     * animation of the dot should start
     */
    static const Float OVERSHOOT_TIME_POSITION;

    /**
     * The raw text size, will be multiplied by the scaled density when drawn
     */
    Int32 mTextHeightRaw;
    AutoPtr<IArrayList> mTextChars;
    String mText;
    AutoPtr<IStack> mCharPool;
    Int32 mDotSize;
    AutoPtr<IPowerManager> mPM;
    Int32 mCharPadding;
    AutoPtr<IPaint> mDrawPaint;
    AutoPtr<IInterpolator> mAppearInterpolator;
    AutoPtr<IInterpolator> mDisappearInterpolator;
    AutoPtr<IInterpolator> mFastOutSlowInInterpolator;
    Boolean mShowPassword;
};

} // namespace Keyguard
} // namespace SystemUI
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_SYSTEMUI_KEYGUARD_CPASSWORDTEXTVIEW_H__