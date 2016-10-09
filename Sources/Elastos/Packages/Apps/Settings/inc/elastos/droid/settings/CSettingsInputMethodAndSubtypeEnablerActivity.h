
#ifndef __ELASTOS_DROID_SETTINGS_CSETTINGSINPUTMETHODANDSUBTYPEENABLERACTIVITY_H__
#define __ELASTOS_DROID_SETTINGS_CSETTINGSINPUTMETHODANDSUBTYPEENABLERACTIVITY_H__

#include "elastos/droid/settings/CSettings.h"
#include "_Elastos_Droid_Settings_CSettingsInputMethodAndSubtypeEnablerActivity.h"

using Elastos::Droid::Settings::CSettings;

namespace Elastos {
namespace Droid {
namespace Settings {

CarClass(CSettingsInputMethodAndSubtypeEnablerActivity)
    , public CSettings::InputMethodAndSubtypeEnablerActivity
{
public:
    CAR_OBJECT_DECL()
};

} // namespace Settings
} // namespace Droid
} // namespace Elastos

#endif //__ELASTOS_DROID_SETTINGS_CSETTINGSINPUTMETHODANDSUBTYPEENABLERACTIVITY_H__
