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

#include "elastos/droid/launcher2/InstallShortcutReceiver.h"
#include "elastos/droid/launcher2/LauncherSettings.h"
#include "elastos/droid/launcher2/ItemInfo.h"
#include "elastos/droid/launcher2/LauncherModel.h"
#include "elastos/droid/launcher2/LauncherApplication.h"
#include "elastos/droid/launcher2/CellLayout.h"
#include "Elastos.Droid.Service.h"
#include "Elastos.Droid.Utility.h"
#include "Elastos.Droid.Widget.h"
#include "Elastos.CoreLibrary.External.h"
#include <elastos/core/AutoLock.h>
#include <elastos/core/CoreUtils.h>
#include <elastos/utility/logging/Slogger.h>
#include "R.h"

using Elastos::Droid::Content::Pm::IPackageItemInfo;
using Elastos::Droid::Content::IIntentHelper;
using Elastos::Droid::Content::CIntentHelper;
using Elastos::Droid::Content::Pm::IActivityInfo;
using Elastos::Droid::Content::IComponentName;
using Elastos::Droid::Content::Pm::IPackageManager;
using Elastos::Droid::Content::CIntentShortcutIconResource;
using Elastos::Droid::Content::IIntentShortcutIconResource;
using Elastos::Droid::Graphics::IBitmapFactory;
using Elastos::Droid::Graphics::CBitmapFactory;
using Elastos::Droid::Utility::CBase64;
using Elastos::Droid::Utility::IBase64;
using Elastos::Droid::Widget::IToast;
using Elastos::Droid::Widget::CToastHelper;
using Elastos::Droid::Widget::IToastHelper;
using Elastos::Core::AutoLock;
using Elastos::Core::CoreUtils;
using Elastos::Core::ICharSequence;
using Elastos::Utility::ISet;
using Elastos::Utility::CHashSet;
using Elastos::Utility::ICollection;
using Elastos::Utility::IIterator;
using Elastos::Utility::CArrayList;
using Elastos::Utility::Logging::Slogger;
using Org::Json::CJSONStringer;
using Org::Json::IJSONStringer;
using Org::Json::CJSONTokener;
using Org::Json::IJSONTokener;
using Org::Json::CJSONObject;
using Org::Json::IJSONObject;

