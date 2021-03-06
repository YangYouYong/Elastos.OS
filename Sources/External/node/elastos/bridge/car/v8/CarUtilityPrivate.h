/*
 * Copyright 2010, The Android Open Source Project
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CarUtilityPrivate_h
#define CarUtilityPrivate_h

#include <elastos.h>

#if ENABLE(CAR_BRIDGE)

#include "npruntime.h"

#include "NPV8Object.h"
#include "V8NPUtils.h"
#include "V8Binding.h"

#include "CarString.h"
#include "CarMethod.h"

#include "CarUtility.h"

namespace JSC {
namespace Bindings {

class CarValue;

void ReportException(v8::Isolate* isolate, v8::TryCatch* try_catch);

WebCore::LocalDOMWindow* getRootObject();

void convertNPVariantToCarValue_In(NPVariant, CarValue*);
void convertCarValuesToNPVariants(CarValue*, Int32, NPVariant**);
void convertCarValuesToNPVariant(const CarMethod*, CarValue*, ArrayOf<Int32>*, NPVariant*);
void _convertCarValueToNPVariant_In(CarValue&, NPVariant*);
void convertCarValueToNPVariant(CarValue&, NPVariant*);

void convertV8ValueToCarValue_CallerAllocOut(v8::Handle<v8::Value>& v8Arg, CarValue& carArg);
void convertV8ValueToCarValue(v8::Handle<v8::Value>& v8Arg, CarValue& carArg);
void convertV8ValuesToCarValues(v8::Handle<v8::Value>* v8Args, Int32 count, CarValue** carArgs);

} // namespace Bindings

} // namespace JSC

#endif // ENABLE(CAR_BRIDGE)
#endif // CarUtilityPrivate_h