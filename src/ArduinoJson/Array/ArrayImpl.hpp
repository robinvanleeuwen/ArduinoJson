// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Array/ArrayRef.hpp>
#include <ArduinoJson/Object/ObjectRef.hpp>
#include <ArduinoJson/Variant/VariantAttorney.hpp>

namespace ARDUINOJSON_NAMESPACE {

template <typename TArray>
inline ArrayRef ArrayShortcuts<TArray>::createNestedArray() const {
  return VariantAttorney::addElement(impl()).template to<ArrayRef>();
}

template <typename TArray>
inline ObjectRef ArrayShortcuts<TArray>::createNestedObject() const {
  return VariantAttorney::addElement(impl()).template to<ObjectRef>();
}

template <typename TArray>
inline ElementProxy<TArray> ArrayShortcuts<TArray>::operator[](
    size_t index) const {
  return ElementProxy<TArray>(impl(), index);
}

template <typename TArray>
inline VariantRef ArrayShortcuts<TArray>::add() const {
  return impl().addElement();
}

template <typename TArray>
template <typename T>
inline bool ArrayShortcuts<TArray>::add(const T &value) const {
  return VariantAttorney::addElement(impl()).set(value);
}

template <typename TArray>
template <typename T>
inline bool ArrayShortcuts<TArray>::add(T *value) const {
  return VariantAttorney::addElement(impl()).set(value);
}

}  // namespace ARDUINOJSON_NAMESPACE
