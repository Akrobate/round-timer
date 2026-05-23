include <../configurations/global.scad>

/**
 * lampshadePiece
 * @name lampshadePiece
 * @description lampshadePiece
 * @type piece
 * @parent root
 */
module lampshadePiece(
    lampshade_diameter = lampshade_piece_lampshade_diameter,
    lampshade_height = lampshade_piece_lampshade_height,
    walled_width = lampshade_piece_walled_width,
    border_diameter = lampshade_piece_border_diameter,
    border_height = lampshade_piece_border_height
) {

    lampshade_internal_diameter = lampshade_diameter - (walled_width * 2);

    union () {
        scale([
            1,
            1,
            lampshade_height / (lampshade_diameter / 2) 
        ]) {

            difference() {
                sphere(d = lampshade_diameter);
                sphere(d = lampshade_internal_diameter);
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
    lampshade_diameter = lampshade_piece_lampshade_diameter,
    lampshade_height = lampshade_piece_lampshade_height,
    walled_width = lampshade_piece_walled_width,
    border_diameter = lampshade_piece_border_diameter,
    border_height = lampshade_piece_border_height
) {

    lampshade_internal_diameter = lampshade_diameter - (walled_width * 2);
    union () {
        difference() {
            scale([
                1,
                1,
                lampshade_height / (lampshade_diameter / 2) 
            ]) {
                sphere(d = lampshade_diameter);
            }

            scale([
                1,
                1,
                (lampshade_height - walled_width) / (lampshade_diameter / 2) 
            ]) {
                sphere(d = lampshade_internal_diameter);
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


/**
 * @stl
 * @png
 * @colorscheme BeforeDawn
 * @view axes,scales
 */
lampshadePiece($fn = 500);

translate([100,0,0])
    lampshadePiece_v2($fn = 500);