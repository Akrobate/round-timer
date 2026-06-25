include <../configurations/global.scad>

use <../pieces/beeperHolderPiece.scad>
use <../pieces/beeperHolderBackPiece.scad>


/**
 * beeperComponent
 * @name beeperComponent
 * @description beeperComponent
 * @type component
 */
module beeperComponent() {

    translate([0,0,beeperHolder_size.z / 2])
        beeperHolderPiece();

    translate([0,0,beeperHolder_size.z + beeperHolder_size.z / 2 + case_external_panes_thickness])
        beeperHolderBackPiece();
}


/**
 * @png
 * @colorscheme BeforeDawn
 * @view axes,scales
 */
beeperComponent();