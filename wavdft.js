import { WaveFile } from "https://code4fukui.github.io/wavefile-es/index.js";
import { CBOR } from "https://js.sabae.cc/CBOR.js";
import { dft, idft, makeLen } from "./DFT.js";

const fn = "sekaideichiban.wav";
const dsec = .1;

const wav = new WaveFile();
wav.fromBuffer(await Deno.readFile(fn));
console.log(wav);

const data = wav.data.samples;
console.log(data.length);

const nlen = Math.floor(dsec * wav.fmt.sampleRate);
console.log(nlen);
//const nlen = data.length / 4;

const right = new Int16Array(nlen);
const left = new Int16Array(nlen);
for (let i = 0; i < nlen; i++) {
  const n = i * 4;
  right[i] = data[n] + (data[n + 1] << 8);
  left[i] = data[n + 2] + (data[n + 3] << 8);
}
const toArray = (ar) => {
  const res = new Array(ar.length);
  for (let i = 0; i < ar.length; i++) {
    res[i] = ar[i];
  }
  return res;
};
//await Deno.writeTextFile(fn + "-r.json", JSON.stringify(right));
//await Deno.writeTextFile(fn + "-l.json", JSON.stringify(left));
await Deno.writeFile(fn + "-r.cbor", CBOR.encode(toArray(right)));
await Deno.writeFile(fn + "-l.cbor", CBOR.encode(toArray(left)));

const freq = dft(right);
const power = makeLen(freq[0], freq[1]);
await Deno.writeFile(fn + "-p.cbor", CBOR.encode(power));
