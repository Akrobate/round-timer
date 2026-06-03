include <configurations/global.scad>

use <./components/lampSetComponent.scad>
use <./components/housingComponent.scad>

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

}


main();

