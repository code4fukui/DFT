export const dft = (data) => {
  const len = data.length;
  //const re = new Array(len);
  //const im = new Array(len);
  const re = new Float32Array(len);
  const im = new Float32Array(len);
  for (let i = 0; i < len; i++) {
    let re1 = 0;
    let im1 = 0;
    const dth = 2 * Math.PI * i / len;
    let th = 0;
    for (let j = 0; j < len; j++) {
      const d = data[j];
      re1 += d * Math.cos(th);
      im1 -= d * Math.sin(th);
      th += dth;
    }
    re[i] = re1;
    im[i] = im1;
  }
  return [re, im];
};

export const idft = (re, im) => {
  const len = re.length;
  const re2 = new Array(len);
  const im2 = new Array(len);
  for (let i = 0; i < len; i++) {
    let re1 = 0.0;
    //let im1 = 0.0;
    for (let j = 0; j < len; j++) {
      const th = 2 * Math.PI * i * j / len;
      re1 += re[j] * Math.cos(th) - im[j] * Math.sin(th);
      //im1 += re[j] * Math.sin(th) + im[j] * Math.cos(th);
    }
    re2[i] = re1 / len;
    //im2[i] = im1 / len;
  }
  //return [re2, im2];
  return re2;
};

export const makeLen = (re, im) => {
  const res = new Array(re.length);
  for (let i = 0; i < re.length; i++) {
    res[i] = Math.sqrt(re[i] * re[i] + im[i] * im[i]);
  }
  return res;
};
