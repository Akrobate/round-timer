use <./subpieces/roundedBorderPaneSubpiece.scad>
use <./subpieces/paneFixationThrows.scad>

// Beeper diameter : 11.7mm

beeperHolderBackPiece();

module beeperHolderBackPiece(
    size_x = 30,
    size_y = 20,
    size_z = 2,
    _fn = 500
) {

    difference() {

        roundedBorderPaneSubpiece(
            size_x = size_x,
            size_y = size_y,
            size_z = size_z,

            border_radius = 3,

            $fn = 150
        );

        paneFixationThrows(
            size_x = size_x,
            size_y = size_y,
            size_z = size_z * 2,

            throws_diameter = 3.5,
            throws_margin = 3
        );
    }
}
