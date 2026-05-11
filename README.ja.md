# DFT

離散フーリエ変換（DFT）を用いたシンプルな音声処理のデモンストレーションです。

## データソース

- [Sekaide Ichiban Atsui Machi Sabae MP3 by Sing J Roy](https://www.city.sabae.fukui.jp/about_city/opendata/data_list/sekai-de-ichiban.html) [CC BY](https://creativecommons.org/licenses/by/4.0/deed.ja)

## ベンチマーク

本リポジトリでは、さまざまな環境における離散フーリエ変換（DFT）実装のベンチマークを提供しています。

- M1 Macbook Pro, JavaScript (Deno): 33.18秒
- M1 Macbook Pro, C言語: 11.786060秒
- M1 Macbook Pro, C言語（6スレッド）: 2.250893秒
- Core i7-6700 Windows 10, JavaScript (Deno): 84.94秒
- Core i7-6700 Windows 10, C言語 (gcc): 132.6863497秒
- Core i7-6700 Windows 10, C言語 (nvcc): 34.3973202秒
- Core i7-6700 Windows 10 NVIDIA RXT 3060Ti: 0.074750秒
- Core i7-6700 Windows 10 NVIDIA RXT 3060Ti (fast-math): 0.007705秒

## コンパイルと実行

### Windows

```
powershell -C Measure-Command {./a.exe}
```

Windows環境で `nvcc` を使用して `dft_st.c` をコンパイルする場合:

```
nvcc dft_st.c -D_USE_MATH_DEFINES
```

### Mac

Mac環境で `dft_mt.c` をコンパイルする場合:

```
gcc dft_mt.c -D__device__=
```

## ライセンス

MIT License — 詳細は [LICENSE](LICENSE) を参照してください。
