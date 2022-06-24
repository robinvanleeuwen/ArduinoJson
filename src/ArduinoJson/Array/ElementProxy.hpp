// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Configuration.hpp>
#include <ArduinoJson/Variant/VariantAttorney.hpp>
#include <ArduinoJson/Variant/VariantOperators.hpp>
#include <ArduinoJson/Variant/VariantRef.hpp>
#include <ArduinoJson/Variant/VariantShortcuts.hpp>
#include <ArduinoJson/Variant/VariantTo.hpp>

#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable : 4522)
#endif

namespace ARDUINOJSON_NAMESPACE {

template <typename TArray>
class ElementProxy : public VariantOperators<ElementProxy<TArray> >,
                     public VariantShortcuts<ElementProxy<TArray> >,
                     public Visitable,
                     public VariantTag {
  typedef ElementProxy<TArray> this_type;

  friend class VariantAttorney;

 public:
  typedef VariantRef variant_type;

  FORCE_INLINE ElementProxy(TArray array, size_t index)
      : _array(array), _index(index) {}

  FORCE_INLINE ElementProxy(const ElementProxy& src)
      : _array(src._array), _index(src._index) {}

  FORCE_INLINE this_type& operator=(const this_type& src) {
    getOrAddUpstreamElement().set(src.as<VariantConstRef>());
    return *this;
  }

  // Replaces the value
  //
  // operator=(const TValue&)
  // TValue = bool, long, int, short, float, double, serialized, VariantRef,
  //          std::string, String, ArrayRef, ObjectRef
  template <typename T>
  FORCE_INLINE this_type& operator=(const T& src) {
    getOrAddUpstreamElement().set(src);
    return *this;
  }
  //
  // operator=(TValue)
  // TValue = char*, const char*, const __FlashStringHelper*
  template <typename T>
  FORCE_INLINE this_type& operator=(T* src) {
    getOrAddUpstreamElement().set(src);
    return *this;
  }

  FORCE_INLINE void clear() const {
    getUpstreamElement().clear();
  }

  FORCE_INLINE bool isNull() const {
    return getUpstreamElementConst().isNull();
  }

  template <typename T>
  FORCE_INLINE typename enable_if<!is_same<T, char*>::value &&
                                      !ConverterNeedsWriteableRef<T>::value,
                                  T>::type
  as() const {
    return getUpstreamElementConst().template as<T>();
  }

  template <typename T>
  FORCE_INLINE typename enable_if<ConverterNeedsWriteableRef<T>::value, T>::type
  as() const {
    return getUpstreamElement().template as<T>();
  }

  template <typename T>
  FORCE_INLINE typename enable_if<is_same<T, char*>::value, const char*>::type
  ARDUINOJSON_DEPRECATED("Replace as<char*>() with as<const char*>()")
      as() const {
    return as<const char*>();
  }

  template <typename T>
  FORCE_INLINE operator T() const {
    return as<T>();
  }

  template <typename T>
  FORCE_INLINE
      typename enable_if<ConverterNeedsWriteableRef<T>::value, bool>::type
      is() const {
    return getUpstreamElement().template is<T>();
  }

  template <typename T>
  FORCE_INLINE
      typename enable_if<!ConverterNeedsWriteableRef<T>::value, bool>::type
      is() const {
    return getUpstreamElementConst().template is<T>();
  }

  template <typename T>
  FORCE_INLINE typename VariantTo<T>::type to() const {
    return getOrAddUpstreamElement().template to<T>();
  }

  FORCE_INLINE void link(VariantConstRef value) const {
    getOrAddUpstreamElement().link(value);
  }

  // Replaces the value
  //
  // bool set(const TValue&)
  // TValue = bool, long, int, short, float, double, serialized, VariantRef,
  //          std::string, String, ArrayRef, ObjectRef
  template <typename TValue>
  FORCE_INLINE bool set(const TValue& value) const {
    return getOrAddUpstreamElement().set(value);
  }
  //
  // bool set(TValue)
  // TValue = char*, const char*, const __FlashStringHelper*
  template <typename TValue>
  FORCE_INLINE bool set(TValue* value) const {
    return getOrAddUpstreamElement().set(value);
  }

  FORCE_INLINE size_t size() const {
    return getUpstreamElementConst().size();
  }

  FORCE_INLINE size_t memoryUsage() const {
    return getUpstreamElementConst().memoryUsage();
  }

  FORCE_INLINE void remove(size_t index) const {
    getUpstreamElement().remove(index);
  }
  // remove(char*) const
  // remove(const char*) const
  // remove(const __FlashStringHelper*) const
  template <typename TChar>
  FORCE_INLINE typename enable_if<IsString<TChar*>::value>::type remove(
      TChar* key) const {
    getUpstreamElement().remove(key);
  }
  // remove(const std::string&) const
  // remove(const String&) const
  template <typename TString>
  FORCE_INLINE typename enable_if<IsString<TString>::value>::type remove(
      const TString& key) const {
    getUpstreamElement().remove(key);
  }

 private:
  VariantRef getOrAddUpstreamElement() const {
    return VariantRef(getPool(), getOrCreateData());
  }

  VariantRef getUpstreamElement() const {
    return VariantRef(getPool(), getData());
  }

  VariantConstRef getUpstreamElementConst() const {
    return VariantConstRef(getDataConst());
  }

 protected:
  FORCE_INLINE MemoryPool* getPool() const {
    return VariantAttorney::getPool(_array);
  }

  FORCE_INLINE VariantData* getData() const {
    VariantData* data = VariantAttorney::getData(_array);
    return data ? data->getElement(_index) : 0;
  }

  FORCE_INLINE VariantData* getOrCreateData() const {
    VariantData* data = VariantAttorney::getOrCreateData(_array);
    return data ? data->getOrAddElement(_index, getPool()) : 0;
  }

  FORCE_INLINE const VariantData* getDataConst() const {
    const VariantData* data = VariantAttorney::getDataConst(_array);
    return data ? data->resolve()->getElement(_index) : 0;
  }

 private:
  friend void convertToJson(const this_type& src, VariantRef dst) {
    dst.set(src.getUpstreamElementConst());
  }

  TArray _array;
  const size_t _index;
};

}  // namespace ARDUINOJSON_NAMESPACE

#ifdef _MSC_VER
#  pragma warning(pop)
#endif
