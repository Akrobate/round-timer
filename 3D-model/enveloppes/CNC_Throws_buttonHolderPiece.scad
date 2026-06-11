use <../pieces/subpieces/roundedBorderPaneSubpiece.scad>
use <../pieces/subpieces/paneFixationThrows.scad>
include <../configurations/global.scad>


module buttonFixationThrows(
    size_x = buttonHolderPiece_size.x,
    size_y = buttonHolderPiece_size.y,
    size_z = buttonHolderPiece_size.z * 4,
    throws_diameter = buttonHolderPiece_throws_diameter,
    throws_margin = buttonHolderPiece_throws_margin,
    button_diameter = buttonHolderPiece_button_diameter,
    correction_button_diameter = buttonFixationThrows_correction_button_diameter,
    $fn = 500
) {
    paneFixationThrows(
        size_x = size_x,
        size_y = size_y,
        size_z = size_z,
        head_throw_diameter = 0,
        head_throw_size_z = 0,
        throws_diameter = throws_diameter,
        throws_margin = throws_margin
    );

    cylinder(
        d = button_diameter + correction_button_diameter,
        h = size_z,
        center = true
    );
}


color(alpha = 0.2)
    buttonFixationThrows();