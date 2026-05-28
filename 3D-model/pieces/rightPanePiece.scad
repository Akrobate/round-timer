include <../configurations/global.scad>


module rightPanePiece(
    x_size = external_size.y - (case_external_panes_thickness * 2),
    y_size = external_size.z,
    z_size = case_external_panes_thickness
) {
    cube([x_size, y_size, z_size]);
}

rightPanePiece();