// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Serialization/Writers/DummyWriter.hpp>

namespace ARDUINOJSON_NAMESPACE {

template <template <typename> class TSerializer>
size_t measure(VariantConstRef source) {
  DummyWriter dp;
  TSerializer<DummyWriter> serializer(dp);
  return variantAccept(VariantAttorney::getDataConst(source), serializer);
}

}  // namespace ARDUINOJSON_NAMESPACE
