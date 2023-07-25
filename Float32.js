export const Float32 = {
  encode: (data) => {
    if (data instanceof Array) {
      data = new Float32Array(data);
    }
    const bin = new Uint8Array(data.buffer);
    return bin;
  },
  decode: (bin) => {
    return new Float32Array(bin.buffer);
  },
};
