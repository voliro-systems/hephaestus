//================================================================================================
// Copyright (C) 2023-2024 HEPHAESTUS Contributors
//=================================================================================================

#pragma once

#include <string>

namespace heph::ipc {

struct TopicConfig {
  std::string name;
};

[[nodiscard]] TopicConfig createTopicConfig(const std::string& topic_name);

}  // namespace heph::ipc
