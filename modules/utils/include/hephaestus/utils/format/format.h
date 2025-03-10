//=================================================================================================
// Copyright (C) 2023-2024 HEPHAESTUS Contributors
//=================================================================================================

#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>
#include <string_view>

#include <fmt/chrono.h>  // NOLINT(misc-include-cleaner)
#include <fmt/format.h>
#include <magic_enum.hpp>

#include "hephaestus/utils/concepts.h"

namespace heph::utils::format {

//=================================================================================================
// Array and Vector
//=================================================================================================
template <typename T>
concept ArrayOrVectorType = ArrayType<T> || VectorType<T>;

template <ArrayOrVectorType T>
[[nodiscard]] inline auto toString(const T& vec) -> std::string {
  std::stringstream ss;

  std::size_t idx = 0;
  for (const auto& value : vec) {
    const std::string str = fmt::format("  Index: {}, Value: {}\n", idx, value);
    ++idx;
    ss << str;
  }

  return ss.str();
}

//=================================================================================================
// Optionals
//=================================================================================================
template <OptionalType T>
[[nodiscard]] inline auto toString(const T& optional) -> std::string {
  std::stringstream ss;

  if (optional.has_value()) {
    ss << optional.value();
  } else {
    ss << "std::nullopt";
  }

  return ss.str();
}

//=================================================================================================
// UnorderedMap
//=================================================================================================
template <UnorderedMapType T>
[[nodiscard]] inline auto toString(const T& umap) -> std::string {
  std::stringstream ss;

  for (const auto& [key, value] : umap) {
    const std::string str = fmt::format("  Key: {}, Value: {}\n", key, value);
    ss << str;
  }

  return ss.str();
}

//=================================================================================================
// Enum
//=================================================================================================
template <EnumType T>
[[nodiscard]] inline auto toString(T value) -> std::string_view {
  return magic_enum::enum_name(value);
}

//=================================================================================================
// ChronoTimePoint
//=================================================================================================
template <ChronoSystemClockType Clock, ChronoDurationType Duration>
[[nodiscard]] inline auto toString(const std::chrono::time_point<Clock, Duration>& timestamp) -> std::string {
  return fmt::format("{:%Y-%m-%d %H:%M:%S}",
                     std::chrono::time_point_cast<std::chrono::microseconds, Clock>(timestamp));
}

template <ChronoSteadyClockType Clock, ChronoDurationType Duration>
[[nodiscard]] inline auto toString(const std::chrono::time_point<Clock, Duration>& timestamp) -> std::string {
  auto duration_since_epoch = timestamp.time_since_epoch();
  auto total_seconds = std::chrono::duration_cast<std::chrono::seconds>(duration_since_epoch).count();
  auto days = total_seconds / (24 * 3600);            // NOLINT(cppcoreguidelines-avoid-magic-numbers)
  auto hours = (total_seconds % (24 * 3600)) / 3600;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
  auto minutes = (total_seconds % 3600) / 60;         // NOLINT(cppcoreguidelines-avoid-magic-numbers)
  auto seconds = total_seconds % 60;                  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
  auto sub_seconds = (duration_since_epoch - std::chrono::seconds(total_seconds)).count();

  static constexpr auto TIME_BASE = Clock::duration::period::den;  // sub-second precision
  static constexpr int64_t GIGA = 1'000'000'000;
  static constexpr int64_t SCALER = GIGA / TIME_BASE;  // 1 for time base nanoseconds, 1'000 for microseconds

  return fmt::format("{}d {:02}h:{:02}m:{:02}.{:09}s", days, hours, minutes, seconds, sub_seconds * SCALER);
}

};  // namespace heph::utils::format
