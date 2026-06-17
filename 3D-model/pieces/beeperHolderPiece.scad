include <../configurations/global.scad>

use <./subpieces/roundedBorderPaneSubpiece.scad>
use <./subpieces/paneFixationThrows.scad>

 /**
 * beeperHolderPiece
 * @name beeperHolderPiece
 * @description Beeper diameter : 11.7mm
 * @type piece
 * @parent beeperComponent
 */
module beeperHolderPiece(
    size_x = beeperHolder_size.x,
    size_y = beeperHolder_size.y,
    size_z = beeperHolder_size.z,
    buzzer_diameter = beeperHolder_buzzer_diameter,
    buzzer_border_holder = beeperHolder_buzzer_border_holder,
    buzzer_holder_height = beeperHolder_buzzer_holder_height
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

        translate([0, -5, 0])
            for(i = [0:2:10]) {
                translate([0, i, 0])
                    rotate([60, 0, 0])
                        cube([15, 20, 1], center = true);
            }
    }

    difference() {

        translate([0, 0, size_z / 2])
            cylinder(d = buzzer_diameter + buzzer_border_holder, h = buzzer_holder_height);

        translate([0, 0, size_z / 2 - 0.01 + 1])
            cylinder(d = 12.5, h = 3 + 0.02);

        translate([0, 0, size_z / 2 - 0.01])
            cylinder(d = 9, h = 3);
    }
}


/**
 * @stl
 * @png
 * @colorscheme BeforeDawn
 * @view axes,scales
 */
beeperHolderPiece($fn = 150);
