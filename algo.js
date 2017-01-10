function* algorithm() {

    // number of simulated pixels in the buffer, use the Golden ratio 1.618 to make them
    // approximately square

    var kW = 64;
    var kH = (kW / 1.618) >> 0;

    // grid layout is used to show the pixels

    var layout = new algo.layout.GridLayout(algo.BOUNDS.inflate(-10, -10), kH, kW);

    // create an array visualizer with a simple grid layout object

    var visualizer = new algo.core.PixelBuffer({

        // dimensions of buffer

        width: kW,
        height: kH,

        // called whenever a new pixel element is required. updatePixel will called
        // immediately after, for now we just have to create the element
        createPixel: _.bind(function(x, y) {

            return new algo.render.Rectangle({
                strokeWidth: 0
            });

        }, this),

        // update pixel element color and position
        updatePixel: _.bind(function(x, y, pixel, element) {

            element.set({
                fill: pixel
            });
            element.fillBox(layout.getBox(y, x).inflate(-1, -1));

        }, this),

        // destroy a pixel
        destroyPixel: _.bind(function(x, y, element) {
            element.destroy();
        }, this)

    });

    // -----------------------------------------------------------------------------------------------------------------


    // help functions, plot gets called from within the line drawing
    // algorithm itself. c is the intensity of the pixel with 1.0 meaning
    // full color and zero meaning no color. It should be used as a multiplier
    // for the RGB channels of the pixel. In this simple example we just use
    // it to create a grayscale pixel

    function plot(x, y, c, rgb) {

        // anti aliasing algorithms might try to draw outside of the pixel
        // buffer so ignore edge cases

        if (x < 0 || y < 0 || x >= kW || y >= kH) return;

        visualizer.setPixel(x, y, {
            red: rgb.getRed(),
            green: rgb.getGreen(),
            blue: rgb.getBlue(),
            alpha: c
        });
    }

    /**
     * integer part of x
     * @param x
     * @returns {*}
     */
    function ipart(x) {
        return x >> 0;
    }

    /**
     * round x to nearest integer
     * @param x
     * @returns {*}
     */
    function round(x) {
        return ipart(x + 0.5);
    }

    /**
     * fractional part of x
     * @param x
     */
    function fpart(x) {

        // fractional part must be unsigned
        var n = Math.abs(x);
        return n - Math.floor(n);
    }

    /**
     * 1 - the fractional part of x
     * @param x
     */
    function rfpart(x) {
        return 1 - fpart(x);
    }

    /**
     * the core of the Xialin Wu, algorithm
     * @param x0
     * @param y0
     * @param x1
     * @param y1
     * @param {red, green, blue, alpha} rgb
     */
    //=drawLine
    function* drawLine(x0, y0, x1, y1, rgb) {

        var steep = Math.abs(y1 - y0) > Math.abs(x1 - x0);

        if (steep) {
            y0 = [x0, x0 = y0][0]; // swap x0/y0
            y1 = [x1, x1 = y1][0]; // swap x1, y1
        }

        if (x0 > x1) {
            x1 = [x0, x0 = x1][0]; // swap x0/x1
            y1 = [y0, y0 = y1][0]; // swap y0/y1
        }

        var dx = x1 - x0;
        var dy = y1 - y0;

        var gradient = dy / dx;

        // handle first endpoint

        var xend = round(x0);
        var yend = y0 + gradient * (xend - x0);
        var xgap = rfpart(x0 + 0.5);
        var xpxl1 = xend;
        var ypxl1 = ipart(yend);

        if (steep) {
            plot(ypxl1, xpxl1, rfpart(yend) * xgap, rgb);
            plot(ypxl1 + 1, xpxl1, fpart(yend) * xgap, rgb);
        } else {
            plot(xpxl1, ypxl1, rfpart(yend) * xgap, rgb);
            plot(xpxl1, ypxl1 + 1, fpart(yend) * xgap, rgb);
        }

        var intery = yend + gradient;

        // handle second endpoint

        xend = round(x1);
        yend = y1 + gradient * (xend - x1);
        xgap = fpart(x1 + 0.5);
        var xpxl2 = xend;
        var ypxl2 = ipart(yend);

        if (steep) {
            plot(ypxl2, xpxl2, rfpart(yend) * xgap, rgb);
            plot(ypxl2 + 1, xpxl2, fpart(yend) * xgap, rgb);
        } else {
            plot(xpxl2, ypxl2, rfpart(yend) * xgap, rgb);
            plot(xpxl2, ypxl2 + 1, fpart(yend) * xgap, rgb);
        }

        // main loop

        for (var x = xpxl1 + 1; x < xpxl2; x += 1) {

            if (steep) {
                plot(ipart(intery), x, rfpart(intery), rgb);
                plot(ipart(intery) + 1, x, fpart(intery), rgb);
            } else {
                plot(x, ipart(intery), rfpart(intery), rgb);
                plot(x, ipart(intery) + 1, fpart(intery), rgb);
            }

            intery = intery + gradient;
        }

        yield({
            step: _.sprintf("drawLine renders the anti-aliased line using optimal integer calculations."),
            variables: {
                x0: x0 >> 0,
                y0: y0 >> 0,
                x1: x1 >> 0,
                y1: y1 >> 0
            },
            line: "drawLine"
        });
    }

    // draw a square within the circle cx,cy,r starting at degrees i using color rgb
    //=drawSquare
    function* drawSquare(cx, cy, r, i, rgb) {

        // get 4 points on a circle starting at i degrees

        var pts = [
            algo.core.pointOnCircle(cx, cy, r, i),
            algo.core.pointOnCircle(cx, cy, r, (i + 90) % 360),
            algo.core.pointOnCircle(cx, cy, r, (i + 180) % 360),
            algo.core.pointOnCircle(cx, cy, r, (i + 270) % 360),
        ];

        yield* drawLine(pts[0].x, pts[0].y, pts[1].x, pts[1].y, rgb);
        yield* drawLine(pts[1].x, pts[1].y, pts[2].x, pts[2].y, rgb);
        yield* drawLine(pts[2].x, pts[2].y, pts[3].x, pts[3].y, rgb);
        yield* drawLine(pts[3].x, pts[3].y, pts[0].x, pts[0].y, rgb);
    }

    var steps = 10,
        r = (kH >> 1) - 1,
        xc = [r, kW >> 1, kW - r - 1];


    var colors = [algo.Color.iRED, algo.Color.iGREEN, algo.Color.iBLUE];

    for (var i = 10; i < 360; i += steps) {

        // draw three squares
        for (var j = 0; j < 3; j += 1) {
            yield* drawSquare(xc[j], kH >> 1, (kH >> 1) - 1, i, colors[j]);
        }


        visualizer.clear();
    }

    yield ({
        step: 'Done'
    });
}