namespace Elastos {
namespace Droid {
namespace Launcher2 {

InstallShortcutReceiver::PendingInstallShortcutInfo::PendingInstallShortcutInfo(
    /* [in] */ IIntent* rawData,
    /* [in] */ const String& shortcutName,
    /* [in] */ IIntent* shortcutIntent)
    : mData(rawData)
    , mLaunchIntent(shortcutIntent)
    , mName(shortcutName)
{
}

InstallShortcutReceiver::MyThread::MyThread(
    /* [in] */ const String& name,
    /* [in] */ ISharedPreferences* sharedPrefs,
    /* [in] */ Int32 screen,
    /* [in] */ IIntent* intent)
    : mSharedPrefs(sharedPrefs)
    , mScreen(screen)
    , mIntent(intent)
{
    Thread::constructor(name);
}

ECode InstallShortcutReceiver::MyThread::Run()
{
    {
        AutoLock syncLock(sLock);
        // If the new app is going to fall into the same page as before,
        // then just continue adding to the current page
        Int32 newAppsScreen;
        mSharedPrefs->GetInt32(InstallShortcutReceiver::NEW_APPS_PAGE_KEY,
                mScreen, &newAppsScreen);
        AutoPtr<ISharedPreferencesEditor> editor;
        mSharedPrefs->Edit((ISharedPreferencesEditor**)&editor);
        if (newAppsScreen == -1 || newAppsScreen == mScreen) {
            String str;
            mIntent->ToUri(0, &str);
            AddToStringSet(mSharedPrefs,
                editor, InstallShortcutReceiver::NEW_APPS_LIST_KEY,
                str);
        }
        editor->PutInt32(InstallShortcutReceiver::NEW_APPS_PAGE_KEY, mScreen);
        Boolean res;
        editor->Commit(&res);
    }
    return NOERROR;
}

const Int32 InstallShortcutReceiver::INSTALL_SHORTCUT_SUCCESSFUL = 0;
const Int32 InstallShortcutReceiver::INSTALL_SHORTCUT_IS_DUPLICATE = -1;
const Int32 InstallShortcutReceiver::INSTALL_SHORTCUT_NO_SPACE = -2;

Object InstallShortcutReceiver::sLock;

// Determines whether to defer installing shortcuts immediately until
// processAllPendingInstalls() is called.
Boolean InstallShortcutReceiver::mUseInstallQueue = FALSE;

CAR_INTERFACE_IMPL(InstallShortcutReceiver, BroadcastReceiver, IInstallShortcutReceiver);

ECode InstallShortcutReceiver::AddToStringSet(
    /* [in] */ ISharedPreferences* sharedPrefs,
    /* [in] */ ISharedPreferencesEditor* editor,
    /* [in] */ const String& key,
    /* [in] */ const String& value)
{
    AutoPtr<ISet> strings;
    sharedPrefs->GetStringSet(key, NULL, (ISet**)&strings);
    if (strings == NULL) {
        CHashSet::New(0, (ISet**)&strings);
    }
    else {
        CHashSet::New(ICollection::Probe(strings), (ISet**)&strings);
    }
    AutoPtr<ICharSequence> chars = CoreUtils::Convert(value);
    strings->Add(TO_IINTERFACE(chars));
    return editor->PutStringSet(key, strings);
}

ECode InstallShortcutReceiver::AddToInstallQueue(
    /* [in] */ ISharedPreferences* sharedPrefs,
    /* [in] */ PendingInstallShortcutInfo* info)
{
    {
        AutoLock syncLock(sLock);
    //try
    {
        AutoPtr<IJSONStringer> json;
        CJSONStringer::New((IJSONStringer**)&json);
        FAIL_GOTO(json->Object(), EXIT)
        FAIL_GOTO(json->Key(DATA_INTENT_KEY), EXIT)
        String str;
        info->mData->ToUri(0, &str);
        AutoPtr<ICharSequence> cchar = CoreUtils::Convert(str);
        FAIL_GOTO(json->Value(TO_IINTERFACE(cchar)), EXIT)
        FAIL_GOTO(json->Key(LAUNCH_INTENT_KEY), EXIT)
        String str2;
        info->mLaunchIntent->ToUri(0, &str2);
        AutoPtr<ICharSequence> cchar2 = CoreUtils::Convert(str2);
        FAIL_GOTO(json->Value(TO_IINTERFACE(cchar2)), EXIT)
        FAIL_GOTO(json->Key(NAME_KEY), EXIT)
        AutoPtr<ICharSequence> cchar3 = CoreUtils::Convert(info->mName);
        FAIL_GOTO(json->Value(TO_IINTERFACE(cchar3)), EXIT)
        if (info->mIcon != NULL) {
            AutoPtr<ArrayOf<Byte> > iconByteArray = ItemInfo::FlattenBitmap(info->mIcon);
            FAIL_GOTO(json->Key(ICON_KEY), EXIT)
            AutoPtr<IBase64> base64;
            CBase64::AcquireSingleton((IBase64**)&base64);
            String str;
            base64->EncodeToString(iconByteArray, 0, iconByteArray->GetLength(),
                    IBase64::DEFAULT, &str);
            AutoPtr<ICharSequence> obj = CoreUtils::Convert(str);
            FAIL_GOTO(json->Value(obj), EXIT)
        }
        if (info->mIconResource != NULL) {
            FAIL_GOTO(json->Key(ICON_RESOURCE_NAME_KEY), EXIT)
            String resourceName;
            info->mIconResource->GetResourceName(&resourceName);
            AutoPtr<ICharSequence> obj = CoreUtils::Convert(resourceName);
            FAIL_GOTO(json->Value(obj), EXIT)
            FAIL_GOTO(json->Key(ICON_RESOURCE_PACKAGE_NAME_KEY), EXIT)
            String packageName;
            info->mIconResource->GetPackageName(&packageName);
            AutoPtr<ICharSequence> obj2 = CoreUtils::Convert(packageName);
            FAIL_GOTO(json->Value(obj2), EXIT)
        }
        FAIL_GOTO(json->EndObject(), EXIT)
        AutoPtr<ISharedPreferencesEditor> editor;
        sharedPrefs->Edit((ISharedPreferencesEditor**)&editor);
        String res;
        IObject::Probe(json)->ToString(&res);
        AddToStringSet(sharedPrefs, editor, APPS_PENDING_INSTALL, res);
        Boolean tmp;
        editor->Commit(&tmp);
    }
    //} catch (org.json.JSONException e) {
EXIT:
    Slogger::D("InstallShortcutReceiver", "Exception when adding shortcut");
    //}
    }
    return NOERROR;
}

AutoPtr<IArrayList> InstallShortcutReceiver::GetAndClearInstallQueue(
    /* [in] */ ISharedPreferences* sharedPrefs)
{
    {
        AutoLock syncLock(sLock);
        AutoPtr<ISet> strings;
        sharedPrefs->GetStringSet(APPS_PENDING_INSTALL, NULL, (ISet**)&strings);
        if (strings == NULL) {
            AutoPtr<IArrayList> list;
            CArrayList::New((IArrayList**)&list);
            return list;
        }
        AutoPtr<IArrayList> infos;
        CArrayList::New((IArrayList**)&infos);

        AutoPtr<ArrayOf<IInterface*> > array;
        strings->ToArray((ArrayOf<IInterface*>**)&array);
        for (Int32 i = 0; i < array->GetLength(); i++) {
            AutoPtr<ICharSequence> cobj = ICharSequence::Probe((*array)[i]);
            String json;
            cobj->ToString(&json);

            //try {
            AutoPtr<IJSONTokener> tokener;
            CJSONTokener::New(json, (IJSONTokener**)&tokener);
            AutoPtr<IInterface> obj;
            tokener->NextValue((IInterface**)&obj);
            AutoPtr<IJSONObject> object = IJSONObject::Probe(obj);

            String key;
            object->GetString(DATA_INTENT_KEY, &key);
            AutoPtr<IIntent> data;
            AutoPtr<IIntentHelper> helper;
            CIntentHelper::AcquireSingleton((IIntentHelper**)&helper);
            helper->ParseUri(key, 0, (IIntent**)&data);

            String key2;
            object->GetString(LAUNCH_INTENT_KEY, &key2);
            AutoPtr<IIntent> launchIntent;
            helper->ParseUri(key2, 0, (IIntent**)&launchIntent);

            String name;
            object->GetString(NAME_KEY, &name);
            String iconBase64;
            object->OptString(ICON_KEY, &iconBase64);
            String iconResourceName;
            object->OptString(ICON_RESOURCE_NAME_KEY, &iconResourceName);
            String iconResourcePackageName;
            object->OptString(ICON_RESOURCE_PACKAGE_NAME_KEY, &iconResourcePackageName);

            if (iconBase64 != NULL && !iconBase64.IsEmpty()) {
                AutoPtr<IBase64> base64;
                CBase64::AcquireSingleton((IBase64**)&base64);
                AutoPtr<ArrayOf<Byte> > iconArray;
                base64->Decode(iconBase64, IBase64::DEFAULT, (ArrayOf<Byte>**)&iconArray);

                AutoPtr<IBitmapFactory> factory;
                CBitmapFactory::AcquireSingleton((IBitmapFactory**)&factory);
                AutoPtr<IBitmap> b;
                factory->DecodeByteArray(iconArray, 0, iconArray->GetLength(), (IBitmap**)&b);

                data->PutExtra(IIntent::EXTRA_SHORTCUT_ICON, IParcelable::Probe(b));
            }
            else if (iconResourceName != NULL && !iconResourceName.IsEmpty()) {
                AutoPtr<IIntentShortcutIconResource> iconResource;
                CIntentShortcutIconResource::New((IIntentShortcutIconResource**)&iconResource);
                iconResource->SetResourceName(iconResourceName);
                iconResource->SetPackageName(iconResourcePackageName);
                data->PutExtra(IIntent::EXTRA_SHORTCUT_ICON_RESOURCE, IParcelable::Probe(iconResource));
            }
            data->PutExtra(IIntent::EXTRA_SHORTCUT_INTENT, IParcelable::Probe(launchIntent));
            AutoPtr<PendingInstallShortcutInfo> info =
                    new PendingInstallShortcutInfo(data, name, launchIntent);
            infos->Add(TO_IINTERFACE(info));
            // } catch (org.json.JSONException e) {
            //     Log.d("InstallShortcutReceiver", "Exception reading shortcut to add: " + e);
            // } catch (java.net.URISyntaxException e) {
            //     Log.d("InstallShortcutReceiver", "Exception reading shortcut to add: " + e);
            // }
        }

        AutoPtr<ISharedPreferencesEditor> edit;
        sharedPrefs->Edit((ISharedPreferencesEditor**)&edit);
        AutoPtr<ISet> set;
        CHashSet::New((ISet**)&set);
        edit->PutStringSet(APPS_PENDING_INSTALL, set);
        Boolean res;
        edit->Commit(&res);
        return infos;
    }
    return NULL;
}

InstallShortcutReceiver::InstallShortcutReceiver()
{}

ECode InstallShortcutReceiver::constructor()
{
    return BroadcastReceiver::constructor();
}

ECode InstallShortcutReceiver::OnReceive(
    /* [in] */ IContext* context,
    /* [in] */ IIntent* data)
{
    String action;
    data->GetAction(&action);
    if (!ACTION_INSTALL_SHORTCUT.Equals(action)) {
        return NOERROR;
    }

    AutoPtr<IParcelable> p;
    data->GetParcelableExtra(IIntent::EXTRA_SHORTCUT_INTENT, (IParcelable**)&p);
    AutoPtr<IIntent> intent = IIntent::Probe(p);
    if (intent == NULL) {
        return NOERROR;
    }
    // This name is only used for comparisons and notifications, so fall back to activity name
    // if not supplied
    String name;
    data->GetStringExtra(IIntent::EXTRA_SHORTCUT_NAME, &name);
    if (name.IsNull()) {
        //try {
        AutoPtr<IPackageManager> pm;
        ECode ec = context->GetPackageManager((IPackageManager**)&pm);
        if (ec == (ECode)E_NAME_NOT_FOUND_EXCEPTION) return NOERROR;
        AutoPtr<IComponentName> componentName;
        ec = intent->GetComponent((IComponentName**)&componentName);
        if (ec == (ECode)E_NAME_NOT_FOUND_EXCEPTION) return NOERROR;
        AutoPtr<IActivityInfo> info;
        ec = pm->GetActivityInfo(componentName, 0, (IActivityInfo**)&info);
        if (ec == (ECode)E_NAME_NOT_FOUND_EXCEPTION) return NOERROR;
        AutoPtr<ICharSequence> label;
        ec = IPackageItemInfo::Probe(info)->LoadLabel(pm, (ICharSequence**)&label);
        if (ec == (ECode)E_NAME_NOT_FOUND_EXCEPTION) return NOERROR;
        label->ToString(&name);
        //} catch (PackageManager.NameNotFoundException nnfe) {
        //    return;
        //}
    }
    AutoPtr<IParcelable> p2;
    data->GetParcelableExtra(IIntent::EXTRA_SHORTCUT_ICON, (IParcelable**)&p2);
    AutoPtr<IBitmap> icon = IBitmap::Probe(p2);

    AutoPtr<IParcelable> p3;
    data->GetParcelableExtra(IIntent::EXTRA_SHORTCUT_ICON_RESOURCE,
            (IParcelable**)&p3);
    AutoPtr<IIntentShortcutIconResource> iconResource = IIntentShortcutIconResource::Probe(p3);

    // Queue the item up for adding if launcher has not loaded properly yet
    Int32 x;
    LauncherModel::GetCellCountX(&x);
    Int32 y;
    LauncherModel::GetCellCountY(&y);
    Boolean launcherNotLoaded = x <= 0 || y <= 0;

    AutoPtr<PendingInstallShortcutInfo> info =
            new PendingInstallShortcutInfo(data, name, intent);
    info->mIcon = icon;
    info->mIconResource = iconResource;
    if (mUseInstallQueue || launcherNotLoaded) {
        String spKey;
        LauncherApplication::GetSharedPreferencesKey(&spKey);
        AutoPtr<ISharedPreferences> sp;
        context->GetSharedPreferences(spKey, IContext::MODE_PRIVATE,
                (ISharedPreferences**)&sp);
        AddToInstallQueue(sp, info);
    }
    else {
        ProcessInstallShortcut(context, info);
    }
    return NOERROR;
}

ECode InstallShortcutReceiver::EnableInstallQueue()
{
    mUseInstallQueue = TRUE;
    return NOERROR;
}

ECode InstallShortcutReceiver::DisableAndFlushInstallQueue(
    /* [in] */ IContext* context)
{
    mUseInstallQueue = FALSE;
    return FlushInstallQueue(context);
}

ECode InstallShortcutReceiver::FlushInstallQueue(
    /* [in] */ IContext* context)
{
    String spKey;
    LauncherApplication::GetSharedPreferencesKey(&spKey);
    AutoPtr<ISharedPreferences> sp;
    context->GetSharedPreferences(spKey, IContext::MODE_PRIVATE,
            (ISharedPreferences**)&sp);
    AutoPtr<IArrayList> installQueue = GetAndClearInstallQueue(sp);

    AutoPtr<IIterator> iter;
    installQueue->GetIterator((IIterator**)&iter);
    Boolean res;
    while (iter->HasNext(&res), res) {
        AutoPtr<IInterface> obj;
        iter->GetNext((IInterface**)&obj);
        PendingInstallShortcutInfo* info = (PendingInstallShortcutInfo*)IObject::Probe(obj);
        ProcessInstallShortcut(context, info);
    }
    return NOERROR;
}

void InstallShortcutReceiver::ProcessInstallShortcut(
    /* [in] */ IContext* context,
    /* [in] */ PendingInstallShortcutInfo* pendingInfo)
{
    String spKey;
    LauncherApplication::GetSharedPreferencesKey(&spKey);
    AutoPtr<ISharedPreferences> sp;
    context->GetSharedPreferences(spKey, IContext::MODE_PRIVATE,
            (ISharedPreferences**)&sp);

    AutoPtr<IIntent> data = pendingInfo->mData;
    AutoPtr<IIntent> intent = pendingInfo->mLaunchIntent;
    String name = pendingInfo->mName;

    // Lock on the app so that we don't try and get the items while apps are being added
    AutoPtr<IContext> ctx;
    context->GetApplicationContext((IContext**)&ctx);
    AutoPtr<ILauncherApplication> app = ILauncherApplication::Probe(ctx);
    AutoPtr<ArrayOf<Int32> > result = ArrayOf<Int32>::Alloc(1);
    (*result)[0] = INSTALL_SHORTCUT_SUCCESSFUL;
    Boolean found = FALSE;
    {
        AutoLock syncLock(app);
        // Flush the LauncherModel worker thread, so that if we just did another
        // processInstallShortcut, we give it time for its shortcut to get added to the
        // database (getItemsInLocalCoordinates reads the database)
        AutoPtr<ILauncherModel> modle;
        app->GetModel((ILauncherModel**)&modle);
        modle->FlushWorkerThread();
        AutoPtr<IArrayList> items;
        LauncherModel::GetItemsInLocalCoordinates(context, (IArrayList**)&items);
        Boolean exists;
        LauncherModel::ShortcutExists(context, name, intent, &exists);

        // Try adding to the workspace screens incrementally, starting at the default or center
        // screen and alternating between +1, -1, +2, -2, etc. (using ~ ceil(i/2f)*(-1)^(i-1))
        const Int32 screen = ILauncher::DEFAULT_SCREEN;
        for (Int32 i = 0; i < (2 * ILauncher::SCREEN_COUNT) + 1 && !found; ++i) {
            Int32 si = screen + (Int32)((i / 2.0f) + 0.5f) * ((i % 2 == 1) ? 1 : -1);
            if (0 <= si && si < ILauncher::SCREEN_COUNT) {
                found = InstallShortcut(context, data, items, name, intent, si, exists, sp,
                        result);
            }
        }
    }

    // We only report error messages (duplicate shortcut or out of space) as the add-animation
    // will provide feedback otherwise
    if (!found) {
        if ((*result)[0] == INSTALL_SHORTCUT_NO_SPACE) {
            String str;
            context->GetString(Elastos::Droid::Launcher2::R::
                    string::completely_out_of_space, &str);

            AutoPtr<IToastHelper> helper;
            CToastHelper::AcquireSingleton((IToastHelper**)&helper);
            AutoPtr<ICharSequence> text = CoreUtils::Convert(str);
            AutoPtr<IToast> toast;
            helper->MakeText(context, text,
                    IToast::LENGTH_SHORT, (IToast**)&toast);
            toast->Show();
        }
        else if ((*result)[0] == INSTALL_SHORTCUT_IS_DUPLICATE) {
            AutoPtr<ArrayOf<IInterface*> > array = ArrayOf<IInterface*>::Alloc(1);
            AutoPtr<ICharSequence> cchar = CoreUtils::Convert(name);
            array->Set(0, TO_IINTERFACE(cchar));
            String str;
            context->GetString(Elastos::Droid::Launcher2::R::string::shortcut_duplicate, array, &str);
            AutoPtr<IToastHelper> helper;
            CToastHelper::AcquireSingleton((IToastHelper**)&helper);
            AutoPtr<ICharSequence> text = CoreUtils::Convert(str);
            AutoPtr<IToast> toast;
            helper->MakeText(context, text,
                    IToast::LENGTH_SHORT, (IToast**)&toast);
            toast->Show();
        }
    }
}

Boolean InstallShortcutReceiver::InstallShortcut(
    /* [in] */ IContext* context,
    /* [in] */ IIntent* data,
    /* [in] */ IArrayList* items,
    /* [in] */ const String& name,
    /* [in] */ IIntent* intent,
    /* [in] */ Int32 screen,
    /* [in] */ Boolean shortcutExists,
    /* [in] */ ISharedPreferences* sharedPrefs,
    /* [in] */ ArrayOf<Int32>* result)
{
    AutoPtr<ArrayOf<Int32> > tmpCoordinates = ArrayOf<Int32>::Alloc(2);
    if (FindEmptyCell(context, items, tmpCoordinates, screen)) {
        if (intent != NULL) {
            String action;
            intent->GetAction(&action);
            if (action.IsNull()) {
                intent->SetAction(IIntent::ACTION_VIEW);
            }
            else if (action.Equals(IIntent::ACTION_MAIN)){
                AutoPtr<ArrayOf<String> > categories;
                intent->GetCategories((ArrayOf<String>**)&categories);
                if (categories != NULL) {
                    Boolean res2 = FALSE;
                    for (Int32 i = 0; i < categories->GetLength(); i++){
                        if((*categories)[i].Equals(IIntent::CATEGORY_LAUNCHER)) {
                            res2 = TRUE;
                            break;
                        }
                    }
                    if (res2) {
                        intent->AddFlags(
                                IIntent::FLAG_ACTIVITY_NEW_TASK |
                                IIntent::FLAG_ACTIVITY_RESET_TASK_IF_NEEDED);
                    }
                }
            }

            // By default, we allow for duplicate entries (located in
            // different places)
            Boolean duplicate;
            data->GetBooleanExtra(ILauncher::EXTRA_SHORTCUT_DUPLICATE, TRUE, &duplicate);
            if (duplicate || !shortcutExists) {
                AutoPtr<MyThread> t = new MyThread(String("setNewAppsThread"),
                    sharedPrefs, screen, intent);
                t->Start();

                // Update the Launcher db
                AutoPtr<IContext> ctx;
                context->GetApplicationContext((IContext**)&ctx);
                AutoPtr<ILauncherApplication> app = ILauncherApplication::Probe(ctx);
                AutoPtr<ILauncherModel> model;
                app->GetModel((ILauncherModel**)&model);
                AutoPtr<IShortcutInfo> info;
                model->AddShortcut(context, data,
                        LauncherSettings::Favorites::CONTAINER_DESKTOP, screen,
                        (*tmpCoordinates)[0], (*tmpCoordinates)[1], TRUE, (IShortcutInfo**)&info);
                if (info == NULL) {
                    return FALSE;
                }
            }
            else {
                (*result)[0] = INSTALL_SHORTCUT_IS_DUPLICATE;
            }

            return TRUE;
        }
    }
    else {
        (*result)[0] = INSTALL_SHORTCUT_NO_SPACE;
    }

    return FALSE;
}

Boolean InstallShortcutReceiver::FindEmptyCell(
    /* [in] */ IContext* context,
    /* [in] */ IArrayList* items,
    /* [in] */ ArrayOf<Int32>* xy,
    /* [in] */ Int32 screen)
{
    Int32 xCount;
    LauncherModel::GetCellCountX(&xCount);
    Int32 yCount;
    LauncherModel::GetCellCountY(&yCount);
    AutoPtr<ArrayOf<ArrayOf<Boolean>* > > occupied = ArrayOf<ArrayOf<Boolean>* >::Alloc(xCount);
    for (Int32 i = 0; i < xCount; i++) {
        (*occupied)[i] = ArrayOf<Boolean>::Alloc(yCount);
    }

    AutoPtr<IItemInfo> item;
    Int32 cellX, cellY, spanX, spanY;
    Int32 size;
    items->GetSize(&size);
    for (Int32 i = 0; i < size; ++i) {
        AutoPtr<IInterface> obj;
        items->Get(i, (IInterface**)&obj);
        item = IItemInfo::Probe(obj);
        ItemInfo* _info = (ItemInfo*)item.Get();
        if (_info->mContainer == LauncherSettings::Favorites::CONTAINER_DESKTOP) {
            if (_info->mScreen == screen) {
                cellX = _info->mCellX;
                cellY = _info->mCellY;
                spanX = _info->mSpanX;
                spanY = _info->mSpanY;
                for (Int32 x = cellX; 0 <= x && x < cellX + spanX && x < xCount; x++) {
                    for (Int32 y = cellY; 0 <= y && y < cellY + spanY && y < yCount; y++) {
                        (*((*occupied)[x]))[y] = TRUE;
                    }
                }
            }
        }
    }
    Boolean tmp;
    CellLayout::FindVacantCell(xy, 1, 1, xCount, yCount,
            occupied.Get(), &tmp);
    return tmp;
}

} // namespace Launcher2
} // namespace Droid
} // namespace Elastos