export class DataViewer extends HTMLElement {
  constructor(data) {
    super();
    this.data = data;
    this.canvas = document.createElement("canvas");
    this.canvas.style.width = "100%";
    this.canvas.style.height = "100%";
    this.appendChild(this.canvas);
    this.g = this.canvas.getContext("2d");
    const show = () => {
      const wc = this.canvas.clientWidth;
      const hc = this.canvas.clientHeight;
      const dpr = devicePixelRatio;
      const w = wc * dpr;
      const h = hc * dpr;
      this.canvas.width = w;
      this.canvas.height = h;
      let miny = Number.MAX_VALUE;
      let maxy = Number.MIN_VALUE;
      for (let i = 0; i < this.data.length; i++) {
        const n = this.data[i];
        if (n < miny) {
          miny = n;
        }
        if (n > maxy) {
          maxy = n;
        }
      }
      const g = this.g;
      g.fillStyle = "white";
      g.fillRect(0, 0, w, h);
      //g.fillStyle = "black";
      g.strokeStyle = "black";
      for (let i = 0; i < w; i++) {
        const i2 = Math.floor(i / w * this.data.length);
        const n = this.data[i2];
        const m = (n - miny) / (maxy - miny) * h;
        //g.fillRect(i, m, 1, 1);
        if (i == 0) {
          g.moveTo(i, m);
        } else {
          g.lineTo(i, m);
        }
      }
      g.stroke();
    };
    //show();
    //this.addEventListener("resize", () => show());
    setTimeout(show, 1);
  }
};

customElements.define("data-viewer", DataViewer);
