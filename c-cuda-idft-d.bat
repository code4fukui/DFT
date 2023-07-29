nvcc -D_USE_MATH_DEFINES -Xcompiler "/wd 4819" -use_fast_math idft_cuda_d.cu -o idft_d.exe
rem nvcc -D_USE_MATH_DEFINES -Xcompiler "/wd 4819" idft_cuda.cu
