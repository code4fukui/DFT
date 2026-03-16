# DFT

離散フーリエ変換(Discrete Fourier Transform)を使った、簡単な音声処理のデモンストレーションです。

## データソース

- [Sekaide Ichiban Atsui Machi Sabae MP3 by Sing J Roy](https://www.city.sabae.fukui.jp/about_city/opendata/data_list/sekai-de-ichiban.html) [CC BY](https://creativecommons.org/licenses/by/4.0/deed.ja)

## ベンチマーク

各環境でのDFTの処理時間を計測しています。

### 44100サンプル 1秒

- M1 Macbook Pro, Deno in JavaScript: 33.18秒
- M1 Macbook Pro, C言語: 11.786060秒
- M1 Macbook Pro, C言語 (6スレッド): 2.250893秒
- Core i7-6700 Windows 10, Deno in JavaScript: 84.94秒
- Core i7-6700 Windows 10, C言語 (gcc): 132.6863497秒
- Core i7-6700 Windows 10, C言語 (nvcc): 34.3973202秒
- Core i7-6700 Windows 10 NVIDIA RTX 3060Ti: 0.074750秒
- Core i7-6700 Windows 10 NVIDIA RTX 3060Ti (fast-math): 0.007705秒

### 132300サンプル 3秒

- M1 Macbook Pro, C言語 (6スレッド): 22.464575秒
- Core i7-6700 Windows 10 NVIDIA RTX 3060Ti: 0.690248秒
- Core i7-6700 Windows 10 NVIDIA RTX 3060Ti (fast-math): 0.044306秒

### 441000サンプル 10秒 

- M1 Macbook Pro, C言語 (6スレッド): 266.189622秒
- Core i7-6700 Windows 10 NVIDIA RTX 3060Ti: 9.357527秒
- Core i7-6700 Windows 10 NVIDIA RTX 3060Ti (fast-math): 0.387023秒

### 6028176サンプル全体

- Core i7-6700 Windows 10 NVIDIA RTX 3060Ti (fast-math): 63.493813秒

## ライセンス

MIT License — see [LICENSE](LICENSE).