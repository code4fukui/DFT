import { WaveFile } from "https://code4fukui.github.io/wavefile-es/index.js";
import { dft, idft, makeLen } from "./DFT.js";
import { Int16 } from "./Int16.js";
import { Float32 } from "./Float32.js";

const fn = "sekaideichiban.wav";
const fndst = "sekaideichiban-make.wav";

const re = Float32.decode(await Deno.readFile(fn + "-re.f32.bin"));
const im = Float32.decode(await Deno.readFile(fn + "-im.f32.bin"));

console.log(re.length);

for (let i = 0; i < im.length; i++) {
  //im[i] = 0;
  const p = Math.sqrt(re[i] * re[i] + im[i] * im[i]);
  const th = Math.atan2(re[i], im[i]);
  const th2 = th + Math.PI / 4;
  re[i] = Math.cos(th2) * p;
  im[i] = Math.sin(th2) * p;
}

const now = performance.now();
const right2 = idft(re, im);
const dt = performance.now() - now;
console.log("idft time: " + dt / 1000 + "sec"); // 44100samples

await Deno.writeFile(fn + "-r-idftjs.i16.bin", Int16.encode(right2));

const wav = new WaveFile();

const samples = right2;
//console.log(samples);

// Create a mono wave file, 44.1 kHz, 16-bit with samples
wav.fromScratch(1, 44100, '16', samples);
await Deno.writeFile(fndst, wav.toBuffer());
