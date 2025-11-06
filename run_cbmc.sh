#!/usr/bin/env bash
set -e

COMMON_FLAGS="--bounds-check --pointer-check --nan-check --floatbv --unwind 6 --unwinding-assertions"

# FORMAL-01: Verify a single-step harness
cbmc verify/cbmc/control_loop_cbmc.c src/control_loop.c $COMMON_FLAGS

# FORMAL-02: Verify a multi-step (unrolled) harness
cbmc verify/cbmc/control_loop_unrolled_cbmc.c src/control_loop.c $COMMON_FLAGS

# FORMAL-03: Check for varied gains
cbmc verify/cbmc/control_loop_gains_cbmc.c src/control_loop.c $COMMON_FLAGS
