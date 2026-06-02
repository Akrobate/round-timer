include <../configurations/global.scad>

use <../pieces/topPanePiece.scad>
use <../pieces/bottomPanePiece.scad>
use <../pieces/leftPanePiece.scad>
use <../pieces/rightPanePiece.scad>
use <../pieces/frontPanePiece.scad>
use <../pieces/backPanePiece.scad>

use <../pieces/angleHolderPiece.scad>

module housingComponent() {

    // Panes
    color("DarkGoldenrod") {
        *translate([
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
    }

    color("Peru") {
        translate([
            0,
            case_external_panes_thickness,
            0
        ])
            rotate([90, 0, 90])
                leftPanePiece();

        translate([
            external_size.x - case_external_panes_thickness,
            case_external_panes_thickness,
            0
        ])
            rotate([90, 0, 90])
                rightPanePiece();
    }

    color("Goldenrod") {
        #translate([
            0,
            case_external_panes_thickness,
            0
        ])
            rotate([90, 0, 0])
                frontPanePiece();

        translate([
            0,
            external_size.y,
            0
        ])
            rotate([90, 0, 0])
                backPanePiece();
    }

    // angle Holders
    color("DimGray") {
        translate([0, 0, external_size.z - case_external_panes_thickness - angleHolderPiece_size_z])
            positionnedAngleHolders();
        
        translate([0, 0, angleHolderPiece_size_z + case_external_panes_thickness])
            mirror([0,0,1])
                positionnedAngleHolders();
    }


    module positionnedAngleHolders() {
        translate([case_external_panes_thickness, case_external_panes_thickness, 0])
            angleHolderPiece();

        translate([external_size.x - case_external_panes_thickness, case_external_panes_thickness, 0])
            rotate([0, 0, 90])
                angleHolderPiece();

        translate([external_size.x - case_external_panes_thickness, external_size.y - case_external_panes_thickness, 0])
            rotate([0, 0, 180])
                angleHolderPiece();

        translate([case_external_panes_thickness, external_size.y - case_external_panes_thickness, 0])
            rotate([0, 0, 270])
                angleHolderPiece();
    }
}

translate([0,0,0])
    housingComponent();