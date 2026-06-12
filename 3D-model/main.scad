include <configurations/global.scad>

use <./components/lampSetComponent.scad>
use <./components/housingComponent.scad>

use <pieces/buttonHolderPiece.scad>

module main() {
    translate([0, 0, external_size.z])
        lampSetComponent();
    
    housingComponent();



    translate([external_size.x / 2, 0, external_size.z / 2])
        rotate([90,0,0])
            buttonHolderPiece();

    translate([external_size.x / 2 - space_between_lamps, 0, external_size.z / 2])
        rotate([90,0,0])
            buttonHolderPiece();


    translate([external_size.x / 2 + space_between_lamps, 0, external_size.z / 2])
        rotate([90,0,0])
            buttonHolderPiece();
}


main();

