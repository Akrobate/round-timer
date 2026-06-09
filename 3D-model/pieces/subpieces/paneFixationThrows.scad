// @todo should be refactored to be used in panes

module paneFixationThrows(
    size_x = 25,
    size_y = 25,
    size_z = 1,
    head_throw_diameter = 3.5 * 2,
    head_throw_size_z = 2,
    throws_diameter = 3.5,
    throws_margin = 3,
    $fn = 150
) {
    translation_x = (size_x / 2) - throws_margin;
    translation_y = (size_y / 2) - throws_margin;

    coords_list = [
        [translation_x, translation_y, 0],
        [translation_x, -translation_y, 0],
        [-translation_x, translation_y, 0],
        [-translation_x, -translation_y, 0]
    ];

    union() {
        for (coord = coords_list)
            translate(coord) {
                cylinder(d = throws_diameter, h = size_z, center = true, $fn = $fn);
                translate([0, 0, (size_z / 2) + (head_throw_size_z / 2) - 0.01])
                    cylinder(d1 = throws_diameter, d2 = head_throw_diameter, h = head_throw_size_z, center = true);
            }

    }
}


paneFixationThrows(
    size_z = 20,
    head_throw_size_z = 0
);

paneFixationThrows();