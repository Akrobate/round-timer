include <../configurations/global.scad>

 /**
 * boltJoinPiece
 * @name boltJoinPiece
 * @description LED Holder
 * @type piece
 * @parent root
 */
module boltJoinPiece(
    internal_diameter = boltJoinPiece_internal_diameter,
    external_diameter = boltJoinPiece_external_diameter,
    height = boltJoinPiece_height,
    z_center = false,
    $fn = 500
) {
    difference() {
        cylinder(d = external_diameter, h = height, center = z_center);
        cylinder(d = internal_diameter, h = height * 2, center = z_center);
    }
}


/**
 * @stl
 * @png
 * @colorscheme BeforeDawn
 * @view axes,scales
 */
boltJoinPiece($fn = 500);
