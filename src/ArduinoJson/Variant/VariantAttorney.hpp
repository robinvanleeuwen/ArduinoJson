// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Variant/VariantTo.hpp>
#include "VariantRef.hpp"

namespace ARDUINOJSON_NAMESPACE {

// Grants access to the internal variant API
template <typename TClient>
class VariantAttorney {
 public:
  template <typename TVisitor>
  typename TVisitor::result_type accept(TClient client, TVisitor &visitor) {
    return client.accept(visitor);
  }

  static VariantRef addElement(TClient client) {
    return client.addElement();
  }

  static VariantRef getElement(TClient client, size_t index) {
    return client.getElement(index);
  }

  static VariantConstRef getElementConst(TClient client, size_t index) {
    return client.getElementConst(index);
  }

  static VariantRef getOrAddElement(TClient client, size_t index) {
    return client.getOrAddElement(index);
  }

  template <typename TChar>
  static VariantRef getMember(TClient client, TChar *key) {
    return client.getMember(key);
  }

  template <typename TString>
  static VariantRef getMember(TClient client, const TString &key) {
    return client.getMember(key);
  }

  template <typename TChar>
  static VariantConstRef getMemberConst(TClient client, TChar *key) {
    return client.getMemberConst(key);
  }

  template <typename TString>
  static VariantConstRef getMemberConst(TClient client, const TString &key) {
    return client.getMemberConst(key);
  }

  template <typename TChar>
  static VariantRef getOrAddMember(TClient client, TChar *key) {
    return client.getOrAddMember(key);
  }

  template <typename TString>
  static VariantRef getOrAddMember(TClient client, const TString &key) {
    return client.getOrAddMember(key);
  }
};

}  // namespace ARDUINOJSON_NAMESPACE
