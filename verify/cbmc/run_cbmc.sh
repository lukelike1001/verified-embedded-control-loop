#!/usr/bin/env bash
set -e

cbmc \
    verify/cbmc/control_loop_cbmc.c \
    src/control_loop.c \
    --bounds-check \
    --pointer_check \
    --nan-check \
    --floatbv \
    --unwind 2 \
    --unwinding-assertions