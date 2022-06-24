// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Polyfills/attributes.hpp>
#include <ArduinoJson/Variant/VariantTo.hpp>
#include "VariantRef.hpp"

namespace ARDUINOJSON_NAMESPACE {

// Grants access to the internal variant API
class VariantAttorney {
 public:
  template <typename TClient>
  static FORCE_INLINE MemoryPool *getPool(TClient &client) {
    return client.getPool();
  }

  template <typename TClient>
  static FORCE_INLINE VariantData *getData(TClient &client) {
    return client.getData();
  }

  template <typename TClient>
  static FORCE_INLINE VariantData *getOrCreateData(TClient &client) {
    return client.getOrCreateData();
  }

  template <typename TClient>
  static FORCE_INLINE const VariantData *getDataConst(const TClient &client) {
    return client.getDataConst();
  }
};

}  // namespace ARDUINOJSON_NAMESPACE
