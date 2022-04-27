#!/usr/bin/bash
valgrind --tool=cachegrind --branch-sim=yes ./tema2_neopt input_valgrind
# valgrind --tool=cachegrind --branch-sim=yes ./tema2_opt_m input_valgrind
# valgrind --tool=cachegrind --branch-sim=yes ./tema2_blas input_valgrind