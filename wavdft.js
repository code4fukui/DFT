import { WaveFile } from "https://code4fukui.github.io/wavefile-es/index.js";
import { CBOR } from "https://js.sabae.cc/CBOR.js";
import { dft, idft, makeLen } from "./DFT.js";

const Int16 = {
  encode: (data) => {
    const bin = new Uint8Array(data.buffer);
    return bin;
    /*
    if (data instanceof Int16Array) {
      const bin = new Uint8Array(data.length * 2);
      let idx = 0;
      for (let i = 0; i < data.length; i++) {
        const d = data[i];
        bin[idx++] = d;
        bin[idx++] = d >> 8;
      }
      return bin;
    } else {
      throw new Error("not supported type");
    }
    */
  },
};

const t = new Int16Array(2);
t[0] = 1;
t[1] = 0x100;
await Deno.writeFile("test-r.i16.bin", Int16.encode(t));

const fn = "sekaideichiban.wav";
const dsec = 1;

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

await Deno.writeFile(fn + "-r.i16.bin", Int16.encode(right));

//Deno.exit();

const now = performance.now();
const freq = dft(right);
const dt = performance.now() - now;
console.log("time: " + dt / 1000 + "sec"); // 44100samples time: 33.18sec

await Deno.writeFile(fn + "-re.cbor", CBOR.encode(freq[0]));
const power = makeLen(freq[0], freq[1]);
await Deno.writeFile(fn + "-p.cbor", CBOR.encode(power));

