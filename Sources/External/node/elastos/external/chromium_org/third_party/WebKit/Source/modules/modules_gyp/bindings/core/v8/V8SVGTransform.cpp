// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#include "config.h"
#include "V8SVGTransform.h"

#include "bindings/core/v8/V8SVGElement.h"
#include "bindings/core/v8/V8SVGMatrix.h"
#include "bindings/v8/ExceptionState.h"
#include "bindings/v8/V8DOMConfiguration.h"
#include "bindings/v8/V8HiddenValue.h"
#include "bindings/v8/V8ObjectConstructor.h"
#include "core/dom/ContextFeatures.h"
#include "core/dom/Document.h"
#include "platform/RuntimeEnabledFeatures.h"
#include "platform/TraceEvent.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace WebCore {

static void initializeScriptWrappableForInterface(SVGTransformTearOff* object)
{
    if (ScriptWrappable::wrapperCanBeStoredInObject(object))
        ScriptWrappable::fromObject(object)->setTypeInfo(&V8SVGTransform::wrapperTypeInfo);
    else
        ASSERT_NOT_REACHED();
}

} // namespace WebCore

void webCoreInitializeScriptWrappableForInterface(WebCore::SVGTransformTearOff* object)
{
    WebCore::initializeScriptWrappableForInterface(object);
}

namespace WebCore {
const WrapperTypeInfo V8SVGTransform::wrapperTypeInfo = { gin::kEmbedderBlink, V8SVGTransform::domTemplate, V8SVGTransform::derefObject, 0, 0, V8SVGTransform::visitDOMWrapper, V8SVGTransform::installPerContextEnabledMethods, 0, WrapperTypeObjectPrototype, RefCountedObject };

namespace SVGTransformTearOffV8Internal {

template <typename T> void V8_USE(T) { }

static void typeAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    SVGTransformTearOff* impl = V8SVGTransform::toNative(holder);
    v8SetReturnValueUnsigned(info, impl->transformType());
}

static void typeAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    SVGTransformTearOffV8Internal::typeAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void matrixAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    SVGTransformTearOff* impl = V8SVGTransform::toNative(holder);
    v8SetReturnValueFast(info, WTF::getPtr(impl->matrix()), impl);
}

static void matrixAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    SVGTransformTearOffV8Internal::matrixAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void angleAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    SVGTransformTearOff* impl = V8SVGTransform::toNative(holder);
    v8SetReturnValue(info, impl->angle());
}

static void angleAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    SVGTransformTearOffV8Internal::angleAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void setMatrixMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "setMatrix", "SVGTransform", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        throwMinimumArityTypeError(exceptionState, 1, info.Length());
        return;
    }
    SVGTransformTearOff* impl = V8SVGTransform::toNative(info.Holder());
    SVGMatrixTearOff* matrix;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        if (info.Length() > 0 && !V8SVGMatrix::hasInstance(info[0], info.GetIsolate())) {
            exceptionState.throwTypeError("parameter 1 is not of type 'SVGMatrix'.");
            exceptionState.throwIfNeeded();
            return;
        }
        TONATIVE_VOID_INTERNAL(matrix, V8SVGMatrix::toNativeWithTypeCheck(info.GetIsolate(), info[0]));
    }
    impl->setMatrix(matrix, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void setMatrixMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    SVGTransformTearOffV8Internal::setMatrixMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void setTranslateMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "setTranslate", "SVGTransform", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 2)) {
        throwMinimumArityTypeError(exceptionState, 2, info.Length());
        return;
    }
    SVGTransformTearOff* impl = V8SVGTransform::toNative(info.Holder());
    float tx;
    float ty;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TONATIVE_VOID_INTERNAL(tx, static_cast<float>(info[0]->NumberValue()));
        TONATIVE_VOID_INTERNAL(ty, static_cast<float>(info[1]->NumberValue()));
    }
    impl->setTranslate(tx, ty, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void setTranslateMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    SVGTransformTearOffV8Internal::setTranslateMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void setScaleMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "setScale", "SVGTransform", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 2)) {
        throwMinimumArityTypeError(exceptionState, 2, info.Length());
        return;
    }
    SVGTransformTearOff* impl = V8SVGTransform::toNative(info.Holder());
    float sx;
    float sy;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TONATIVE_VOID_INTERNAL(sx, static_cast<float>(info[0]->NumberValue()));
        TONATIVE_VOID_INTERNAL(sy, static_cast<float>(info[1]->NumberValue()));
    }
    impl->setScale(sx, sy, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void setScaleMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    SVGTransformTearOffV8Internal::setScaleMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void setRotateMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "setRotate", "SVGTransform", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 3)) {
        throwMinimumArityTypeError(exceptionState, 3, info.Length());
        return;
    }
    SVGTransformTearOff* impl = V8SVGTransform::toNative(info.Holder());
    float angle;
    float cx;
    float cy;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TONATIVE_VOID_INTERNAL(angle, static_cast<float>(info[0]->NumberValue()));
        TONATIVE_VOID_INTERNAL(cx, static_cast<float>(info[1]->NumberValue()));
        TONATIVE_VOID_INTERNAL(cy, static_cast<float>(info[2]->NumberValue()));
    }
    impl->setRotate(angle, cx, cy, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void setRotateMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    SVGTransformTearOffV8Internal::setRotateMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void setSkewXMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "setSkewX", "SVGTransform", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        throwMinimumArityTypeError(exceptionState, 1, info.Length());
        return;
    }
    SVGTransformTearOff* impl = V8SVGTransform::toNative(info.Holder());
    float angle;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TONATIVE_VOID_INTERNAL(angle, static_cast<float>(info[0]->NumberValue()));
    }
    impl->setSkewX(angle, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void setSkewXMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    SVGTransformTearOffV8Internal::setSkewXMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void setSkewYMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "setSkewY", "SVGTransform", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        throwMinimumArityTypeError(exceptionState, 1, info.Length());
        return;
    }
    SVGTransformTearOff* impl = V8SVGTransform::toNative(info.Holder());
    float angle;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TONATIVE_VOID_INTERNAL(angle, static_cast<float>(info[0]->NumberValue()));
    }
    impl->setSkewY(angle, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void setSkewYMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMMethod");
    SVGTransformTearOffV8Internal::setSkewYMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

} // namespace SVGTransformTearOffV8Internal

