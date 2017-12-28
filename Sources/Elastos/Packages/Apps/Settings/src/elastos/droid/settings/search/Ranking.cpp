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

#include "elastos/droid/settings/search/Ranking.h"
#include <elastos/core/AutoLock.h>
#include <elastos/core/CoreUtils.h>

using Elastos::Core::AutoLock;
using Elastos::Core::CoreUtils;
using Elastos::Core::IInteger32;
using Elastos::Utility::CHashMap;

namespace Elastos {
namespace Droid {
namespace Settings {
namespace Search {

const Int32 Ranking::RANK_WIFI = 1;
const Int32 Ranking::RANK_BT = 2;
const Int32 Ranking::RANK_SIM = 3;
const Int32 Ranking::RANK_DATA_USAGE = 4;
const Int32 Ranking::RANK_WIRELESS = 5;
const Int32 Ranking::RANK_HOME = 6;
const Int32 Ranking::RANK_DISPLAY = 7;
const Int32 Ranking::RANK_WALLPAPER = 8;
const Int32 Ranking::RANK_NOTIFICATIONS = 9;
const Int32 Ranking::RANK_MEMORY = 10;
const Int32 Ranking::RANK_POWER_USAGE = 11;
const Int32 Ranking::RANK_USERS = 12;
const Int32 Ranking::RANK_LOCATION = 13;
const Int32 Ranking::RANK_SECURITY = 14;
const Int32 Ranking::RANK_IME = 15;
const Int32 Ranking::RANK_PRIVACY = 16;
const Int32 Ranking::RANK_DATE_TIME = 17;
const Int32 Ranking::RANK_ACCESSIBILITY = 18;
const Int32 Ranking::RANK_PRINTING = 19;
const Int32 Ranking::RANK_DEVELOPEMENT = 20;
const Int32 Ranking::RANK_DEVICE_INFO = 21;

const Int32 Ranking::RANK_UNDEFINED = -1;
const Int32 Ranking::RANK_OTHERS = 1024;
const Int32 Ranking::BASE_RANK_DEFAULT = 2048;

Int32 Ranking::sCurrentBaseRank = BASE_RANK_DEFAULT;

static Boolean InitPut(
    /* [in] */ IHashMap* map,
    /* [in] */ const String& className,
    /* [in] */ Int32 id)
{
    map->Put(CoreUtils::Convert(className), CoreUtils::Convert(id));
    return TRUE;
}

static AutoPtr<IHashMap> InitsRankMap()
{
    AutoPtr<IHashMap> map;
    CHashMap::New((IHashMap**)&map);

    // Wi-Fi
    InitPut(map, String("Elastos.Droid.Settings.Wifi.CWifiSettings"),
            Ranking::RANK_WIFI);
    InitPut(map, String("Elastos.Droid.Settings.Wifi.CAdvancedWifiSettings"),
            Ranking::RANK_WIFI);
    InitPut(map,
            String("Elastos.Droid.Settings.Wifi.CSavedAccessPointsWifiSettings"),
            Ranking::RANK_WIFI);

    // BT
    InitPut(map, String("Elastos.Droid.Settings.Bluetooth.CBluetoothSettings"),
            Ranking::RANK_BT);

    // SIM Cards
    InitPut(map, String("Elastos.Droid.Settings.Sim.CSimSettings"),
            Ranking::RANK_SIM);

    // DataUsage
    InitPut(map, String("Elastos.Droid.Settings.CDataUsageSummary"),
            Ranking::RANK_DATA_USAGE);
    InitPut(map, String("Elastos.Droid.Settings.Net.CDataUsageMeteredSettings"),
            Ranking::RANK_DATA_USAGE);

    // Other wireless settinfs
    InitPut(map, String("Elastos.Droid.Settings.CWirelessSettings"),
            Ranking::RANK_WIRELESS);

    // Home
    InitPut(map, String("Elastos.Droid.Settings.CHomeSettings"),
            Ranking::RANK_HOME);

    // Display
    InitPut(map, String("Elastos.Droid.Settings.CDisplaySettings"),
            Ranking::RANK_DISPLAY);

    // Wallpapers
    InitPut(map, String("Elastos.Droid.Settings.CWallpaperTypeSettings"),
            Ranking::RANK_WALLPAPER);

    // Notifications
    InitPut(map,
            String("Elastos.Droid.Settings.Notification.CNotificationSettings"),
            Ranking::RANK_NOTIFICATIONS);
    InitPut(map,
            String("Elastos.Droid.Settings.Notification.COtherSoundSettings"),
            Ranking::RANK_NOTIFICATIONS);
    InitPut(map,
            String("Elastos.Droid.Settings.Notification.CZenModeSettings"),
            Ranking::RANK_NOTIFICATIONS);

    // Memory
    InitPut(map, String("Elastos.Droid.Settings.Deviceinfo.CMemory"),
            Ranking::RANK_MEMORY);

    // Battery
    InitPut(map,
            String("Elastos.Droid.Settings.Fuelgauge.CPowerUsageSummary"),
            Ranking::RANK_POWER_USAGE);
    InitPut(map,
            String("Elastos.Droid.Settings.Fuelgauge.CBatterySaverSettings"),
            Ranking::RANK_POWER_USAGE);

    // Users
    InitPut(map, String("Elastos.Droid.Settings.Users.CUserSettings"),
            Ranking::RANK_USERS);

    // Location
    InitPut(map,
            String("Elastos.Droid.Settings.Location.CLocationSettings"),
            Ranking::RANK_LOCATION);

    // Security
    InitPut(map, String("Elastos.Droid.Settings.CSecuritySettings"),
            Ranking::RANK_SECURITY);
    InitPut(map,
            String("Elastos.Droid.Settings.CChooseLockGenericFragment"),
            Ranking::RANK_SECURITY);
    InitPut(map, String("Elastos.Droid.Settings.CScreenPinningSettings"),
            Ranking::RANK_SECURITY);

    // IMEs
    InitPut(map,
            String("Elastos.Droid.Settings.Inputmethod.CInputMethodAndLanguageSettings"),
            Ranking::RANK_IME);
    InitPut(map, String("Elastos.Droid.Settings.Voice.CVoiceInputSettings"),
            Ranking::RANK_IME);

    // Privacy
    InitPut(map, String("Elastos.Droid.Settings.CPrivacySettings"),
            Ranking::RANK_PRIVACY);

    // Date / Time
    InitPut(map, String("Elastos.Droid.Settings.CDateTimeSettings"),
            Ranking::RANK_DATE_TIME);

    // Accessibility
    InitPut(map,
            String("Elastos.Droid.Settings.Accessibility.CAccessibilitySettings"),
            Ranking::RANK_ACCESSIBILITY);

    // Print
    InitPut(map, String("Elastos.Droid.Settings.Print.CPrintSettingsFragment"),
            Ranking::RANK_PRINTING);

    // Development
    InitPut(map, String("Elastos.Droid.Settings.CDevelopmentSettings"),
            Ranking::RANK_DEVELOPEMENT);

    // Device infos
    InitPut(map, String("Elastos.Droid.Settings.CDeviceInfoSettings"),
            Ranking::RANK_DEVICE_INFO);

    return map;
}

AutoPtr<IHashMap> Ranking::sRankMap = InitsRankMap();

static AutoPtr<IHashMap> InitsBaseRankMap()
{
    AutoPtr<IHashMap> map;
    CHashMap::New((IHashMap**)&map);

    InitPut(map, String("Elastos.Droid.Settings"), 0);
    return map;
}

AutoPtr<IHashMap> Ranking::sBaseRankMap = InitsBaseRankMap();

Int32 Ranking::GetRankForClassName(
    /* [in] */ const String& className)
{
    AutoPtr<IInterface> obj;
    sRankMap->Get(CoreUtils::Convert(className), (IInterface**)&obj);
    IInteger32* rank = IInteger32::Probe(obj);
    if (rank != NULL) {
        Int32 value;
        rank->GetValue(&value);
        return value;
    }
    return RANK_OTHERS;
}

Int32 Ranking::GetBaseRankForAuthority(
    /* [in] */ const String& authority)
{
    {
        AutoLock syncLock(sBaseRankMap);
        AutoPtr<IInterface> obj;
        sBaseRankMap->Get(CoreUtils::Convert(authority), (IInterface**)&obj);
        IInteger32* base = IInteger32::Probe(obj);

        if (base != NULL) {
            Int32 value;
            base->GetValue(&value);
            return value;
        }

        sCurrentBaseRank++;
        sBaseRankMap->Put(CoreUtils::Convert(authority), CoreUtils::Convert(sCurrentBaseRank));
        return sCurrentBaseRank;
    }
    return 0;
}

} // namespace Search
} // namespace Settings
} // namespace Droid
} // namespace Elastos
