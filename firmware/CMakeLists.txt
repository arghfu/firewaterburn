# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

set(NO_BUILD_TYPE_WARNING TRUE)
list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

include(${ZEPHYR_BASE}/cmake/cfb.cmake NO_POLICY_SCOPE)

project(firewaterburn)

add_subdirectory(src/peripheral)

target_include_directories(app PUBLIC ${ZEPHYR_BASE}/subsys/net/ip)

target_sources(app PRIVATE src/main.c)


set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)
generate_cfb_font_for_target(app fonts/fsex302.ttf ${gen_dir}/cfb_font_fsex302.h 8 16 -s 16 --first 32 --last 180 -n a)
generate_cfb_font_for_target(app fonts/sig_strength.png ${gen_dir}/cfb_font_sig_strength.h 17 16 --first 49 --last 54 -n b)
generate_cfb_font_for_target(app fonts/channel.png ${gen_dir}/cfb_font_channel.h 20 16 --first 48 --last 53 -n c)