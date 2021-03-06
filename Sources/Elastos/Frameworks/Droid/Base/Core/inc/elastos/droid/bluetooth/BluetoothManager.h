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

#ifndef __ELASTOS_DROID_BLUETOOTH_BLUETOOTHMANAGER_H__
#define __ELASTOS_DROID_BLUETOOTH_BLUETOOTHMANAGER_H__

#include "Elastos.Droid.Bluetooth.h"
#include <elastos/core/Object.h>
#include "elastos/droid/ext/frameworkext.h"

using Elastos::Droid::Content::IContext;
using Elastos::Utility::IList;

namespace Elastos {
namespace Droid {
namespace Bluetooth {

/**
  * High level manager used to obtain an instance of an {@link BluetoothAdapter}
  * and to conduct overall Bluetooth Management.
  * <p>
  * Use {@link android.content.Context#getSystemService(java.lang.String)}
  * with {@link Context#BLUETOOTH_SERVICE} to create an {@link BluetoothManager},
  * then call {@link #getAdapter} to obtain the {@link BluetoothAdapter}.
  * <p>
  * Alternately, you can just call the static helper
  * {@link BluetoothAdapter#getDefaultAdapter()}.
  *
  * <div class="special reference">
  * <h3>Developer Guides</h3>
  * <p>For more information about using BLUETOOTH, read the
  * <a href="{@docRoot}guide/topics/connectivity/bluetooth.html">Bluetooth</a> developer guide.</p>
  * </div>
  *
  * @see Context#getSystemService
  * @see BluetoothAdapter#getDefaultAdapter()
  */
class BluetoothManager
    : public Object
    , public IBluetoothManager
{
public:
    CAR_INTERFACE_DECL()

    BluetoothManager();

    /**
      * @hide
      */
    CARAPI constructor(
        /* [in] */ IContext* context);

    /**
      * Get the default BLUETOOTH Adapter for this device.
      *
      * @return the default BLUETOOTH Adapter
      */
    CARAPI GetAdapter(
        /* [out] */ IBluetoothAdapter** result);

    /**
      * Get the current connection state of the profile to the remote device.
      *
      * <p>This is not specific to any application configuration but represents
      * the connection state of the local Bluetooth adapter for certain profile.
      * This can be used by applications like status bar which would just like
      * to know the state of Bluetooth.
      *
      * <p>Requires {@link android.Manifest.permission#BLUETOOTH} permission.
      *
      * @param device Remote bluetooth device.
      * @param profile GATT or GATT_SERVER
      * @return State of the profile connection. One of
      *         {@link BluetoothProfile#STATE_CONNECTED}, {@link BluetoothProfile#STATE_CONNECTING},
      *         {@link BluetoothProfile#STATE_DISCONNECTED},
      *         {@link BluetoothProfile#STATE_DISCONNECTING}
      */
    CARAPI GetConnectionState(
        /* [in] */ IBluetoothDevice* device,
        /* [in] */ Int32 profile,
        /* [out] */ Int32* result);

    /**
      * Get connected devices for the specified profile.
      *
      * <p> Return the set of devices which are in state {@link BluetoothProfile#STATE_CONNECTED}
      *
      * <p>This is not specific to any application configuration but represents
      * the connection state of Bluetooth for this profile.
      * This can be used by applications like status bar which would just like
      * to know the state of Bluetooth.
      *
      * <p>Requires {@link android.Manifest.permission#BLUETOOTH} permission.
      *
      * @param profile GATT or GATT_SERVER
      * @return List of devices. The list will be empty on error.
      */
    CARAPI GetConnectedDevices(
        /* [in] */ Int32 profile,
        /* [out] */ IList** result);// BluetoothDevice

    /**
      *
      * Get a list of devices that match any of the given connection
      * states.
      *
      * <p> If none of the devices match any of the given states,
      * an empty list will be returned.
      *
      * <p>This is not specific to any application configuration but represents
      * the connection state of the local Bluetooth adapter for this profile.
      * This can be used by applications like status bar which would just like
      * to know the state of the local adapter.
      *
      * <p>Requires {@link android.Manifest.permission#BLUETOOTH} permission.
      *
      * @param profile GATT or GATT_SERVER
      * @param states Array of states. States can be one of
      *        {@link BluetoothProfile#STATE_CONNECTED}, {@link BluetoothProfile#STATE_CONNECTING},
      *        {@link BluetoothProfile#STATE_DISCONNECTED},
      *        {@link BluetoothProfile#STATE_DISCONNECTING},
      * @return List of devices. The list will be empty on error.
      */
    CARAPI GetDevicesMatchingConnectionStates(
        /* [in] */ Int32 profile,
        /* [in] */ ArrayOf<Int32>* states,
        /* [out] */ IList** result);// BluetoothDevice

    /**
      * Open a GATT Server
      * The callback is used to deliver results to Caller, such as connection status as well
      * as the results of any other GATT server operations.
      * The method returns a BluetoothGattServer instance. You can use BluetoothGattServer
      * to conduct GATT server operations.
      * @param context App context
      * @param callback GATT server callback handler that will receive asynchronous callbacks.
      * @return BluetoothGattServer instance
      */
    CARAPI OpenGattServer(
        /* [in] */ IContext* context,
        /* [in] */ IBluetoothGattServerCallback* callback,
        /* [out] */ IBluetoothGattServer** result);

    /**
      * Open a GATT Server
      * The callback is used to deliver results to Caller, such as connection status as well
      * as the results of any other GATT server operations.
      * The method returns a BluetoothGattServer instance. You can use BluetoothGattServer
      * to conduct GATT server operations.
      * @param context App context
      * @param callback GATT server callback handler that will receive asynchronous callbacks.
      * @param transport preferred transport for GATT connections to remote dual-mode devices
      *             {@link BluetoothDevice#TRANSPORT_AUTO} or
      *             {@link BluetoothDevice#TRANSPORT_BREDR} or {@link BluetoothDevice#TRANSPORT_LE}
      * @return BluetoothGattServer instance
      * @hide
      */
    CARAPI OpenGattServer(
        /* [in] */ IContext* context,
        /* [in] */ IBluetoothGattServerCallback* callback,
        /* [in] */ Int32 transport,
        /* [out] */ IBluetoothGattServer** result);

private:
    static const String TAG;
    static const Boolean DBG;
    static const Boolean VDBG;
    AutoPtr<IBluetoothAdapter> mAdapter;
};

} // namespace Bluetooth
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_BLUETOOTH_BLUETOOTHMANAGER_H__
