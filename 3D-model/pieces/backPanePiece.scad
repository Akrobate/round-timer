include <../configurations/global.scad>

module backPanePiece(
    x_size = external_size.x,
    y_size = external_size.z,
    z_size = case_external_panes_thickness,
    x_throw_margin = case_external_panes_thickness + angleHolderPiece_insert_generic_offset,
    y_throw_margin = case_external_panes_thickness + angleHolderPiece_size_z / 2,
    throw_diameter = throw_diameter
) {

    debug = false;

    if (debug) {
        translate([x_size / 2, y_size - 10])
            cylinder(h = 50, r = 10, center = true);
    }

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

backPanePiece();