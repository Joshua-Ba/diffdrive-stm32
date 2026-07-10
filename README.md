# diffdrive-stm32

A bare-metal differential-drive robot firmware for the STM32F401. Hand-written and
free of generated code, with fully host-testable control logic.

[![CI](https://github.com/Joshua-Ba/diffdrive-stm32/actions/workflows/ci.yml/badge.svg)](https://github.com/Joshua-Ba/diffdrive-stm32/actions/workflows/ci.yml)

## About

A small two-wheeled differential-drive robot built as an embedded-systems portfolio
project. The design goal is a clean separation between hardware-independent logic and
the metal: all control logic (kinematics, odometry, PID, sensor fusion) lives in
`core/` as plain C++ and is unit-tested natively on the host, while only a thin driver
layer runs on the MCU. The same `core` library is compiled for both the host test
build and the ARM firmware - one source of truth, verified on every push.

## Hardware

- STM32F401CCU6 ("Black Pill"), Cortex-M4F
- DRV8833 dual H-bridge motor driver
- DG01D-E-PH motors with encoder
- GY-521 / MPU-6050 IMU (I2C)

## Project layout

```
src/core/     shared, hardware-independent control logic (host-tested)
src/hal/      abstract hardware interfaces (motor, encoder, IMU)
src/drivers/  MCU-specific driver implementations (firmware only)
src/app/      startup code, linker script, main entry point
tests/        Unity unit tests, run natively on the host
```

## Build & test

Host tests:
```
cmake -S . -B build-host -G Ninja
cmake --build build-host
ctest --test-dir build-host --output-on-failure
```

Firmware (cross-compiled for STM32F401):
```
cmake -S . -B build-fw -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake
cmake --build build-fw
```

## Status

Implemented: kinematics, bare-metal startup, and CI.
Planned: odometry, PID control, and hardware drivers.
