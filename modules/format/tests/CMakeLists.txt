# =================================================================================================
# Copyright (C) 2025 HEPHAESTUS Contributors
# =================================================================================================

define_module_test(
  NAME generic_formatter_tests
  SOURCES generic_formatter_tests.cpp
  PUBLIC_LINK_LIBS hephaestus::types hephaestus::types_proto
)
