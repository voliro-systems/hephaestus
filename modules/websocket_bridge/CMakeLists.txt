#=================================================================================================
# Copyright (C) 2025 HEPHAESTUS Contributors
#=================================================================================================

declare_module(
        NAME websocket_bridge
        DEPENDS_ON_MODULES ipc cli concurrency containers utils serdes telemetry
        DEPENDS_ON_EXTERNAL_PROJECTS  absl fmt foxglove_websocket OpenSSL reflectcpp ZLIB)

find_package(absl REQUIRED)
find_package(fmt REQUIRED)
find_package(foxglove_websocket REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(reflectcpp REQUIRED)
find_package(ZLIB REQUIRED)

# library target
file(GLOB_RECURSE SOURCES 
        src/websocket_bridge/*.cpp
        src/websocket_bridge/utils/*.cpp
        src/websocket_bridge/ipc/*.cpp
        include/hephaestus/websocket_bridge/*.h
        include/hephaestus/websocket_bridge/utils/*.h
        include/hephaestus/websocket_bridge/ipc/*.h
)

define_module_library(
        NAME websocket_bridge
        PUBLIC_LINK_LIBS
                absl::base
                absl::log
                fmt::fmt
                foxglove::foxglove_websocket
                hephaestus::ipc
                OpenSSL::Crypto
                OpenSSL::SSL
                reflectcpp::reflectcpp
                yaml-cpp
                ZLIB::ZLIB
        PRIVATE_LINK_LIBS ""
        SOURCES ${SOURCES} README.md
        PUBLIC_INCLUDE_PATHS
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
        PRIVATE_INCLUDE_PATHS ""
        SYSTEM_PRIVATE_INCLUDE_PATHS ""
)
target_compile_definitions(hephaestus_websocket_bridge PUBLIC ZENOH_WITH_UNSTABLE_API Z_FEATURE_UNSTABLE_API ZENOHCXX_ZENOHC)

# Subprojects
add_subdirectory(tests)
add_subdirectory(apps)
add_subdirectory(examples)
