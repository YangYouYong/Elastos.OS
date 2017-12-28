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

#include "elastos/droid/server/net/LockdownVpnTracker.h"
// #include "elastos/droid/server/CConnectivityService.h"
#include <elastos/core/AutoLock.h>
#include <elastos/core/StringUtils.h>
#include <elastos/droid/Manifest.h>
#include <elastos/droid/R.h>
#include <elastos/droid/os/Build.h>
#include <elastos/droid/system/Os.h>
#include <elastos/droid/text/TextUtils.h>
#include <elastos/utility/Objects.h>
#include <elastos/utility/logging/Logger.h>
#include <elastos/utility/logging/Slogger.h>
#include <Elastos.Droid.App.h>
#include <Elastos.Droid.Content.h>
#include <Elastos.Droid.Internal.h>
#include <Elastos.Droid.Net.h>
#include <Elastos.Droid.Os.h>
#include <Elastos.Droid.Text.h>
#include <Elastos.Droid.Utility.h>
#include <Elastos.Droid.KeyStore.h>
#include <Elastos.CoreLibrary.Core.h>
#include <Elastos.CoreLibrary.Net.h>
#include <Elastos.CoreLibrary.Security.h>
#include <Elastos.CoreLibrary.Utility.h>

// using Elastos::Droid::Server::Connectivity::Vpn;

using Elastos::Core::AutoLock;
using Elastos::Droid::App::CPendingIntentHelper;
using Elastos::Droid::App::INotification;
using Elastos::Droid::App::CNotificationBuilder;
using Elastos::Droid::App::CNotificationManagerHelper;
using Elastos::Droid::App::INotificationBuilder;
using Elastos::Droid::App::INotificationManager;
using Elastos::Droid::App::INotificationManagerHelper;
using Elastos::Droid::App::IPendingIntentHelper;
using Elastos::Droid::Content::CIntent;
using Elastos::Droid::Content::CIntentFilter;
using Elastos::Droid::Content::IBroadcastReceiver;
using Elastos::Droid::Content::IContext;
using Elastos::Droid::Content::IIntent;
using Elastos::Droid::Content::IIntentFilter;
using Elastos::Droid::Content::Res::IResources;
using Elastos::Droid::Internal::Net::IVpnConfig;
using Elastos::Droid::Internal::Net::IVpnProfile;
using Elastos::Droid::Internal::Utility::IPreconditions;
using Elastos::Droid::Manifest;
using Elastos::Droid::Net::CConnectivityManager;
using Elastos::Droid::Net::CNetworkInfo;
using Elastos::Droid::Net::CConnectivityManagerHelper;
using Elastos::Droid::Net::IConnectivityManager;
using Elastos::Droid::Net::IConnectivityManagerHelper;
using Elastos::Droid::Net::ILinkProperties;
using Elastos::Droid::Net::INetworkInfo;
using Elastos::Droid::Net::NetworkInfoDetailedState;
using Elastos::Droid::Net::NetworkInfoDetailedState_FAILED;
using Elastos::Droid::Net::NetworkInfoState;
using Elastos::Droid::Net::NetworkInfoState_DISCONNECTED;
using Elastos::Droid::Os::Build;
using Elastos::Droid::Os::IINetworkManagementService;
using Elastos::Droid::R;
using Elastos::Droid::KeyStore::Security::ICredentials;
using Elastos::Droid::KeyStore::Security::IKeyStore;
// using Elastos::Droid::KeyStore::Security::CKeyStoreHelper;
using Elastos::Droid::KeyStore::Security::IKeyStoreHelper;
using Elastos::Droid::System::Os;
using Elastos::Droid::Text::ITextUtils;
using Elastos::Droid::Text::TextUtils;
using Elastos::Droid::Utility::ISlog;

