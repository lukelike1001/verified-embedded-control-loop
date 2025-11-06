CBMC=cbmc
COMMON_FLAGS=--bounds-check --pointer-check --nan-check --floatbv --unwind 6 --unwinding-assertions

cbmc:
	$(CBMC) verify/cbmc/control_loop_cbmc.c src/control_loop.c $(COMMON_FLAGS)
	$(CBMC) verify/cbmc/control_loop_unrolled_cbmc.c src/control_loop.c $(COMMON_FLAGS)
	$(CBMC) verify/cbmc/control_loop_gains_cbmc.c src/control_loop.c $(COMMON_FLAGS)