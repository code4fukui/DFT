export const Float64 = {
  encode: (data) => {
    if (data instanceof Array) {
      data = new Float64Array(data);
    }
    const bin = new Uint8Array(data.buffer);
    return bin;
  },
  decode: (bin) => {
    return new Float64Array(bin.buffer);
  },
};
