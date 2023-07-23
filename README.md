# DFT

- [DFT demo](https://code4fukui.github.io/DFT/)

## データ出典

- [世界で一番熱い町さばえ MP3 by Sing J Roy](https://www.city.sabae.fukui.jp/about_city/opendata/data_list/sekai-de-ichiban.html) [CC BY](https://creativecommons.org/licenses/by/4.0/deed.ja)

## ベンチマーク

44100samples

- M1 Macbook Pro, Deno in JavaScript, 33.18 sec
- M1 Macbook Pro, in C, 11.786060 sec
- M1 Macbook Pro, in C with 6 threads, 2.250893 sec
- Core i7-6700 Windows 10, Deno in JavaScript, 84.94 sec
- Core i7-6700 Windows 10, in C (gcc), 132.6863497 sec
- Core i7-6700 Windows 10, in C (nvcc), 34.3973202 sec

### Windowsでの時間計測方法

```
powershell -C Measure-Command {./a.exe}
```

### compile dft_st.c by nvcc on Windows

```
nvcc dft_st.c -D_USE_MATH_DEFINES
```
