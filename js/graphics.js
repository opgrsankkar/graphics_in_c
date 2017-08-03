document.body.setAttribute("style", "margin: 0;");
var canvas = document.getElementById('stage');

canvas.width = window.innerWidth
    || document.documentElement.clientWidth
    || document.body.clientWidth;
canvas.height = window.innerHeight
    || document.documentElement.clientHeight
    || document.body.clientHeight;
var g = canvas.getContext("2d");

g.getmaxx = function () { return canvas.width; };
g.getmaxy = function () { return canvas.height; };

g.putpixel = function (x, y) {
    g.fillRect(x, y, 1, 1);
};

g.line = function (x1, y1, x2, y2) {
    g.beginPath();
    g.moveTo(x1, y1);
    g.lineTo(x2, y2);
    g.stroke();
};

g.rectangle = function (x1, y1, x2, y2) {
    g.strokeRect(x1, y1, x2-x1, y2-y1);
};

g.circle = function (cx, cy, r) {
    g.beginPath();
    g.arc(cx, cy, r, 0, 2*Math.PI);
    g.stroke();
};

g.cleardevice = function () {
    g.clearRect(0,0,g.getmaxx(),g.getmaxy());
};
g.delay = function (ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
  }
