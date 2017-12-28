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

#include "elastos/droid/systemui/doze/DozeLog.h"
#include "Elastos.CoreLibrary.IO.h"
#include "Elastos.CoreLibrary.Utility.h"
#include <elastos/core/AutoLock.h>
#include <elastos/core/StringBuilder.h>
#include <elastos/core/Math.h>
#include <elastos/droid/os/Build.h>
#include <elastos/droid/utility/TimeUtils.h>
#include <elastos/utility/logging/Logger.h>

using Elastos::Droid::Os::Build;
using Elastos::Droid::Utility::TimeUtils;
using Elastos::Core::AutoLock;
using Elastos::Core::StringBuilder;
using Elastos::Core::CSystem;
using Elastos::Core::ISystem;
using Elastos::Text::CSimpleDateFormat;
using Elastos::Text::IDateFormat;
using Elastos::Utility::CDate;
using Elastos::Utility::IDate;
using Elastos::Utility::Logging::Logger;

namespace Elastos {
namespace Droid {
namespace SystemUI {
namespace Doze {

//===============================================================
// DozeLog::
//===============================================================
String DozeLog::TAG("DozeLog");
Boolean DozeLog::DEBUG = FALSE;//Logger::IsLoggable(TAG, Logger::___DEBUG);
Boolean DozeLog::ENABLED = TRUE;
Int32 DozeLog::SIZE = Build::IS_DEBUGGABLE ? 400 : 50;
AutoPtr<ISimpleDateFormat> DozeLog::FORMAT;
AutoPtr<ArrayOf<Int64> > DozeLog::sTimes;
AutoPtr<ArrayOf<String> > DozeLog::sMessages;
Int32 DozeLog::sPosition = 0;
Int32 DozeLog::sCount = 0;
Boolean DozeLog::sPulsing = FALSE;
Int64 DozeLog::sSince = 0;
AutoPtr<DozeLog::SummaryStats> DozeLog::sPickupPulseNearVibrationStats;
AutoPtr<DozeLog::SummaryStats> DozeLog::sPickupPulseNotNearVibrationStats;
AutoPtr<DozeLog::SummaryStats> DozeLog::sNotificationPulseStats;
AutoPtr<DozeLog::SummaryStats> DozeLog::sScreenOnPulsingStats;
AutoPtr<DozeLog::SummaryStats> DozeLog::sScreenOnNotPulsingStats;
AutoPtr<DozeLog::SummaryStats> DozeLog::sEmergencyCallStats;
AutoPtr<DozeLog::SummaryStats> DozeLog::sProxNearStats;
AutoPtr<DozeLog::SummaryStats> DozeLog::sProxFarStats;
Boolean DozeLog::sInit = InitStatic();
Object DozeLog::sDozeLog;

Boolean DozeLog::InitStatic()
{
    CSimpleDateFormat::New(String("MM-dd HH:mm:ss.SSS"), (ISimpleDateFormat**)&FORMAT);
    return TRUE;
}

void DozeLog::TracePickupPulse(
    /* [in] */ Boolean withinVibrationThreshold)
{
    if (!ENABLED) return;
    StringBuilder sb("pickupPulse withinVibrationThreshold="); sb += withinVibrationThreshold;
    Log(sb.ToString());
    (withinVibrationThreshold ? sPickupPulseNearVibrationStats.Get()
            : sPickupPulseNotNearVibrationStats.Get())->Append();
}

void DozeLog::TracePulseStart()
{
    if (!ENABLED) return;
    sPulsing = TRUE;
    return Log(String("pulseStart"));
}

void DozeLog::TracePulseFinish()
{
    if (!ENABLED) return;
    sPulsing = FALSE;
    return Log(String("pulseFinish"));
}

void DozeLog::TraceNotificationPulse(
    /* [in] */ Int64 instance)
{
    if (!ENABLED) return;
    StringBuilder sb("notificationPulse instance="); sb += instance;
    Log(sb.ToString());
    sNotificationPulseStats->Append();
}

void DozeLog::TraceDozing(
    /* [in] */ IContext* context,
    /* [in] */ Boolean dozing)
{
    if (!ENABLED) return;
    sPulsing = FALSE;
    {
        AutoLock syncLock(sDozeLog);
        if (dozing && sMessages == NULL) {
            sTimes = ArrayOf<Int64>::Alloc(SIZE);
            sMessages = ArrayOf<String>::Alloc(SIZE);
            AutoPtr<ISystem> system;
            Elastos::Core::CSystem::AcquireSingleton((ISystem**)&system);
            system->GetCurrentTimeMillis(&sSince);
            sPickupPulseNearVibrationStats = new SummaryStats();
            sPickupPulseNotNearVibrationStats = new SummaryStats();
            sNotificationPulseStats = new SummaryStats();
            sScreenOnPulsingStats = new SummaryStats();
            sScreenOnNotPulsingStats = new SummaryStats();
            sEmergencyCallStats = new SummaryStats();
            sProxNearStats = new SummaryStats();
            sProxFarStats = new SummaryStats();
            Log(String("init"));
            assert(0 && "TODO");
            // KeyguardUpdateMonitor.getInstance(context).registerCallback(sKeyguardCallback);
        }
    }
    StringBuilder sb("dozing "); sb += dozing;
    Log(sb.ToString());
}

void DozeLog::TraceFling(
    /* [in] */ Boolean expand,
    /* [in] */ Boolean aboveThreshold,
    /* [in] */ Boolean thresholdNeeded,
    /* [in] */ Boolean screenOnFromTouch)
{
    if (!ENABLED) return;
    // Log(String("fling expand=") + (Char32)expand + " aboveThreshold=" + (Char32)aboveThreshold + " thresholdNeeded="
    //         + (Char32)thresholdNeeded + " screenOnFromTouch=" + (Char32)screenOnFromTouch);
}

void DozeLog::TraceEmergencyCall()
{
    if (!ENABLED) return;
    Log(String("emergencyCall"));
    sEmergencyCallStats->Append();
}

void DozeLog::TraceKeyguardBouncerChanged(
    /* [in] */ Boolean showing)
{
    if (!ENABLED) return;
    StringBuilder sb("bouncer "); sb += showing;
    Log(sb.ToString());
}

void DozeLog::TraceScreenOn()
{
    if (!ENABLED) return;
    StringBuilder sb("screenOn pulsing="); sb += sPulsing;
    Log(sb.ToString());
    (sPulsing ? sScreenOnPulsingStats : sScreenOnNotPulsingStats)->Append();
    sPulsing = FALSE;
}

void DozeLog::TraceScreenOff(
    /* [in] */ Int32 why)
{
    if (!ENABLED) return;
    StringBuilder sb("keyguard"); sb += why;
    Log(sb.ToString());
}

void DozeLog::TraceKeyguard(
    /* [in] */ Boolean showing)
{
    if (!ENABLED) return;
    StringBuilder sb("keyguard"); sb += showing;
    Log(sb.ToString());
    if (!showing) {
        sPulsing = FALSE;
    }
}

void DozeLog::TraceProximityResult(
    /* [in] */ Boolean near,
    /* [in] */ Int64 millis)
{
    if (!ENABLED) return;
    StringBuilder sb("proximityResult near="); sb += near; sb += " millis="; sb += millis;
    Log(sb.ToString());
    (near ? sProxNearStats : sProxFarStats)->Append();
}

void DozeLog::Dump(
    /* [in] */ IPrintWriter* pw)
{
    {
        AutoLock syncLock(sDozeLog);
        if (sMessages == NULL) return;
        pw->Println(String("  Doze log:"));
        Int32 start = (sPosition - sCount + SIZE) % SIZE;
        for (Int32 i = 0; i < sCount; i++) {
            Int32 j = (start + i) % SIZE;
            pw->Print(String("    "));
            AutoPtr<IDate> date;
            CDate::New((*sTimes)[j], (IDate**)&date);
            String str;
            IDateFormat::Probe(FORMAT)->Format(date, &str);
            pw->Print(str);
            pw->PrintChar(' ');
            pw->Println((*sMessages)[j]);
        }
        pw->Print(String("  Doze summary stats (for "));
        AutoPtr<ISystem> system;
        Elastos::Core::CSystem::AcquireSingleton((ISystem**)&system);
        Int64 when = 0;
        system->GetCurrentTimeMillis(&when);
        TimeUtils::FormatDuration(when - sSince, pw);
        pw->Println(String("):"));
        sPickupPulseNearVibrationStats->Dump(pw, String("Pickup pulse (near vibration)"));
        sPickupPulseNotNearVibrationStats->Dump(pw, String("Pickup pulse (not near vibration)"));
        sNotificationPulseStats->Dump(pw, String("Notification pulse"));
        sScreenOnPulsingStats->Dump(pw, String("Screen on (pulsing)"));
        sScreenOnNotPulsingStats->Dump(pw, String("Screen on (not pulsing)"));
        sEmergencyCallStats->Dump(pw, String("Emergency call"));
        sProxNearStats->Dump(pw, String("Proximity (near)"));
        sProxFarStats->Dump(pw, String("Proximity (far)"));
    }
}

void DozeLog::Log(
    /* [in] */ const String& msg)
{
    {
        AutoLock syncLock(sDozeLog);
        if (sMessages == NULL) return;
        AutoPtr<ISystem> system;
        Elastos::Core::CSystem::AcquireSingleton((ISystem**)&system);
        system->GetCurrentTimeMillis(&((*sTimes)[sPosition]));
        (*sMessages)[sPosition] = msg;
        sPosition = (sPosition + 1) % SIZE;
        sCount = Elastos::Core::Math::Min(sCount + 1, SIZE);
    }
    if (DEBUG) Logger::D(TAG, msg);
}

//===============================================================
// DozeLog::SummaryStats
//===============================================================
void DozeLog::SummaryStats::Append()
{
    mCount++;
}

void DozeLog::SummaryStats::Dump(
    /* [in] */ IPrintWriter* pw,
    /* [in] */ const String& type)
{
    pw->Print(String("    "));
    pw->Print(type);
    pw->Print(String(": n="));
    pw->Print(mCount);
    pw->Print(String(" ("));
    AutoPtr<ISystem> system;
    Elastos::Core::CSystem::AcquireSingleton((ISystem**)&system);
    Int64 mills = 0;
    system->GetCurrentTimeMillis(&mills);
    double perHr = (double) mCount / (mills - sSince)
            * 1000 * 60 * 60;
    pw->Print(perHr);
    pw->Print(String("/hr)"));
    pw->Println();
}

//===============================================================
// DozeLog::KeyguardUpdateMonitorCallback
//===============================================================
void DozeLog::KeyguardUpdateMonitorCallback::OnEmergencyCallAction()
{
    TraceEmergencyCall();
}

void DozeLog::KeyguardUpdateMonitorCallback::OnKeyguardBouncerChanged(
    /* [in] */ Boolean bouncer)
{
    TraceKeyguardBouncerChanged(bouncer);
}

void DozeLog::KeyguardUpdateMonitorCallback::OnScreenTurnedOn()
{
    TraceScreenOn();
}

void DozeLog::KeyguardUpdateMonitorCallback::OnScreenTurnedOff(
    /* [in] */ Int32 why)
{
    TraceScreenOff(why);
}

void DozeLog::KeyguardUpdateMonitorCallback::OnKeyguardVisibilityChanged(
    /* [in] */ Boolean showing)
{
    TraceKeyguard(showing);
}

} // namespace Doze
} // namespace SystemUI
} // namespace Droid
} // namespace Elastos
