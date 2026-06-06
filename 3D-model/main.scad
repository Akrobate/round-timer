include <configurations/global.scad>

use <./components/lampSetComponent.scad>
use <./components/housingComponent.scad>

use <pieces/buttonHolderPiece.scad>


//$fn = 150;
$fn = 50;

holder_diameter = 75;
holder_spaces = 10;
lamp_set_margins = 10;
face_thickness = 60;


module main() {
    translate([0, 0, face_thickness])
        lampSetComponent(
            holder_diameter = holder_diameter,
            holder_spaces = holder_spaces,
            $fn = 50
        );

    translate([- external_size.x / 2, - external_size.y / 2, 0])
        housingComponent();


    translate([0, -external_size.y / 2, external_size.z / 2])
        rotate([90,0,0])
            buttonHolderPiece();

    translate([- space_between_lamps, -external_size.y / 2, external_size.z / 2])
        rotate([90,0,0])
            buttonHolderPiece();


    translate([space_between_lamps, -external_size.y / 2, external_size.z / 2])
        rotate([90,0,0])
            buttonHolderPiece();
}


main();

