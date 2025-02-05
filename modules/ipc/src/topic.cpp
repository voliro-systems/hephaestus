//================================================================================================
// Copyright (C) 2023-2024 HEPHAESTUS Contributors
//=================================================================================================

#include "hephaestus/ipc/topic.h"

#include <string>
#include <utility>

#include <fmt/format.h>

#include "hephaestus/utils/exception.h"

namespace heph::ipc {
[[nodiscard]] TopicConfig createTopicConfig(const std::string& topic_name) {
  if (topic_name.empty() || topic_name.starts_with('/') || topic_name.ends_with('/')) {
    throw std::invalid_argument(fmt::format("invalid topic name: '{}'", topic_name));
  }
  return { .name = topic_name };
}
}  // namespace heph::ipc
