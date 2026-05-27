include <../configurations/global.scad>

use <../pieces/topPanePiece.scad>
use <../pieces/bottomPanePiece.scad>
use <../pieces/leftPanePiece.scad>
use <../pieces/rightPanePiece.scad>

use <../pieces/frontPanePiece.scad>
use <../pieces/backPanePiece.scad>

module housingComponent() {

    translate([
        case_external_panes_thickness,
        case_external_panes_thickness,
        external_size.z - case_external_panes_thickness
    ])
        topPanePiece();

    translate([
        case_external_panes_thickness,
        case_external_panes_thickness,
        0
    ])
        bottomPanePiece();

    rotate([90, 0, 90])
        leftPanePiece();

}


housingComponent();