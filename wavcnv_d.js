import { Float64 } from "./Float64.js";

const fn = "sekaideichiban.wav";
const re = Float64.decode(await Deno.readFile(fn + "-re.f64.bin"));
const im = Float64.decode(await Deno.readFile(fn + "-im.f64.bin"));

console.log(re.length);

for (let i = 0; i < im.length; i++) {
  const p = Math.sqrt(re[i] * re[i] + im[i] * im[i]);
  const th = Math.atan2(re[i], im[i]);
  //const th2 = th + Math.PI / 4;
  //const th2 = th + Math.PI / 32; // 11.25deg
  const th2 = th + Math.PI / 320; // 1.125deg
  re[i] = Math.cos(th2) * p;
  im[i] = Math.sin(th2) * p;
}

await Deno.writeFile(fn + "-re.f64.bin", Float64.encode(re));
await Deno.writeFile(fn + "-im.f64.bin", Float64.encode(im));
