
lampshadeHolderPiece();


module lampshadeHolderPiece(
    holder_external_diameter = 75,
    lampshade_diameter = 61,
    lampshade_border_diameter = 65,
    lampshade_border_height = 2.1,
    holder_height = 4,


    bolt_throws_count = 4,
    bolt_throws_diameter = 3.5,
    bolt_throws_z = 4,

    $fn = 500
    //$fn = 150
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