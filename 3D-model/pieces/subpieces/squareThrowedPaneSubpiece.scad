use <../../openscad_modules/commons/forEachCoord.scad>
use <../../openscad_modules/commons/generateCoords.scad>

module squareThrowedPaneSubpiece(
    x_size = 50,
    y_size = 30,
    z_size = 5,
    x_throw_margin = 5,
    y_throw_margin = 5,
    throw_diameter = 3
) {
    difference() {
        cube([x_size, y_size, z_size]);
        forEachCoord(generateFourCoords(x_size, y_size, x_throw_margin, y_throw_margin))
            cylinder(h = 50, d = throw_diameter, center = true);
    }
}

squareThrowedPaneSubpiece();