include <configurations/global.scad>


use <components/lampSetComponent.scad>
use <components/housingComponent.scad>
use <components/beeperComponent.scad>
use <components/holder8266D1Component.scad>
use <pieces/buttonHolderPiece.scad>

module main() {
    translate([0, 0, external_size.z])
        lampSetComponent();
    
    housingComponent();

    translate([beeperHolder_size.z + external_size.x,external_size.y / 2,external_size.z / 2])
        rotate([-90,0,90])
            beeperComponent();

    translate([external_size.x / 2, 0, external_size.z / 2])
        rotate([90,0,0])
            buttonHolderPiece();

    translate([external_size.x / 2 - space_between_lamps, 0, external_size.z / 2])
        rotate([90,0,0])
            buttonHolderPiece();


    translate([external_size.x / 2 + space_between_lamps, 0, external_size.z / 2])
        rotate([90,0,0])
            buttonHolderPiece();

    translate([0, external_size.y / 2, external_size.z / 2])
        rotate([0,0,-90])
            holder8266D1Component();
}


main();

