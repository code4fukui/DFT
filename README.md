# DFT

> 日本語のREADMEはこちらです: [README.ja.md](README.ja.md)

A simple audio processing demonstration using the Discrete Fourier Transform.

## Data Source

- [Sekaide Ichiban Atsui Machi Sabae MP3 by Sing J Roy](https://www.city.sabae.fukui.jp/about_city/opendata/data_list/sekai-de-ichiban.html) [CC BY](https://creativecommons.org/licenses/by/4.0/deed.ja)

## Benchmarks

The repository provides benchmarks for the Discrete Fourier Transform (DFT) implementation in different environments:

- M1 Macbook Pro, Deno in JavaScript: 33.18 sec
- M1 Macbook Pro, in C: 11.786060 sec
- M1 Macbook Pro, in C with 6 threads: 2.250893 sec
- Core i7-6700 Windows 10, Deno in JavaScript: 84.94 sec
- Core i7-6700 Windows 10, in C (gcc): 132.6863497 sec
- Core i7-6700 Windows 10, in C (nvcc): 34.3973202 sec
- Core i7-6700 Windows 10 NVIDIA RXT 3060Ti: 0.074750 sec
- Core i7-6700 Windows 10 NVIDIA RXT 3060Ti (fast-math): 0.007705 sec

## Compile and Run

### Windows

```
powershell -C Measure-Command {./a.exe}
```

Compile `dft_st.c` with `nvcc` on Windows:

```
nvcc dft_st.c -D_USE_MATH_DEFINES
```

### Mac

Compile `dft_mt.c` on Mac:

```
gcc dft_mt.c -D__device__=
```

## License

MIT License — see [LICENSE](LICENSE).