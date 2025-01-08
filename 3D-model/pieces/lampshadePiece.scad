lampshadePiece();
// lampshadePiece_v2();


module lampshadePiece(
    lampshade_diameter = 60,
    lampshade_height = 70,
    walled_width = 1,
    border_diameter = 64,
    border_height = 2,
    //$fn = 150
    $fn = 500
) {

    lampshade_internal_diameter = lampshade_diameter - (walled_width * 2);

    union () {
        scale([
            1,
            1,
            lampshade_height / (lampshade_diameter / 2) 
        ]) {

            difference() {
                sphere(d = lampshade_diameter, $fn = $fn);
                sphere(d = lampshade_internal_diameter, $fn = $fn);
                translate([0, 0, - lampshade_diameter / 4])
                    cube([border_diameter, border_diameter, lampshade_diameter / 2], center = true);
            }
        }

        difference() {
            cylinder(d = border_diameter, h = border_height);
            translate([0,0,-0.05])
                cylinder(d = lampshade_internal_diameter, h = border_height * 1.1);
        }
    }

}




module lampshadePiece_v2(
    lampshade_diameter = 60,
    lampshade_height = 70,
    walled_width = 1,
    border_diameter = 64,
    border_height = 2,
    //$fn = 150
    $fn = 500
) {

    lampshade_internal_diameter = lampshade_diameter - (walled_width * 2);

    union () {

        difference() {
            scale([
                1,
                1,
                lampshade_height / (lampshade_diameter / 2) 
            ]) {
                sphere(d = lampshade_diameter, $fn = $fn);
            }

            scale([
                1,
                1,
                (lampshade_height - walled_width) / (lampshade_diameter / 2) 
            ]) {
                sphere(d = lampshade_internal_diameter, $fn = $fn);
            }

            scale([
                1,
                1,
                lampshade_height / (lampshade_diameter / 2) 
            ]) {
            translate([0, 0, - lampshade_diameter / 4])
                    cube([border_diameter, border_diameter, lampshade_diameter / 2], center = true);
            }
        }

        difference() {
            cylinder(d = border_diameter, h = border_height);
            translate([0,0,-0.05])
                cylinder(d = lampshade_internal_diameter, h = border_height * 1.1);
        }
    }

}
