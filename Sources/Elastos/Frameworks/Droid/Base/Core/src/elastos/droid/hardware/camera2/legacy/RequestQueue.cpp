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

#include <Elastos.CoreLibrary.Utility.h>
#include "elastos/droid/hardware/camera2/legacy/RequestQueue.h"
#include "elastos/droid/hardware/camera2/legacy/CBurstHolder.h"
#include "elastos/droid/utility/CPairHelper.h"
#include <elastos/core/AutoLock.h>
#include <elastos/core/CoreUtils.h>
#include <elastos/utility/logging/Logger.h>

using Elastos::Droid::Utility::IPairHelper;
using Elastos::Droid::Utility::CPairHelper;
using Elastos::Core::AutoLock;
using Elastos::Core::IInteger64;
using Elastos::Utility::IDeque;
using Elastos::Utility::CArrayDeque;
using Elastos::Utility::ICollection;
using Elastos::Utility::Logging::Logger;

namespace Elastos {
namespace Droid {
namespace Hardware {
namespace Camera2 {
namespace Legacy {

CAR_INTERFACE_IMPL(RequestQueue, Object, IRequestQueue)

const String RequestQueue::TAG("RequestQueue");
const Int64 RequestQueue::INVALID_FRAME = -1;

RequestQueue::RequestQueue()
    : mCurrentFrameNumber(0)
    , mCurrentRepeatingFrameNumber(INVALID_FRAME)
    , mCurrentRequestId(0)
{
}

ECode RequestQueue::constructor()
{
    return NOERROR;
}

ECode RequestQueue::constructor(
    /* [in] */ IList* jpegSurfaceIds)
{
    mJpegSurfaceIds = jpegSurfaceIds;
    CArrayDeque::New((IArrayDeque**)&mRequestQueue);
    return NOERROR;
}

ECode RequestQueue::GetNext(
    /* [out] */ IPair** outpair)
{
    VALIDATE_NOT_NULL(outpair)
    *outpair = NULL;

    {
        AutoLock syncLock(this);
        AutoPtr<IInterface> obj;
        IDeque::Probe(mRequestQueue)->Poll((IInterface**)&obj);
        AutoPtr<IBurstHolder> next = IBurstHolder::Probe(obj);
        if (next == NULL && mRepeatingRequest != NULL) {
            next = mRepeatingRequest;
            Int32 value;
            next->GetNumberOfRequests(&value);
            mCurrentRepeatingFrameNumber = mCurrentFrameNumber + value;
        }

        if (next == NULL) {
            *outpair = NULL;
            return  NOERROR;
        }

        AutoPtr<IPairHelper> helper;
        CPairHelper::AcquireSingleton((IPairHelper**)&helper);
        AutoPtr<IPair> ret;
        AutoPtr<IInteger64> num = CoreUtils::Convert(mCurrentFrameNumber);
        helper->Create(TO_IINTERFACE(next), TO_IINTERFACE(num), (IPair**)&ret);

        Int32 value;
        next->GetNumberOfRequests(&value);
        mCurrentFrameNumber += value;
        *outpair = ret;
        REFCOUNT_ADD(*outpair);
    }
    return NOERROR;
}

ECode RequestQueue::StopRepeating(
    /* [in] */ Int32 requestId,
    /* [out] */ Int64* value)
{
    VALIDATE_NOT_NULL(value)
    *value = 0;

    {
        AutoLock syncLock(this);
        Int64 ret = INVALID_FRAME;
        if (mRepeatingRequest != NULL) {
            Int32 id;
            mRepeatingRequest->GetRequestId(&id);
            if (id == requestId) {
                mRepeatingRequest = NULL;
                ret = (mCurrentRepeatingFrameNumber == INVALID_FRAME) ? INVALID_FRAME :
                        mCurrentRepeatingFrameNumber - 1;
                mCurrentRepeatingFrameNumber = INVALID_FRAME;
                Logger::I(TAG, "Repeating capture request cancelled.");
            }
        }
        else {
            Logger::E(TAG, "cancel failed: no repeating request exists for request id: %d", requestId);
        }
        *value = ret;
    }
    return NOERROR;
}

ECode RequestQueue::StopRepeating(
    /* [out] */ Int64* value)
{
    VALIDATE_NOT_NULL(value)
    *value = 0;

    {
        AutoLock syncLock(this);
        if (mRepeatingRequest == NULL) {
            Logger::E(TAG, "cancel failed: no repeating request exists.");
            *value = INVALID_FRAME;
            return NOERROR;
        }

        Int32 id;
        mRepeatingRequest->GetRequestId(&id);
        StopRepeating(id, value);
    }
    return NOERROR;
}

ECode RequestQueue::Submit(
    /* [in] */ IList* requests,
    /* [in] */ Boolean repeating,
    /* [in] */ ILongParcelable* frameNumber,
    /* [out] */ Int32* value)
{
    VALIDATE_NOT_NULL(value)
    *value = 0;

    {
        AutoLock syncLock(this);
        Int32 requestId = mCurrentRequestId++;
        AutoPtr<IBurstHolder> burst;
        CBurstHolder::New(requestId, repeating, requests,
                ICollection::Probe(mJpegSurfaceIds), (IBurstHolder**)&burst);
        Int64 ret = INVALID_FRAME;

        Boolean result;
        burst->IsRepeating(&result);
        if (result) {
            Logger::I(TAG, "Repeating capture request set.");
            if (mRepeatingRequest != NULL) {
                ret = (mCurrentRepeatingFrameNumber == INVALID_FRAME) ? INVALID_FRAME :
                        mCurrentRepeatingFrameNumber - 1;
            }
            mCurrentRepeatingFrameNumber = INVALID_FRAME;
            mRepeatingRequest = burst;
        }
        else {
            IDeque::Probe(mRequestQueue)->Offer(TO_IINTERFACE(burst), &result);
            Int32 id;
            burst->GetRequestId(&id);
            FAIL_RETURN(CalculateLastFrame(id, &ret))
        }
        frameNumber->SetNumber(ret);
        *value = requestId;
    }
    return NOERROR;
}

ECode RequestQueue::CalculateLastFrame(
    /* [in] */ Int32 requestId,
    /* [out] */ Int64* result)
{
    VALIDATE_NOT_NULL(result)
    *result = 0;

    Int64 total = mCurrentFrameNumber;
    Int32 size;
    mRequestQueue->GetSize(&size);
    AutoPtr<ArrayOf<IInterface*> > array = ArrayOf<IInterface*>::Alloc(size);
    mRequestQueue->ToArray((ArrayOf<IInterface*>**)&array);

    for (Int32 i = 0; i < size; i++) {
        AutoPtr<IInterface> obj = (*array)[i];
        AutoPtr<IBurstHolder> b = IBurstHolder::Probe(obj);

        Int32 num;
        b->GetNumberOfRequests(&num);
        total += num;
        Int32 id;
        b->GetRequestId(&id);
        if (id == requestId) {
            *result = total - 1;
            return NOERROR;
        }
    }

    // throw new IllegalStateException(
    //         "At least one request must be in the queue to calculate frame number");
    Logger::E(TAG, "At least one request must be in the queue to calculate frame number");
    return E_ILLEGAL_STATE_EXCEPTION;
}

} // namespace Legacy
} // namespace Camera2
} // namespace Hardware
} // namespace Droid
} // namespace Elastos
