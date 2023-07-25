import { WaveFile } from "https://code4fukui.github.io/wavefile-es/index.js";
import { Int16 } from "./Int16.js";

//const fnsrc = "sekaideichiban.wav-r-idft.i16.bin";
const fnsrc = "sekaideichiban.wav-r-idftjs.i16.bin";
const fndst = "sekaideichiban-make.wav";

const wav = new WaveFile();

const samples = Int16.decode(await Deno.readFile(fnsrc));

console.log(samples);

// Create a mono wave file, 44.1 kHz, 16-bit with samples
wav.fromScratch(1, 44100, '16', samples);
await Deno.writeFile(fndst, wav.toBuffer());
