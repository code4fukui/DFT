nvcc -D_USE_MATH_DEFINES -Xcompiler "/wd 4819" -use_fast_math dft_cuda.cu -o dft.exe
rem nvcc -D_USE_MATH_DEFINES -Xcompiler "/wd 4819" dft_cuda.cu