void V8SVGTransform::visitDOMWrapper(void* object, const v8::Persistent<v8::Object>& wrapper, v8::Isolate* isolate)
{
    SVGTransformTearOff* impl = fromInternalPointer(object);
    v8::Local<v8::Object> creationContext = v8::Local<v8::Object>::New(isolate, wrapper);
    V8WrapperInstantiationScope scope(creationContext, isolate);
    SVGElement* contextElement = impl->contextElement();
    if (contextElement) {
        if (!DOMDataStore::containsWrapper<V8SVGElement>(contextElement, isolate))
            wrap(contextElement, creationContext, isolate);
        DOMDataStore::setWrapperReference<V8SVGElement>(wrapper, contextElement, isolate);
    }
    setObjectGroup(object, wrapper, isolate);
}

static const V8DOMConfiguration::AttributeConfiguration V8SVGTransformAttributes[] = {
    {"type", SVGTransformTearOffV8Internal::typeAttributeGetterCallback, 0, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
    {"matrix", SVGTransformTearOffV8Internal::matrixAttributeGetterCallback, 0, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
    {"angle", SVGTransformTearOffV8Internal::angleAttributeGetterCallback, 0, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
};

static const V8DOMConfiguration::MethodConfiguration V8SVGTransformMethods[] = {
    {"setMatrix", SVGTransformTearOffV8Internal::setMatrixMethodCallback, 0, 1},
    {"setTranslate", SVGTransformTearOffV8Internal::setTranslateMethodCallback, 0, 2},
    {"setScale", SVGTransformTearOffV8Internal::setScaleMethodCallback, 0, 2},
    {"setRotate", SVGTransformTearOffV8Internal::setRotateMethodCallback, 0, 3},
    {"setSkewX", SVGTransformTearOffV8Internal::setSkewXMethodCallback, 0, 1},
    {"setSkewY", SVGTransformTearOffV8Internal::setSkewYMethodCallback, 0, 1},
};

static void configureV8SVGTransformTemplate(v8::Handle<v8::FunctionTemplate> functionTemplate, v8::Isolate* isolate)
{
    functionTemplate->ReadOnlyPrototype();

    v8::Local<v8::Signature> defaultSignature;
    defaultSignature = V8DOMConfiguration::installDOMClassTemplate(functionTemplate, "SVGTransform", v8::Local<v8::FunctionTemplate>(), V8SVGTransform::internalFieldCount,
        V8SVGTransformAttributes, WTF_ARRAY_LENGTH(V8SVGTransformAttributes),
        0, 0,
        V8SVGTransformMethods, WTF_ARRAY_LENGTH(V8SVGTransformMethods),
        isolate);
    v8::Local<v8::ObjectTemplate> instanceTemplate ALLOW_UNUSED = functionTemplate->InstanceTemplate();
    v8::Local<v8::ObjectTemplate> prototypeTemplate ALLOW_UNUSED = functionTemplate->PrototypeTemplate();
    static const V8DOMConfiguration::ConstantConfiguration V8SVGTransformConstants[] = {
        {"SVG_TRANSFORM_UNKNOWN", 0},
        {"SVG_TRANSFORM_MATRIX", 1},
        {"SVG_TRANSFORM_TRANSLATE", 2},
        {"SVG_TRANSFORM_SCALE", 3},
        {"SVG_TRANSFORM_ROTATE", 4},
        {"SVG_TRANSFORM_SKEWX", 5},
        {"SVG_TRANSFORM_SKEWY", 6},
    };
    V8DOMConfiguration::installConstants(functionTemplate, prototypeTemplate, V8SVGTransformConstants, WTF_ARRAY_LENGTH(V8SVGTransformConstants), isolate);
    COMPILE_ASSERT(0 == SVGTransformTearOff::SVG_TRANSFORM_UNKNOWN, TheValueOfSVGTransformTearOff_SVG_TRANSFORM_UNKNOWNDoesntMatchWithImplementation);
    COMPILE_ASSERT(1 == SVGTransformTearOff::SVG_TRANSFORM_MATRIX, TheValueOfSVGTransformTearOff_SVG_TRANSFORM_MATRIXDoesntMatchWithImplementation);
    COMPILE_ASSERT(2 == SVGTransformTearOff::SVG_TRANSFORM_TRANSLATE, TheValueOfSVGTransformTearOff_SVG_TRANSFORM_TRANSLATEDoesntMatchWithImplementation);
    COMPILE_ASSERT(3 == SVGTransformTearOff::SVG_TRANSFORM_SCALE, TheValueOfSVGTransformTearOff_SVG_TRANSFORM_SCALEDoesntMatchWithImplementation);
    COMPILE_ASSERT(4 == SVGTransformTearOff::SVG_TRANSFORM_ROTATE, TheValueOfSVGTransformTearOff_SVG_TRANSFORM_ROTATEDoesntMatchWithImplementation);
    COMPILE_ASSERT(5 == SVGTransformTearOff::SVG_TRANSFORM_SKEWX, TheValueOfSVGTransformTearOff_SVG_TRANSFORM_SKEWXDoesntMatchWithImplementation);
    COMPILE_ASSERT(6 == SVGTransformTearOff::SVG_TRANSFORM_SKEWY, TheValueOfSVGTransformTearOff_SVG_TRANSFORM_SKEWYDoesntMatchWithImplementation);

    // Custom toString template
    functionTemplate->Set(v8AtomicString(isolate, "toString"), V8PerIsolateData::from(isolate)->toStringTemplate());
}

v8::Handle<v8::FunctionTemplate> V8SVGTransform::domTemplate(v8::Isolate* isolate)
{
    return V8DOMConfiguration::domClassTemplate(isolate, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), configureV8SVGTransformTemplate);
}

bool V8SVGTransform::hasInstance(v8::Handle<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Handle<v8::Object> V8SVGTransform::findInstanceInPrototypeChain(v8::Handle<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

SVGTransformTearOff* V8SVGTransform::toNativeWithTypeCheck(v8::Isolate* isolate, v8::Handle<v8::Value> value)
{
    return hasInstance(value, isolate) ? fromInternalPointer(v8::Handle<v8::Object>::Cast(value)->GetAlignedPointerFromInternalField(v8DOMWrapperObjectIndex)) : 0;
}

v8::Handle<v8::Object> wrap(SVGTransformTearOff* impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    ASSERT(impl);
    ASSERT(!DOMDataStore::containsWrapper<V8SVGTransform>(impl, isolate));
    return V8SVGTransform::createWrapper(impl, creationContext, isolate);
}

v8::Handle<v8::Object> V8SVGTransform::createWrapper(PassRefPtr<SVGTransformTearOff> impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    ASSERT(impl);
    ASSERT(!DOMDataStore::containsWrapper<V8SVGTransform>(impl.get(), isolate));
    if (ScriptWrappable::wrapperCanBeStoredInObject(impl.get())) {
        const WrapperTypeInfo* actualInfo = ScriptWrappable::fromObject(impl.get())->typeInfo();
        // Might be a XXXConstructor::wrapperTypeInfo instead of an XXX::wrapperTypeInfo. These will both have
        // the same object de-ref functions, though, so use that as the basis of the check.
        RELEASE_ASSERT_WITH_SECURITY_IMPLICATION(actualInfo->derefObjectFunction == wrapperTypeInfo.derefObjectFunction);
    }

    v8::Handle<v8::Object> wrapper = V8DOMWrapper::createWrapper(creationContext, &wrapperTypeInfo, toInternalPointer(impl.get()), isolate);
    if (UNLIKELY(wrapper.IsEmpty()))
        return wrapper;

    installPerContextEnabledProperties(wrapper, impl.get(), isolate);
    V8DOMWrapper::associateObjectWithWrapper<V8SVGTransform>(impl, &wrapperTypeInfo, wrapper, isolate, WrapperConfiguration::Dependent);
    return wrapper;
}

void V8SVGTransform::derefObject(void* object)
{
    fromInternalPointer(object)->deref();
}

template<>
v8::Handle<v8::Value> toV8NoInline(SVGTransformTearOff* impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    return toV8(impl, creationContext, isolate);
}

} // namespace WebCore
