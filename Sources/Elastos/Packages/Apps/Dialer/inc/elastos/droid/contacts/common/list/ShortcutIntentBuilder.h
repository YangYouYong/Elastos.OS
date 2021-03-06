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

#ifndef __ELASTOS_DROID_CONTACTS_COMMON_LIST_SHORTCUTINTENTBUILDER_H__
#define __ELASTOS_DROID_CONTACTS_COMMON_LIST_SHORTCUTINTENTBUILDER_H__

#include "Elastos.Droid.Content.h"
#include "Elastos.Droid.Graphics.h"
#include "Elastos.Droid.Os.h"
#include "_Elastos.Droid.Dialer.h"
#include "elastos/droid/os/AsyncTask.h"
#include <elastos/core/Object.h>

using Elastos::Droid::Content::IContext;
using Elastos::Droid::Content::Res::IResources;
using Elastos::Droid::Graphics::IBitmap;
using Elastos::Droid::Graphics::Drawable::IDrawable;
using Elastos::Droid::Net::IUri;
using Elastos::Droid::Os::AsyncTask;
using Elastos::Core::Object;

namespace Elastos {
namespace Droid {
namespace Contacts {
namespace Common {
namespace List {

/**
 * Constructs shortcut intents.
 */
class ShortcutIntentBuilder
    : public Object
{
private:
    /**
     * An asynchronous task that loads name, photo and other data from the database.
     */
    class LoadingAsyncTask
        : public AsyncTask
    {
    public:
        LoadingAsyncTask(
            /* [in] */ ShortcutIntentBuilder* host,
            /* [in] */ IUri* uri);

        virtual ~LoadingAsyncTask() {}

    protected:
        // @Override
        CARAPI DoInBackground(
            /* [in] */ ArrayOf<IInterface*>* params,
            /* [out] */ IInterface** result);

        virtual CARAPI_(void) LoadData() = 0;

    private:
        CARAPI_(void) LoadPhoto();

    protected:
        AutoPtr<IUri> mUri;
        String mContentType;
        String mDisplayName;
        String mLookupKey;
        AutoPtr<ArrayOf<Byte> > mBitmapData;
        Int64 mPhotoId;
        ShortcutIntentBuilder* mHost;
    };

    class ContactLoadingAsyncTask
        : public LoadingAsyncTask
    {
    public:
        ContactLoadingAsyncTask(
            /* [in] */ ShortcutIntentBuilder* host,
            /* [in] */ IUri* uri);

    protected:
        // @Override
        CARAPI_(void) LoadData();

        // @Override
        CARAPI OnPostExecute(
            /* [in] */ IInterface* result);
    };

    class PhoneNumberLoadingAsyncTask
        : public LoadingAsyncTask
    {
    public:
        PhoneNumberLoadingAsyncTask(
            /* [in] */ ShortcutIntentBuilder* host,
            /* [in] */ IUri* uri,
            /* [in] */ const String& shortcutAction);

    protected:
        // @Override
        CARAPI_(void) LoadData();

        // @Override
        CARAPI OnPostExecute(
            /* [in] */ IInterface* result);

    private:
        String mShortcutAction;
        String mPhoneNumber;
        Int32 mPhoneType;
        String mPhoneLabel;
    };

public:
    ShortcutIntentBuilder(
        /* [in] */ IContext* context,
        /* [in] */ IOnShortcutIntentCreatedListener* listener);

    CARAPI_(void) CreateContactShortcutIntent(
        /* [in] */ IUri* contactUri);

    CARAPI_(void) CreatePhoneNumberShortcutIntent(
        /* [in] */ IUri* dataUri,
        /* [in] */ const String& shortcutAction);

private:
    CARAPI_(AutoPtr<IDrawable>) GetPhotoDrawable(
        /* [in] */ ArrayOf<Byte>* bitmapData,
        /* [in] */ const String& displayName,
        /* [in] */ const String& lookupKey);

    CARAPI_(void) CreateContactShortcutIntent(
        /* [in] */ IUri* contactUri,
        /* [in] */ const String& contentType,
        /* [in] */ const String& displayName,
        /* [in] */ const String& lookupKey,
        /* [in] */ ArrayOf<Byte>* bitmapData);

    CARAPI_(void) CreatePhoneNumberShortcutIntent(
        /* [in] */ IUri* uri,
        /* [in] */ const String& displayName,
        /* [in] */ const String& lookupKey,
        /* [in] */ ArrayOf<Byte>* bitmapData,
        /* [in] */ const String& phoneNumber,
        /* [in] */ Int32 phoneType,
        /* [in] */ const String& phoneLabel,
        /* [in] */ const String& shortcutAction);

    CARAPI_(AutoPtr<IBitmap>) GenerateQuickContactIcon(
        /* [in] */ IDrawable* photo);

    /**
     * Generates a phone number shortcut icon. Adds an overlay describing the type of the phone
     * number, and if there is a photo also adds the call action icon.
     */
    CARAPI_(AutoPtr<IBitmap>) GeneratePhoneNumberIcon(
        /* [in] */ IDrawable* photo,
        /* [in] */ Int32 phoneType,
        /* [in] */ const String& phoneLabel,
        /* [in] */ Int32 actionResId);

public:
    /**
     * This is a hidden API of the launcher in JellyBean that allows us to disable the animation
     * that it would usually do, because it interferes with our own animation for QuickContact.
     * This is needed since some versions of the launcher override the intent flags and therefore
     * ignore Intent.FLAG_ACTIVITY_NO_ANIMATION.
     */
    static const String INTENT_EXTRA_IGNORE_LAUNCH_ANIMATION;

private:
    static const AutoPtr<ArrayOf<String> > CONTACT_COLUMNS;

    static const Int32 CONTACT_DISPLAY_NAME_COLUMN_INDEX = 0;
    static const Int32 CONTACT_PHOTO_ID_COLUMN_INDEX = 1;
    static const Int32 CONTACT_LOOKUP_KEY_COLUMN_INDEX = 2;

    static const AutoPtr<ArrayOf<String> > PHONE_COLUMNS;

    static const Int32 PHONE_DISPLAY_NAME_COLUMN_INDEX = 0;
    static const Int32 PHONE_PHOTO_ID_COLUMN_INDEX = 1;
    static const Int32 PHONE_NUMBER_COLUMN_INDEX = 2;
    static const Int32 PHONE_TYPE_COLUMN_INDEX = 3;
    static const Int32 PHONE_LABEL_COLUMN_INDEX = 4;
    static const Int32 PHONE_LOOKUP_KEY_COLUMN_INDEX = 5;

    static const AutoPtr<ArrayOf<String> > PHOTO_COLUMNS;

    static const Int32 PHOTO_PHOTO_COLUMN_INDEX = 0;

    static const String PHOTO_SELECTION;

    AutoPtr<IOnShortcutIntentCreatedListener> mListener;
    AutoPtr<IContext> mContext;
    Int32 mIconSize;
    Int32 mIconDensity;
    Int32 mOverlayTextBackgroundColor;
    AutoPtr<IResources> mResources;

    friend class LoadingAsyncTask;
};

} // List
} // Common
} // Contacts
} // Droid
} // Elastos

#endif //__ELASTOS_DROID_CONTACTS_COMMON_LIST_SHORTCUTINTENTBUILDER_H__
