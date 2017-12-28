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


#include "Elastos.Droid.Content.h"
#include "Elastos.Droid.Os.h"
#include "elastos/droid/graphics/TemporaryBuffer.h"
#include "elastos/droid/internal/utility/ArrayUtils.h"
#include <elastos/core/AutoLock.h>

using Elastos::Core::AutoLock;
using Elastos::Droid::Internal::Utility::ArrayUtils;

namespace Elastos {
namespace Droid {
namespace Graphics {

AutoPtr< ArrayOf<Char32> > TemporaryBuffer::sTemp;
Object TemporaryBuffer::sObject;

AutoPtr< ArrayOf<Char32> > TemporaryBuffer::Obtain(
    /* [in] */ Int32 len)
{
    AutoPtr< ArrayOf<Char32> > buf;

    {
        AutoLock syncLock(sObject);
        buf = sTemp;
        sTemp = NULL;
    }

    if (buf == NULL || buf->GetLength() < len) {
        buf = ArrayUtils::NewUnpaddedChar32Array(len);
    }

    return buf;
}

void TemporaryBuffer::Recycle(
    /* [in] */ ArrayOf<Char32>* temp)
{
    if (temp->GetLength() > 1000) return;

    {
        AutoLock syncLock(sObject);
        sTemp = temp;
    }
}

} // namespace Graphics
} // namepsace Droid
} // namespace Elastos
