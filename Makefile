CBMC=cbmc

cbmc:
	$(CBMC) verify/cbmc/control_loop_cbmc.c src/control_loop.c \
		--bounds-check --pointer-check --nan-check --floatbv --unwind 2 --unwinding-assertions