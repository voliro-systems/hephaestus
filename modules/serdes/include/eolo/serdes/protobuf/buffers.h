//=================================================================================================
// Copyright (C) 2023-2024 EOLO Contributors
//=================================================================================================

#pragma once

#include <span>
#include <vector>

#include "eolo/serdes/protobuf/concepts.h"

namespace eolo::serdes::protobuf {

// TODO: add option to provide custom allocator for buffer.
class SerializerBuffer {
public:
  template <ProtobufMessage Proto>
  void serialize(const Proto& proto) {
    buffer_.resize(proto.ByteSizeLong());
    proto.SerializeToArray(buffer_.data(), static_cast<int>(buffer_.size()));
  }

  [[nodiscard]] auto exctractSerializedData() && -> std::vector<std::byte>&& {
    return std::move(buffer_);
  }

private:
  std::vector<std::byte> buffer_;
};

class DeserializerBuffer {
public:
  explicit DeserializerBuffer(std::span<const std::byte> buffer) : buffer_(buffer) {
  }

  template <ProtobufMessage Proto>
  [[nodiscard]] auto deserialize(Proto& proto) const -> bool {
    return proto.ParseFromArray(buffer_.data(), static_cast<int>(buffer_.size()));
  }

private:
  std::span<const std::byte> buffer_;
};

}  // namespace eolo::serdes::protobuf
