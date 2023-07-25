export const Int16 = {
  encode: (data) => {
    if (data instanceof Array) {
      data = new Int16Array(data);
    }
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
  decode: (bin) => {
    return new Int16Array(bin.buffer);
  },
};

/*
const t = new Int16Array(2);
t[0] = 1;
t[1] = 0x100;
await Deno.writeFile("test-r.i16.bin", Int16.encode(t));
*/
