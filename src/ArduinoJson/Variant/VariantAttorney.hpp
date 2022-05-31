// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Variant/VariantTo.hpp>
#include "VariantRef.hpp"

namespace ARDUINOJSON_NAMESPACE {

// Grants access to the internal variant API
class VariantAttorney {
 public:
  template <typename TClient, typename TVisitor>
  typename TVisitor::result_type accept(const TClient &client,
                                        TVisitor &visitor) {
    return client.accept(visitor);
  }

  template <typename TClient>
  static VariantRef addElement(TClient &client) {
    return client.addElement();
  }

  template <typename TClient>
  static VariantRef getElement(TClient &client, size_t index) {
    return client.getElement(index);
  }

  template <typename TClient>
  static VariantConstRef getElementConst(const TClient &client, size_t index) {
    return client.getElementConst(index);
  }

  template <typename TClient>
  static VariantRef getOrAddElement(TClient &client, size_t index) {
    return client.getOrAddElement(index);
  }

  template <typename TClient, typename TChar>
  static VariantRef getMember(TClient &client, TChar *key) {
    return client.getMember(key);
  }

  template <typename TClient, typename TString>
  static VariantRef getMember(TClient &client, const TString &key) {
    return client.getMember(key);
  }

  template <typename TClient, typename TChar>
  static VariantConstRef getMemberConst(const TClient &client, TChar *key) {
    return client.getMemberConst(key);
  }

  template <typename TClient, typename TString>
  static VariantConstRef getMemberConst(const TClient &client,
                                        const TString &key) {
    return client.getMemberConst(key);
  }

  template <typename TClient, typename TChar>
  static VariantRef getOrAddMember(TClient &client, TChar *key) {
    return client.getOrAddMember(key);
  }

  template <typename TClient, typename TString>
  static VariantRef getOrAddMember(TClient &client, const TString &key) {
    return client.getOrAddMember(key);
  }
};

}  // namespace ARDUINOJSON_NAMESPACE
