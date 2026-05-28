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

    color("red")
    translate([
        0,
        case_external_panes_thickness,
        0
    ])
        rotate([90, 0, 90])
            leftPanePiece();

    color("red")
    translate([
        external_size.x - case_external_panes_thickness,
        case_external_panes_thickness,
        0
    ])
        rotate([90, 0, 90])
            rightPanePiece();


    color("green")
    translate([
        0,
        case_external_panes_thickness,
        0
    ])
        rotate([90, 0, 0])
            frontPanePiece();

    color("green")
    translate([
        0,
        external_size.y,
        0
    ])
        rotate([90, 0, 0])
            backPanePiece();
}


housingComponent();