use <./subpieces/roundedBorderPaneSubpiece.scad>
use <./subpieces/paneFixationThrows.scad>

size_x = 30; // 27
size_y = 30; // 27
size_z = 2;
border_radius = 4; // 3

throws_diameter = 3.5;
throws_margin = 4; // 3

button_diameter = 19.5;
clips_button_diameter = 20.64;
clips_button_thickness = 4;
foolproof_button_diameter = 20.34;
foolproof_button_thickness = 2;

correction_button_diameter = 0.5;
correction_clips_button_diameter = 0.5;
correction_clips_button_thickness = 0.5;
correction_foolproof_button_diameter = 0.5;
correction_foolproof_button_thickness = 0.5;

_fn = 500;

/*
buttonHolderPiece(
    size_x = size_x,
    size_y = size_y,
    size_z = size_z,
    border_radius = border_radius,

    throws_diameter = throws_diameter,
    throws_margin = throws_margin,

    button_diameter = button_diameter,
    clips_button_diameter = clips_button_diameter,
    clips_button_thickness = clips_button_thickness,
    foolproof_button_diameter = foolproof_button_diameter,
    foolproof_button_thickness = foolproof_button_thickness,

    correction_button_diameter = correction_button_diameter,
    correction_clips_button_diameter = correction_clips_button_diameter,
    correction_clips_button_thickness = correction_clips_button_thickness,
    correction_foolproof_button_diameter = correction_foolproof_button_diameter,
    correction_foolproof_button_thickness = correction_foolproof_button_thickness,
    _fn = _fn
);
*/


color(alpha = 0.2)
    buttonFixationThrows(
        size_x = size_x,
        size_y = size_y,
        size_z = size_z * 4,
        border_radius = border_radius,

        throws_diameter = throws_diameter + 0.3,
        throws_margin = throws_margin,

        button_diameter = button_diameter,

        correction_button_diameter = correction_button_diameter + 4,

        _fn = _fn
    );


module buttonFixationThrows(
    size_x = 27,
    size_y = 27,
    size_z = 4,
    border_radius = 3,

    throws_diameter = 3.5,
    throws_margin = 3,

    button_diameter = 19.5,

    correction_button_diameter = 0.5,

    _fn = 500
) {
    paneFixationThrows(
        size_x = size_x,
        size_y = size_y,
        size_z = size_z,
        head_throw_diameter = 0,
        head_throw_size_z = 0,
        throws_diameter = throws_diameter,
        throws_margin = throws_margin,
        $fn = _fn
    );

    cylinder(
        d = button_diameter + correction_button_diameter,
        h = size_z,
        center = true,
        $fn = _fn
    );
}




// 4
// 2
// 19.5
// 20.34
// 20.64

module buttonHolderPiece(
    size_x = 27,
    size_y = 27,
    size_z = 2,
    border_radius = 3,

    throws_diameter = 3.5,
    throws_margin = 3,

    button_diameter = 19.5,
    clips_button_diameter = 20.64,
    clips_button_thickness = 4,
    foolproof_button_diameter = 20.34,
    foolproof_button_thickness = 2,

    correction_button_diameter = 0.5,
    correction_clips_button_diameter = 0.5,
    correction_clips_button_thickness = 0.5,
    correction_foolproof_button_diameter = 0.5,
    correction_foolproof_button_thickness = 0.5,

    _fn = 500
) {

    difference() {
        roundedBorderPaneSubpiece(
            size_x = size_x,
            size_y = size_y,
            size_z = size_z,
            border_radius = border_radius,
            $fn = _fn
        );
        buttonEnveloppe(
            button_diameter = button_diameter + correction_button_diameter,
            clips_button_diameter = clips_button_diameter + correction_clips_button_diameter,
            clips_button_thickness = clips_button_thickness + correction_clips_button_thickness,
            foolproof_button_diameter = foolproof_button_diameter + correction_foolproof_button_diameter,
            foolproof_button_thickness = foolproof_button_thickness + correction_foolproof_button_thickness,
            size_z = size_z,
            $fn = _fn
        );
        translate([0,0,-1.8])
        paneFixationThrows(
            size_x = size_x,
            size_y = size_y,
            size_z = size_z,
            
            head_throw_diameter = 6.4,
            head_throw_size_z = 1.82,

            throws_diameter = throws_diameter,
            throws_margin = throws_margin,
            $fn = _fn
        );
    }
}


module buttonEnveloppe(
    button_diameter = 19.5,
    clips_button_diameter = 20.64,
    clips_button_thickness = 4,
    foolproof_button_diameter = 20.34,
    foolproof_button_thickness = 2,
    size_z = 1,
    $fn = 150
) {

    height = size_z * 2;
    union() {
        cylinder(d = button_diameter, h = height, center = true, $fn = $fn);
        cube([clips_button_thickness, clips_button_diameter, height], center = true);

        translate([button_diameter / 2, 0, 0])
            cube([(foolproof_button_diameter - button_diameter) * 2, foolproof_button_thickness, height], center = true);
    }
}
