// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Array/ElementProxy.hpp>
#include <ArduinoJson/Memory/MemoryPool.hpp>
#include <ArduinoJson/Object/MemberProxy.hpp>
#include <ArduinoJson/Object/ObjectRef.hpp>
#include <ArduinoJson/Strings/StoragePolicy.hpp>
#include <ArduinoJson/Variant/VariantRef.hpp>
#include <ArduinoJson/Variant/VariantTo.hpp>

namespace ARDUINOJSON_NAMESPACE {

class JsonDocument : public Visitable,
                     public VariantOperators<const JsonDocument&> {
  friend class VariantAttorney;

 public:
  template <typename T>
  T as() {
    return getVariant().template as<T>();
  }

  template <typename T>
  T as() const {
    return getVariant().template as<T>();
  }

  void clear() {
    _pool.clear();
    _data.init();
  }

  template <typename T>
  bool is() {
    return getVariant().template is<T>();
  }

  template <typename T>
  bool is() const {
    return getVariant().template is<T>();
  }

  bool isNull() const {
    return getVariant().isNull();
  }

  size_t memoryUsage() const {
    return _pool.size();
  }

  bool overflowed() const {
    return _pool.overflowed();
  }

  size_t nesting() const {
    return variantNesting(&_data);
  }

  size_t capacity() const {
    return _pool.capacity();
  }

  size_t size() const {
    return _data.resolve()->size();
  }

  bool set(const JsonDocument& src) {
    return to<VariantRef>().set(src.as<VariantConstRef>());
  }

  template <typename T>
  typename enable_if<!is_base_of<JsonDocument, T>::value, bool>::type set(
      const T& src) {
    return to<VariantRef>().set(src);
  }

  template <typename T>
  typename VariantTo<T>::type to() {
    clear();
    return getVariant().template to<T>();
  }

  // for internal use only
  MemoryPool& memoryPool() {
    return _pool;
  }

  // for internal use only
  VariantData& data() {
    return _data;
  }

  ArrayRef createNestedArray() {
    return addElement().to<ArrayRef>();
  }

  // createNestedArray(char*)
  // createNestedArray(const char*)
  // createNestedArray(const __FlashStringHelper*)
  template <typename TChar>
  ArrayRef createNestedArray(TChar* key) {
    return getOrAddMember(key).template to<ArrayRef>();
  }

  // createNestedArray(const std::string&)
  // createNestedArray(const String&)
  template <typename TString>
  ArrayRef createNestedArray(const TString& key) {
    return getOrAddMember(key).template to<ArrayRef>();
  }

  ObjectRef createNestedObject() {
    return addElement().to<ObjectRef>();
  }

  // createNestedObject(char*)
  // createNestedObject(const char*)
  // createNestedObject(const __FlashStringHelper*)
  template <typename TChar>
  ObjectRef createNestedObject(TChar* key) {
    return getOrAddMember(key).template to<ObjectRef>();
  }

  // createNestedObject(const std::string&)
  // createNestedObject(const String&)
  template <typename TString>
  ObjectRef createNestedObject(const TString& key) {
    return getOrAddMember(key).template to<ObjectRef>();
  }

  // containsKey(char*) const
  // containsKey(const char*) const
  // containsKey(const __FlashStringHelper*) const
  template <typename TChar>
  bool containsKey(TChar* key) const {
    return !getMemberConst(key).isUnbound();
  }

  // containsKey(const std::string&) const
  // containsKey(const String&) const
  template <typename TString>
  bool containsKey(const TString& key) const {
    return !getMemberConst(key).isUnbound();
  }

  // operator[](const std::string&)
  // operator[](const String&)
  template <typename TString>
  FORCE_INLINE typename enable_if<IsString<TString>::value,
                                  MemberProxy<JsonDocument&, TString> >::type
  operator[](const TString& key) {
    return MemberProxy<JsonDocument&, TString>(*this, key);
  }

  // operator[](char*)
  // operator[](const char*)
  // operator[](const __FlashStringHelper*)
  template <typename TChar>
  FORCE_INLINE typename enable_if<IsString<TChar*>::value,
                                  MemberProxy<JsonDocument&, TChar*> >::type
  operator[](TChar* key) {
    return MemberProxy<JsonDocument&, TChar*>(*this, key);
  }

  // operator[](const std::string&) const
  // operator[](const String&) const
  template <typename TString>
  FORCE_INLINE
      typename enable_if<IsString<TString>::value, VariantConstRef>::type
      operator[](const TString& key) const {
    return getMemberConst(key);
  }

  // operator[](char*) const
  // operator[](const char*) const
  // operator[](const __FlashStringHelper*) const
  template <typename TChar>
  FORCE_INLINE
      typename enable_if<IsString<TChar*>::value, VariantConstRef>::type
      operator[](TChar* key) const {
    return getMemberConst(key);
  }

  FORCE_INLINE ElementProxy<JsonDocument&> operator[](size_t index) {
    return ElementProxy<JsonDocument&>(*this, index);
  }

  FORCE_INLINE VariantConstRef operator[](size_t index) const {
    return getElementConst(index);
  }

  FORCE_INLINE VariantRef add() {
    return addElement();
  }

  template <typename TValue>
  FORCE_INLINE bool add(const TValue& value) {
    return addElement().set(value);
  }

  // add(char*) const
  // add(const char*) const
  // add(const __FlashStringHelper*) const
  template <typename TChar>
  FORCE_INLINE bool add(TChar* value) {
    return addElement().set(value);
  }

  FORCE_INLINE void remove(size_t index) {
    _data.remove(index);
  }
  // remove(char*)
  // remove(const char*)
  // remove(const __FlashStringHelper*)
  template <typename TChar>
  FORCE_INLINE typename enable_if<IsString<TChar*>::value>::type remove(
      TChar* key) {
    _data.remove(adaptString(key));
  }
  // remove(const std::string&)
  // remove(const String&)
  template <typename TString>
  FORCE_INLINE typename enable_if<IsString<TString>::value>::type remove(
      const TString& key) {
    _data.remove(adaptString(key));
  }

  FORCE_INLINE operator VariantRef() {
    return getVariant();
  }

  FORCE_INLINE operator VariantConstRef() const {
    return getVariant();
  }

 protected:
  JsonDocument() : _pool(0, 0) {
    _data.init();
  }

  JsonDocument(MemoryPool pool) : _pool(pool) {
    _data.init();
  }

  JsonDocument(char* buf, size_t capa) : _pool(buf, capa) {
    _data.init();
  }

  ~JsonDocument() {}

  void replacePool(MemoryPool pool) {
    _pool = pool;
  }

  VariantRef getVariant() {
    return VariantRef(&_pool, &_data);
  }

  VariantConstRef getVariant() const {
    return VariantConstRef(&_data);
  }

  MemoryPool _pool;
  VariantData _data;

 protected:
  FORCE_INLINE MemoryPool* getPool() {
    return &_pool;
  }

  FORCE_INLINE VariantData* getData() {
    return &_data;
  }

  FORCE_INLINE VariantData* getOrCreateData() {
    return &_data;
  }

  FORCE_INLINE const VariantData* getDataConst() const {
    return &_data;
  }

 private:
  FORCE_INLINE VariantRef addElement() {
    return VariantRef(&_pool, _data.addElement(&_pool));
  }

  FORCE_INLINE VariantRef getElement(size_t index) {
    return VariantRef(&_pool, _data.getElement(index));
  }

  FORCE_INLINE VariantConstRef getElementConst(size_t index) const {
    return VariantConstRef(_data.getElement(index));
  }

  FORCE_INLINE VariantRef getOrAddElement(size_t index) {
    return VariantRef(&_pool, _data.getOrAddElement(index, &_pool));
  }

  // JsonVariantConst getMemberConst(char*) const
  // JsonVariantConst getMemberConst(const char*) const
  // JsonVariantConst getMemberConst(const __FlashStringHelper*) const
  template <typename TChar>
  FORCE_INLINE VariantConstRef getMemberConst(TChar* key) const {
    return VariantConstRef(_data.getMember(adaptString(key)));
  }

  // JsonVariantConst getMemberConst(const std::string&) const
  // JsonVariantConst getMemberConst(const String&) const
  template <typename TString>
  FORCE_INLINE
      typename enable_if<IsString<TString>::value, VariantConstRef>::type
      getMemberConst(const TString& key) const {
    return VariantConstRef(_data.getMember(adaptString(key)));
  }

  // JsonVariant getMember(char*)
  // JsonVariant getMember(const char*)
  // JsonVariant getMember(const __FlashStringHelper*)
  template <typename TChar>
  FORCE_INLINE VariantRef getMember(TChar* key) {
    return VariantRef(&_pool, _data.getMember(adaptString(key)));
  }

  // JsonVariant getMember(const std::string&)
  // JsonVariant getMember(const String&)
  template <typename TString>
  FORCE_INLINE typename enable_if<IsString<TString>::value, VariantRef>::type
  getMember(const TString& key) {
    return VariantRef(&_pool, _data.getMember(adaptString(key)));
  }

  // getOrAddMember(char*)
  // getOrAddMember(const char*)
  // getOrAddMember(const __FlashStringHelper*)
  template <typename TChar>
  FORCE_INLINE VariantRef getOrAddMember(TChar* key) {
    return VariantRef(&_pool,
                      _data.getOrAddMember(adaptString(key), &_pool,
                                           getStringStoragePolicy(key)));
  }

  // getOrAddMember(const std::string&)
  // getOrAddMember(const String&)
  template <typename TString>
  FORCE_INLINE VariantRef getOrAddMember(const TString& key) {
    return VariantRef(&_pool,
                      _data.getOrAddMember(adaptString(key), &_pool,
                                           getStringStoragePolicy(key)));
  }

  JsonDocument(const JsonDocument&);
  JsonDocument& operator=(const JsonDocument&);
};

inline void convertToJson(const JsonDocument& src, VariantRef dst) {
  dst.set(src.as<VariantConstRef>());
}

}  // namespace ARDUINOJSON_NAMESPACE
