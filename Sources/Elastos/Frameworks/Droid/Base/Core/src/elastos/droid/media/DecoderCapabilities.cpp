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

#include "elastos/droid/media/DecoderCapabilities.h"
#include <elastos/core/AutoLock.h>
#include <elastos/utility/etl/List.h>
#include <media/MediaProfiles.h>

using Elastos::Core::AutoLock;
using Elastos::Utility::Etl::List;

namespace Elastos {
namespace Droid {
namespace Media {

DecoderCapabilities::StaticInitializer::StaticInitializer()
{
    Native_init();
}

//=================================================================================
//              DecoderCapabilities
//=================================================================================
static Object sLock;
android::MediaProfiles *ssProfiles = NULL;

const DecoderCapabilities::StaticInitializer DecoderCapabilities::sInitializer;

ECode DecoderCapabilities::GetVideoDecoders(
    /* [out, callee] */ ArrayOf<VideoDecoder>** result)
{
    VALIDATE_NOT_NULL(result);

    Int32 nDecoders = Native_get_num_video_decoders();
    AutoPtr<ArrayOf<VideoDecoder> > vd = ArrayOf<VideoDecoder>::Alloc(nDecoders);
    for (Int32 i = 0; i < nDecoders; i++) {
        vd->Set(i, VIDEO_DECODER_WMV);
        // decoderList->PushBack(VideoDecoder.values()[Native_get_video_decoder_type(i)]);
    }

    *result = vd;
    REFCOUNT_ADD(*result);
    return NOERROR;
}

ECode DecoderCapabilities::GetAudioDecoders(
    /* [out, callee] */ ArrayOf<AudioDecoder>** result)
{
    VALIDATE_NOT_NULL(result);

    Int32 nDecoders = Native_get_num_audio_decoders();
    AutoPtr<ArrayOf<AudioDecoder> > ad = ArrayOf<AudioDecoder>::Alloc(nDecoders);
    for (Int32 i = 0; i < nDecoders; i++) {
        ad->Set(i, AUDIO_DECODER_WMA);
        // decoderList->PushBack(AudioDecoder.values()[Native_get_audio_decoder_type(i)]);
    }

    *result = ad;
    REFCOUNT_ADD(*result);
    return NOERROR;
}

//---------------------------------------------------
//    Native method : android_media_MediaProfiles.cpp
//---------------------------------------------------

void DecoderCapabilities::Native_init()
{
    // ALOGV("native_init");
    {
        AutoLock syncLock(sLock);
        if (ssProfiles == NULL) {
            ssProfiles = android::MediaProfiles::getInstance();
        }
    }
}

Int32 DecoderCapabilities::Native_get_num_video_decoders()
{
    // ALOGV("native_get_num_video_decoders");
    return ssProfiles->getVideoDecoders().size();
}

Int32 DecoderCapabilities::Native_get_video_decoder_type(
    /* [in] */ Int32 index)
{
    // ALOGV("native_get_video_decoder_type: %d", index);
    android::Vector<android::video_decoder> decoders = ssProfiles->getVideoDecoders();
    Int32 nSize = decoders.size();
    if (index < 0 || index >= nSize) {
        // jniThrowException(env, "java/lang/IllegalArgumentException", "out of array boundary");
        return -1;
    }

    return decoders[index];
}

Int32 DecoderCapabilities::Native_get_num_audio_decoders()
{
    // ALOGV("native_get_num_audio_decoders");
    return ssProfiles->getAudioDecoders().size();
}

Int32 DecoderCapabilities::Native_get_audio_decoder_type(
    /* [in] */ Int32 index)
{
    // ALOGV("native_get_audio_decoder_type: %d", index);
    android::Vector<android::audio_decoder> decoders = ssProfiles->getAudioDecoders();
    Int32 nSize = decoders.size();
    if (index < 0 || index >= nSize) {
        // jniThrowException(env, "java/lang/IllegalArgumentException", "out of array boundary");
        return -1;
    }

    return decoders[index];
}

} // namespace Media
} // namepsace Droid
} // namespace Elastos
