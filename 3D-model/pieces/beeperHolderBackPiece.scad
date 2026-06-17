include <../configurations/global.scad>

use <./subpieces/roundedBorderPaneSubpiece.scad>
use <./subpieces/paneFixationThrows.scad>

 /**
 * beeperHolderBackPiece
 * @name beeperHolderBackPiece
 * @description Beeper diameter : 11.7mm
 * @type piece
 * @parent beeperComponent
 */
module beeperHolderBackPiece(
    size_x = beeperHolder_size.x,
    size_y = beeperHolder_size.y,
    size_z = beeperHolder_size.z
) {

    difference() {

        roundedBorderPaneSubpiece(
            size_x = size_x,
            size_y = size_y,
            size_z = size_z,
            border_radius = 3
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


/**
 * @stl
 * @png
 * @colorscheme BeforeDawn
 * @view axes,scales
 */
beeperHolderBackPiece($fn = 150);
