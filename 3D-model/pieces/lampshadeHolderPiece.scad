include <../configurations/global.scad>

module lampshadeHolderPiece(
    holder_external_diameter = lampshade_holder_piece_holder_external_diameter,
    lampshade_diameter = lampshade_holder_piece_lampshade_diameter,
    lampshade_border_diameter = lampshade_holder_piece_lampshade_border_diameter,
    lampshade_border_height = lampshade_holder_piece_lampshade_border_height,
    holder_height = lampshade_holder_piece_holder_height,
    bolt_throws_count = lampshade_holder_piece_bolt_throws_count,
    bolt_throws_diameter = lampshade_holder_piece_bolt_throws_diameter,
    bolt_throws_z = lampshade_holder_piece_bolt_throws_z
) {
  
    difference() {
        cylinder(d1 = holder_external_diameter, d2 = holder_external_diameter, h = holder_height);
        translate([0,0,-0.05])
            cylinder(d = lampshade_diameter, h = holder_height * 1.1);

        translate([0,0,-0.05])
            cylinder(d = lampshade_border_diameter, h = lampshade_border_height + 0.05);
    

        bolt_throws_position_radius = (lampshade_border_diameter / 2) + (bolt_throws_diameter / 2);

        for(i = [0 : 360 / bolt_throws_count : 360]) {
            translate([
                cos(i) * bolt_throws_position_radius,
                sin(i) * bolt_throws_position_radius,
                bolt_throws_z
            ])
                boltThrow(
                    bolt_diameter = bolt_throws_diameter
                );
        }
    }
}


module boltThrow(
    bolt_length = 15,
    bolt_diameter = 3,
    head_diameter = 6,
    head_height = 10
) {
    union() {
        cylinder(d = head_diameter, h = head_height);

        translate([0,0,-bolt_length + 0.01])
            cylinder(d = bolt_diameter, h = bolt_length);
    }
}


lampshadeHolderPiece($fn = 500);