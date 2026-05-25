include <../configurations/global.scad>


module topPanePiece(
    x_size = external_size.x - case_external_panes_thickness,
    y_size = external_size.y - case_external_panes_thickness,
    z_size = case_external_panes_thickness
) {
    cube([x_size, y_size, z_size]);
}


topPanePiece();