#!/usr/bin/env bash
set -e

COMMON_FLAGS = "--bounds-check --pointer_check --nan-check --floatbv --unwind 2 --unwinding-assertions"

# FORMAL-01: Verify a single-step harness
cbmc verify/cbmc/control_loop_cbmc.c src/control_loop.c $COMMON_FLAGS
