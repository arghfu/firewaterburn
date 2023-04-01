# Copyright (c) 2023 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

board_runner_args(jlink "--device=nrf52" "--speed=4000")
board_runner_args(pyocd "--target=nrf52840" "--frequency=4000000")

include(${ZEPHYR_BASE}/boards/common/nrfjprog.board.cmake)
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)

# Suppress "unique_unit_address_if_enabled" to handle the following overlaps:
# - power@40000000 & clock@40000000 & bprot@40000000
# - acl@4001e000 & flash-controller@4001e000
list(APPEND EXTRA_DTC_FLAGS "-Wno-unique_unit_address_if_enabled")