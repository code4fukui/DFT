nvcc -D_USE_MATH_DEFINES -Xcompiler "/wd 4819" -use_fast_math idft_cuda.cu -o idft.exe
rem nvcc -D_USE_MATH_DEFINES -Xcompiler "/wd 4819" idft_cuda.cu
