// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Polyfills/attributes.hpp>
#include <ArduinoJson/Variant/VariantTo.hpp>
#include "VariantRef.hpp"


namespace ARDUINOJSON_NAMESPACE {

// Grants access to the internal variant API
template <typename TClient>
class VariantAttorney {
 public:
  static FORCE_INLINE VariantData *getData(TClient client) {
    return client.getData();
  }

  static FORCE_INLINE const VariantData *getDataConst(TClient client) {
    return client.getDataConst();
  }

  static FORCE_INLINE VariantRef addElement(TClient client) {
    return client.addElement();
  }

  static FORCE_INLINE VariantRef getElement(TClient client, size_t index) {
    return client.getElement(index);
  }

  static FORCE_INLINE VariantConstRef getElementConst(TClient client,
                                                      size_t index) {
    return client.getElementConst(index);
  }

  static FORCE_INLINE VariantRef getOrAddElement(TClient client, size_t index) {
    return client.getOrAddElement(index);
  }

  template <typename TChar>
  static FORCE_INLINE VariantRef getMember(TClient client, TChar *key) {
    return client.getMember(key);
  }

  template <typename TString>
  static FORCE_INLINE VariantRef getMember(TClient client, const TString &key) {
    return client.getMember(key);
  }

  template <typename TChar>
  static FORCE_INLINE VariantConstRef getMemberConst(TClient client,
                                                     TChar *key) {
    return client.getMemberConst(key);
  }

  template <typename TString>
  static FORCE_INLINE VariantConstRef getMemberConst(TClient client,
                                                     const TString &key) {
    return client.getMemberConst(key);
  }

  template <typename TChar>
  static FORCE_INLINE VariantRef getOrAddMember(TClient client, TChar *key) {
    return client.getOrAddMember(key);
  }

  template <typename TString>
  static FORCE_INLINE VariantRef getOrAddMember(TClient client,
                                                const TString &key) {
    return client.getOrAddMember(key);
  }
};

}  // namespace ARDUINOJSON_NAMESPACE
