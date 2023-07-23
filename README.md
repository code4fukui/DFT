# DFT

- [DFT demo](https://code4fukui.github.io/DFT/)

## データ出典

- [世界で一番熱い町さばえ MP3 by Sing J Roy](https://www.city.sabae.fukui.jp/about_city/opendata/data_list/sekai-de-ichiban.html) [CC BY](https://creativecommons.org/licenses/by/4.0/deed.ja)

## ベンチマーク

### 44100 samples 1sec

- M1 Macbook Pro, Deno in JavaScript, 33.18 sec
- M1 Macbook Pro, in C, 11.786060 sec
- M1 Macbook Pro, in C with 6 threads, 2.250893 sec
- Core i7-6700 Windows 10, Deno in JavaScript, 84.94 sec
- Core i7-6700 Windows 10, in C (gcc), 132.6863497 sec
- Core i7-6700 Windows 10, in C (nvcc), 34.3973202 sec
- Core i7-6700 Windows 10 NVIDIA RXT 3060Ti, 0.074750 sec
- Core i7-6700 Windows 10 NVIDIA RXT 3060Ti, 0.007705 sec (fast-math)

### 132300 samples 3sec

- M1 Macbook Pro, in C with 6 threads, 22.464575 sec
- Core i7-6700 Windows 10 NVIDIA RXT 3060Ti, 0.690248 sec
- Core i7-6700 Windows 10 NVIDIA RXT 3060Ti, 0.044306 sec (fast-math)

### 441000 samples 10sec

- M1 Macbook Pro, in C with 6 threads, 266.189622 sec
- Core i7-6700 Windows 10 NVIDIA RXT 3060Ti, 9.357527 sec
- Core i7-6700 Windows 10 NVIDIA RXT 3060Ti, 0.387023 sec (fast-math)

### 6028176 samples all

- Core i7-6700 Windows 10 NVIDIA RXT 3060Ti, 63.493813 sec (fast-math)

### Windowsでの時間計測方法

```
powershell -C Measure-Command {./a.exe}
```

### compile dft_st.c by nvcc on Windows

```
nvcc dft_st.c -D_USE_MATH_DEFINES
```

### compile dft_mt.c by mac

```
gcc dft_mt.c -D__device__=
```
