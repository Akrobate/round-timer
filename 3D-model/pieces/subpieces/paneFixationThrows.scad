module paneFixationThrows(
    size_x = 25,
    size_y = 25,
    size_z = 1,

    head_throw_diameter = 3.5 * 2,
    head_throw_size_z = 2,

    throws_diameter = 3.5,
    throws_margin = 3,

    $fn = 150
) {
    translation_x = (size_x / 2) - throws_margin;
    translation_y = (size_y / 2) - throws_margin;

    union() {    
        translate([translation_x, translation_y, 0]) {
            cylinder(d = throws_diameter, h = size_z, center = true, $fn = $fn);
            paneFixationHeadThrows(
                size_z,
                head_throw_size_z,
                throws_diameter,
                head_throw_diameter,
                _fn = $fn
            );
        }

        translate([translation_x, -translation_y, 0]) {
            cylinder(d = throws_diameter, h = size_z, center = true, $fn = $fn);
            paneFixationHeadThrows(
                size_z,
                head_throw_size_z,
                throws_diameter,
                head_throw_diameter,
                _fn = $fn
            );
        }

        translate([-translation_x, translation_y, 0]){
            cylinder(d = throws_diameter, h = size_z, center = true, $fn = $fn);
            paneFixationHeadThrows(
                size_z,
                head_throw_size_z,
                throws_diameter,
                head_throw_diameter,
                _fn = $fn
            );
        }


        translate([-translation_x, -translation_y, 0]) {
            cylinder(d = throws_diameter, h = size_z, center = true, $fn = $fn);
            paneFixationHeadThrows(
                size_z,
                head_throw_size_z,
                throws_diameter,
                head_throw_diameter,
                _fn = $fn
            );
        }
    }
}


module paneFixationHeadThrows(
    size_z,
    head_throw_size_z,
    throws_diameter,
    head_throw_diameter,
    _fn
) {
    translate([0, 0, (size_z / 2) + (head_throw_size_z / 2) - 0.01])
        cylinder(d1 = throws_diameter, d2 = head_throw_diameter, h = head_throw_size_z, center = true, $fn = _fn);

}