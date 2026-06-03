
module squareThrowedPaneSubpiece(
    x_size = 50,
    y_size = 30,
    z_size = 5,
    x_throw_margin = 5,
    y_throw_margin = 5,
    throw_diameter = 3
) {
    throw_coords = [
        [x_throw_margin, y_throw_margin],
        [x_size - x_throw_margin, y_throw_margin],
        [x_size - x_throw_margin, y_size - y_throw_margin],
        [x_throw_margin, y_size - y_throw_margin]
    ];

    difference() {
        cube([x_size, y_size, z_size]);

        for(throw_coord = throw_coords) {
            translate(throw_coord)
                cylinder(h = 50, d = throw_diameter, center = true);
        }
    }
}

squareThrowedPaneSubpiece();