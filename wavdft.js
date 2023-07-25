import { WaveFile } from "https://code4fukui.github.io/wavefile-es/index.js";
import { CBOR } from "https://js.sabae.cc/CBOR.js";
import { dft, idft, makeLen } from "./DFT.js";
import { Int16 } from "./Int16.js";
import { Float32 } from "./Float32.js";

const fn = "sekaideichiban.wav";
const dsec = 1;
const all = false;
const dftinjs = true;

const wav = new WaveFile();
wav.fromBuffer(await Deno.readFile(fn));
console.log(wav);

const data = wav.data.samples;
console.log(data.length);

const nlen = all ? data.length / 4 : Math.floor(dsec * wav.fmt.sampleRate);
console.log(nlen);

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

await Deno.writeFile(fn + "-r.i16.bin", Int16.encode(right));

if (!dftinjs) Deno.exit();

let freq;
{
  const now = performance.now();
  freq = dft(right);
  const dt = performance.now() - now;
  console.log("dft time: " + dt / 1000 + "sec"); // 44100samples time: 33.18sec

  await Deno.writeFile(fn + "-re.f32.bin", Float32.encode(freq[0]));
  await Deno.writeFile(fn + "-im.f32.bin", Float32.encode(freq[1]));
  const power = makeLen(freq[0], freq[1]);
  //await Deno.writeFile(fn + "-p.cbor", CBOR.encode(power));
  await Deno.writeFile(fn + "-p.f32.bin", Float32.encode(power));
}
