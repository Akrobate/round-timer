include <../configurations/global.scad>

use <../pieces/beeperHolderPiece.scad>
use <../pieces/beeperHolderBackPiece.scad>



module beeperComponent() {

    translate([0,0,beeperHolder_size.z / 2])
        beeperHolderPiece();

    translate([0,0,beeperHolder_size.z + beeperHolder_size.z / 2 + case_external_panes_thickness])
        beeperHolderBackPiece();

}

beeperComponent();