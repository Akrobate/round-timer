use <../enveloppes/CNC_Throws_buttonHolderPiece.scad>

include <../configurations/global.scad>


/**
 * frontPanePiece
 * @name frontPanePiece
 * @description frontPanePiece
 * @type piece
 * @parent housingComponent
 */
module frontPanePiece(
    x_size = external_size.x,
    y_size = external_size.z,
    z_size = case_external_panes_thickness,
    x_throw_margin = case_external_panes_thickness + angleHolderPiece_insert_generic_offset,
    y_throw_margin = case_external_panes_thickness + angleHolderPiece_size_z / 2,
    throw_diameter = throw_diameter
) {

    throw_coords = [
        [x_throw_margin, y_throw_margin],
        [x_size - x_throw_margin, y_throw_margin],
        [x_size - x_throw_margin, y_size - y_throw_margin],
        [x_throw_margin, y_size - y_throw_margin]
    ];

    difference() {
        cube([x_size, y_size, z_size]);

        for(throw_coord = throw_coords)
            translate(throw_coord)
                cylinder(h = 50, d = throw_diameter, center = true);

        for(throw_x_coord = [space_between_lamps, 0, -space_between_lamps])
            translate([x_size / 2 + throw_x_coord, y_size / 2, 0])
                buttonFixationThrows(size_z = 20);
    }

}


/**
 * @stl
 * @png
 * @colorscheme BeforeDawn
 * @view axes,scales
 */
frontPanePiece();