using Elastos::Core::CString;
using Elastos::Core::ICharSequence;
using Elastos::Core::StringUtils;
using Elastos::Utility::ICollection;
using Elastos::Utility::IIterator;
using Elastos::Utility::Logging::Logger;
using Elastos::Utility::Logging::Slogger;
using Elastos::Utility::Objects;

namespace Elastos {
namespace Droid {
namespace Server {
namespace Net {

//=====================================================================
// LockdownVpnTracker::InnerSub_BroadcastReceiver
//=====================================================================
ECode LockdownVpnTracker::InnerSub_BroadcastReceiver::OnReceive(
    /* [in] */ IContext* context,
    /* [in] */ IIntent* intent)
{
    return mOwner->Reset();
}

//=====================================================================
// LockdownVpnTracker
//=====================================================================
const String LockdownVpnTracker::TAG("LockdownVpnTracker");
const Int32 LockdownVpnTracker::MAX_ERROR_COUNT = 4;
const String LockdownVpnTracker::ACTION_LOCKDOWN_RESET("com.android.server.action.LOCKDOWN_RESET");
const String LockdownVpnTracker::ACTION_VPN_SETTINGS("android.net.vpn.SETTINGS");
const String LockdownVpnTracker::EXTRA_PICK_LOCKDOWN("android.net.vpn.PICK_LOCKDOWN");
const Int32 LockdownVpnTracker::ROOT_UID = 0;

LockdownVpnTracker::LockdownVpnTracker()
    : mErrorCount(0)
{}

ECode LockdownVpnTracker::constructor(
    /* [in] */ IContext* context,
    /* [in] */ IINetworkManagementService* netService,
    /* [in] */ IIConnectivityManager* connService,
    /* [in] */ Vpn* vpn,
    /* [in] */ IVpnProfile* profile)
{
    mResetReceiver = new InnerSub_BroadcastReceiver(this);

    mContext = context;
    mNetService = netService;
    // TODO: Waiting for CConnectivityService, Vpn
    assert(0);
    // mConnService = (CConnectivityService*)connService;
    // mVpn = vpn;
    mProfile = profile;

    AutoPtr<IIntent> configIntent;
    CIntent::New(ACTION_VPN_SETTINGS, (IIntent**)&configIntent);
    configIntent->PutBooleanExtra(EXTRA_PICK_LOCKDOWN, TRUE);
    AutoPtr<IPendingIntentHelper> helper;
    CPendingIntentHelper::AcquireSingleton((IPendingIntentHelper**)&helper);
    helper->GetActivity(mContext, 0, configIntent, 0, (IPendingIntent**)&mConfigIntent);

    AutoPtr<IIntent> resetIntent;
    CIntent::New(ACTION_LOCKDOWN_RESET, (IIntent**)&resetIntent);
    resetIntent->AddFlags(IIntent::FLAG_RECEIVER_REGISTERED_ONLY);
    helper->GetBroadcast(mContext, 0, resetIntent, 0, (IPendingIntent**)&mResetIntent);
    return NOERROR;
}

Boolean LockdownVpnTracker::IsEnabled()
{
    Boolean rev = FALSE;
    Logger::W(TAG, "TODO CKeyStoreHelper not ready.");
    AutoPtr<IKeyStoreHelper> helper;
    // CKeyStoreHelper::AcquireSingleton((IKeyStoreHelper**)&helper);
    // AutoPtr<IKeyStore> keyStore;
    // helper->GetInstance((IKeyStore**)&keyStore);
    // keyStore->Contains(ICredentials::LOCKDOWN_VPN, &rev);
    return rev;
}

ECode LockdownVpnTracker::HandleStateChangedLocked()
{
    AutoPtr<INetworkInfo> egressInfo;
    // TODO: Waiting for CConnectivityService
    assert(0);
    // mConnService->GetActiveNetworkInfoUnfiltered((INetworkInfo**)&egressInfo);
    AutoPtr<ILinkProperties> egressProp;
    // mConnService->GetActiveLinkProperties((ILinkProperties**)&egressProp);

    AutoPtr<INetworkInfo> vpnInfo;
    // TODO: Waiting for Vpn
    assert(0);
    // mVpn->GetNetworkInfo((INetworkInfo**)&vpnInfo);
    AutoPtr<IVpnConfig> vpnConfig;
    // mVpn->GetLegacyVpnConfig((IVpnConfig**)&vpnConfig);

    // Restart VPN when egress network disconnected or changed
    NetworkInfoState state;
    Boolean egressDisconnected = egressInfo == NULL
            || NetworkInfoState_DISCONNECTED == (egressInfo->GetState(&state), state);
    String ifaceName;
    Boolean egressChanged = egressProp == NULL
            || (egressProp->GetInterfaceName(&ifaceName), mAcceptedEgressIface.Equals(ifaceName));

    String egressTypeName(NULL);
    if (egressInfo != NULL) {
        AutoPtr<IConnectivityManagerHelper> helper;
        CConnectivityManagerHelper::AcquireSingleton((IConnectivityManagerHelper**)&helper);
        Int32 type;
        egressInfo->GetType(&type);
        helper->GetNetworkTypeName(type, &egressTypeName);
    }
    String egressIface(NULL);
    if (egressProp != NULL) {
        egressProp->GetInterfaceName(&egressIface);
    }
    Slogger::D(TAG, "handleStateChanged: egress=%s %s->%s", egressTypeName.string(),
            mAcceptedEgressIface.string(), egressIface.string());

    if (egressDisconnected || egressChanged) {
        ClearSourceRulesLocked();
        mAcceptedEgressIface = NULL;
        // TODO: Waiting for Vpn
        assert(0);
        // mVpn->StopLegacyVpn();
    }
    if (egressDisconnected) {
        HideNotification();
        return NOERROR;
    }

    Int32 egressType;
    egressInfo->GetType(&egressType);
    NetworkInfoDetailedState dstate;
    vpnInfo->GetDetailedState(&dstate);
    if (dstate == NetworkInfoDetailedState_FAILED) {
        //EventLogTags.writeLockdownVpnError(egressType);
    }

    Boolean isConnected;
    if (mErrorCount > MAX_ERROR_COUNT) {
        ShowNotification(R::string::vpn_lockdown_error, R::drawable::vpn_disconnected);
    }
    else if ((egressInfo->IsConnected(&isConnected), isConnected) &&
            (vpnInfo->IsConnectedOrConnecting(&isConnected), !isConnected)) {
        Boolean isValid;
        mProfile->IsValidLockdownProfile(&isValid);
        if (isValid) {
            Slogger::D(TAG, "Active network connected; starting VPN");
            //EventLogTags.writeLockdownVpnConnecting(egressType);
            ShowNotification(R::string::vpn_lockdown_connecting, R::drawable::vpn_disconnected);

            egressProp->GetInterfaceName(&mAcceptedEgressIface);
                // try {
            // TODO: Waiting for KeyStore
            assert(0);
            // AutoPtr<IKeyStoreHelper> helper;
            // CKeyStoreHelper::AcquireSingleton((IKeyStoreHelper**)&helper);
            ECode ec;
            // TODO: Waiting for Vpn
            assert(0);
            // ec = mVpn->StartLegacyVpn(mProfile, Ptr(helper)->Func(helper->GetInstance), egressProp);
                // } catch (IllegalStateException e) {
            if (FAILED(ec)) {
                if (ec != (ECode)E_ILLEGAL_STATE_EXCEPTION) return ec;
                mAcceptedEgressIface = NULL;
                Slogger::E(TAG, "Failed to start VPN %d", ec);
                ShowNotification(R::string::vpn_lockdown_error, R::drawable::vpn_disconnected);
            }
                // }
        }
        else {
            Slogger::E(TAG, "Invalid VPN profile; requires IP-based server and DNS");
            ShowNotification(R::string::vpn_lockdown_error, R::drawable::vpn_disconnected);
        }
    }
    else if ((vpnInfo->IsConnected(&isConnected), isConnected) && vpnConfig != NULL) {
        String iface;
        AutoPtr<IList> sourceAddrs;
        vpnConfig->GetInterfaze(&iface);
        vpnConfig->GetAddresses((IList**)&sourceAddrs);

        if (TextUtils::Equals(iface, mAcceptedIface)
                && Objects::Equals(sourceAddrs, mAcceptedSourceAddr)) {
            return NOERROR;
        }

        Slogger::D(TAG, "VPN connected using iface=%s, sourceAddr=%s", iface.string(), TO_CSTR(sourceAddrs));
        //EventLogTags.writeLockdownVpnConnected(egressType);
        ShowNotification(R::string::vpn_lockdown_connected, R::drawable::vpn_connected);

        // try {
        ClearSourceRulesLocked();

        ECode ec;
        Int32 uid;
        AutoPtr<IIterator> it;
        FAIL_GOTO(ec = mNetService->SetFirewallInterfaceRule(iface, TRUE), catch_lable)
        ICollection::Probe(sourceAddrs)->GetIterator((IIterator**)&it);
        Boolean hasNext;
        while (it->HasNext(&hasNext), hasNext) {
            AutoPtr<IInterface> addr;
            it->GetNext((IInterface**)&addr);
            FAIL_GOTO(ec = SetFirewallEgressSourceRule(ILinkAddress::Probe(addr), TRUE), catch_lable)
        }

        FAIL_GOTO(ec = mNetService->SetFirewallUidRule(ROOT_UID, TRUE), catch_lable)
        Elastos::Droid::System::Os::Getuid(&uid);
        FAIL_GOTO(ec = mNetService->SetFirewallUidRule(uid, TRUE), catch_lable)

        mErrorCount = 0;
        mAcceptedIface = iface;
        mAcceptedSourceAddr = sourceAddrs;
catch_lable:
        // } catch (RemoteException e) {
        if (FAILED(ec)) {
            if (ec == (ECode)E_REMOTE_EXCEPTION)
            {
                Logger::E(TAG, "Problem setting firewall rules %d", ec);
                return E_RUNTIME_EXCEPTION;
            }
            return ec;
        }
        // }

        AutoPtr<INetworkInfo> info = AugmentNetworkInfo(egressInfo);
        // TODO: Waiting for CConnectivityService
        assert(0);
        // mConnService->SendConnectedBroadcast(info);
    }
    return NOERROR;
}

ECode LockdownVpnTracker::Init()
{
    AutoLock lock(mStateLock);
    return InitLocked();
}

ECode LockdownVpnTracker::InitLocked()
{
    Slogger::D(TAG, "initLocked()");

    // TODO: Waiting for Vpn
    assert(0);
    // mVpn->SetEnableTeardown(FALSE);

    AutoPtr<IIntentFilter> resetFilter;
    CIntentFilter::New(ACTION_LOCKDOWN_RESET, (IIntentFilter**)&resetFilter);
    AutoPtr<IIntent> intent;
    mContext->RegisterReceiver(mResetReceiver, resetFilter,
            Elastos::Droid::Manifest::permission::CONNECTIVITY_INTERNAL, NULL, (IIntent**)&intent);

    // try {
    // TODO: support non-standard port numbers
    String server;
    mProfile->GetServer(&server);
    ECode ec;
    do {
        if (FAILED(ec = mNetService->SetFirewallEgressDestRule(server, 500, TRUE))) break;
        if (FAILED(ec = mNetService->SetFirewallEgressDestRule(server, 4500, TRUE))) break;
        if (FAILED(ec = mNetService->SetFirewallEgressDestRule(server, 1701, TRUE))) break;
    } while(FALSE);
    // } catch (RemoteException e) {
    if (FAILED(ec)) {
        if (ec == (ECode)E_REMOTE_EXCEPTION) {
            Logger::E(TAG, "Problem setting firewall rules %d", ec);
            return E_RUNTIME_EXCEPTION;
        }
        return ec;
    }
    // }

    {
        AutoLock syncLock(mStateLock);
        HandleStateChangedLocked();
    }
    return NOERROR;
}

ECode LockdownVpnTracker::Shutdown()
{
    AutoLock lock(mStateLock);
    return ShutdownLocked();
}

ECode LockdownVpnTracker::ShutdownLocked()
{
    Slogger::D(TAG, "shutdownLocked()");

    mAcceptedEgressIface = NULL;
    mErrorCount = 0;

    // TODO: Waiting for Vpn
    assert(0);
    // mVpn->StopLegacyVpn();
    //try {
    String server;
    mProfile->GetServer(&server);
    ECode ec;
    do {
        if (FAILED(ec = mNetService->SetFirewallEgressDestRule(server, 500, FALSE))) break;
        if (FAILED(ec = mNetService->SetFirewallEgressDestRule(server, 4500, FALSE))) break;
        if (FAILED(ec = mNetService->SetFirewallEgressDestRule(server, 1701, FALSE))) break;
    } while(FALSE);
    //} catch (RemoteException e) {
    if (FAILED(ec)) {
        if ((ECode)E_REMOTE_EXCEPTION == ec) {
            Logger::E(TAG, "Problem setting firewall rules %d", ec);
            return E_RUNTIME_EXCEPTION;
        }
        return ec;
    }
    //}
    ClearSourceRulesLocked();
    HideNotification();

    mContext->UnregisterReceiver(mResetReceiver);
    // TODO: Waiting for Vpn
    assert(0);
    // mVpn->SetEnableTeardown(TRUE);
    return NOERROR;
}

ECode LockdownVpnTracker::Reset()
{
    Slogger::D(TAG, "reset()");
    {
        AutoLock syncLock(mStateLock);
        // cycle tracker, reset error count, and trigger retry
        ShutdownLocked();
        InitLocked();
        HandleStateChangedLocked();
    }
    return NOERROR;
}

ECode LockdownVpnTracker::ClearSourceRulesLocked()
{
    //try {
    ECode ec = NOERROR;
    if (!mAcceptedIface.IsNull()) {
        FAIL_GOTO(ec = mNetService->SetFirewallInterfaceRule(mAcceptedIface, FALSE), label)
        mAcceptedIface = NULL;
    }
    if (mAcceptedSourceAddr != NULL) {
        AutoPtr<IIterator> it;
        mAcceptedSourceAddr->GetIterator((IIterator**)&it);
        Boolean hasNext;
        while (it->HasNext(&hasNext), hasNext) {
            AutoPtr<IInterface> addr;
            it->GetNext((IInterface**)&addr);
            FAIL_GOTO(ec = SetFirewallEgressSourceRule(ILinkAddress::Probe(addr), FALSE), label)
        }

        FAIL_GOTO(ec = mNetService->SetFirewallUidRule(ROOT_UID, FALSE), label)

        Int32 uid;
        Elastos::Droid::System::Os::Getuid(&uid);
        FAIL_GOTO(ec = mNetService->SetFirewallUidRule(uid, FALSE), label)

        mAcceptedSourceAddr = NULL;
    }
label:
    //} catch (RemoteException e) {
    if (FAILED(ec)) {
        if ((ECode)E_REMOTE_EXCEPTION == ec) {
            Logger::E(TAG, "Problem setting firewall rules %d", ec);
            return E_RUNTIME_EXCEPTION;
        }
        return ec;
    }
    //}
    return NOERROR;
}

ECode LockdownVpnTracker::SetFirewallEgressSourceRule(
    /* [in] */ ILinkAddress* address,
    /* [in] */ Boolean allow)
{
    // Our source address based firewall rules must only cover our own source address, not the
    // whole subnet
    AutoPtr<IInetAddress> addr;
    address->GetAddress((IInetAddress**)&addr);
    String addrString;
    addr->GetHostAddress(&addrString);
    return mNetService->SetFirewallEgressSourceRule(addrString, allow);
}

ECode LockdownVpnTracker::OnNetworkInfoChanged()
{
    {
        AutoLock syncLock(mStateLock);
        return HandleStateChangedLocked();
    }
    return NOERROR;
}

ECode LockdownVpnTracker::OnVpnStateChanged(
    /* [in] */ INetworkInfo* info)
{
    NetworkInfoDetailedState state;
    info->GetDetailedState(&state);
    if (state == NetworkInfoDetailedState_FAILED) {
        mErrorCount++;
    }

    {
        AutoLock lock(mStateLock);
        return HandleStateChangedLocked();
    }
}

AutoPtr<INetworkInfo> LockdownVpnTracker::AugmentNetworkInfo(
    /* [in] */ INetworkInfo* _info)
{
    AutoPtr<INetworkInfo> info = _info;
    Boolean isConnected;
    info->IsConnected(&isConnected);
    if (isConnected) {
        AutoPtr<INetworkInfo> vpnInfo;
        // TODO: Waiting for Vpn
        assert(0);
        // mVpn->GetNetworkInfo((INetworkInfo**)&vpnInfo);
        info = NULL;
        CNetworkInfo::New(_info, (INetworkInfo**)&info);
        NetworkInfoDetailedState state;
        vpnInfo->GetDetailedState(&state);
        String reason;
        vpnInfo->GetReason(&reason);
        info->SetDetailedState(state, reason, String(NULL));
    }
    return info;
}

void LockdownVpnTracker::ShowNotification(
    /* [in] */ Int32 titleRes,
    /* [in] */ Int32 iconRes)
{
    AutoPtr<INotificationBuilder> builder;
    CNotificationBuilder::New(mContext, (INotificationBuilder**)&builder);
    builder->SetWhen(0);
    builder->SetSmallIcon(iconRes);
    String value;
    mContext->GetString(titleRes, &value);
    AutoPtr<ICharSequence> csValue;
    CString::New(value, (ICharSequence**)&csValue);
    builder->SetContentTitle(csValue);
    mContext->GetString(R::string::vpn_lockdown_config, &value);
    csValue = NULL;
    CString::New(value, (ICharSequence**)&csValue);
    builder->SetContentText(csValue);
    builder->SetContentIntent(mConfigIntent);
    builder->SetPriority(INotification::PRIORITY_LOW);
    builder->SetOngoing(TRUE);
    mContext->GetString(R::string::reset, &value);
    builder->AddAction(R::drawable::ic_menu_refresh, StringUtils::ParseCharSequence(value), mResetIntent);
    AutoPtr<IResources> resources;
    mContext->GetResources((IResources**)&resources);
    Int32 color;
    resources->GetColor(R::color::system_notification_accent_color, &color);
    builder->SetColor(color);

    AutoPtr<INotification> notification;
    builder->Build((INotification**)&notification);

    AutoPtr<INotificationManagerHelper> helper;
    CNotificationManagerHelper::AcquireSingleton((INotificationManagerHelper**)&helper);
    AutoPtr<INotificationManager> notificationManager;
    helper->From(mContext, (INotificationManager**)&notificationManager);
    notificationManager->Notify(TAG, 0, notification);
}

void LockdownVpnTracker::HideNotification()
{
    AutoPtr<INotificationManagerHelper> helper;
    CNotificationManagerHelper::AcquireSingleton((INotificationManagerHelper**)&helper);
    AutoPtr<INotificationManager> notificationManager;
    helper->From(mContext, (INotificationManager**)&notificationManager);
    notificationManager->Cancel(TAG, 0);
}

} // namespace Net
} // namespace Server
} // namepsace Droid
} // namespace Elastos
