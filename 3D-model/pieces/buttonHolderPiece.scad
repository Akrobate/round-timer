use <./subpieces/roundedBorderPaneSubpiece.scad>
use <./subpieces/paneFixationThrows.scad>

include <../configurations/global.scad>


module buttonHolderPiece(
    size_x = buttonHolderPiece_size.x,
    size_y = buttonHolderPiece_size.y,
    size_z = buttonHolderPiece_size.z,
    border_radius = buttonHolderPiece_border_radius,

    throws_diameter = buttonHolderPiece_throws_diameter,
    throws_margin = buttonHolderPiece_throws_margin,

    button_diameter = buttonHolderPiece_button_diameter,
    clips_button_diameter = buttonHolderPiece_clips_button_diameter,
    clips_button_thickness = buttonHolderPiece_clips_button_thickness,
    foolproof_button_diameter = buttonHolderPiece_foolproof_button_diameter,
    foolproof_button_thickness = buttonHolderPiece_foolproof_button_thickness,

    correction_button_diameter = buttonHolderPiece_correction_button_diameter,
    correction_clips_button_diameter = buttonHolderPiece_correction_clips_button_diameter,
    correction_clips_button_thickness = buttonHolderPiece_correction_clips_button_thickness,
    correction_foolproof_button_diameter = buttonHolderPiece_correction_foolproof_button_diameter,
    correction_foolproof_button_thickness = buttonHolderPiece_correction_foolproof_button_thickness,
    $fn = buttonHolderPiece_fn
) {

    translate([0,0,size_z/2])
    difference() {
        roundedBorderPaneSubpiece(
            size_x = size_x,
            size_y = size_y,
            size_z = size_z,
            border_radius = border_radius
        );
        buttonEnveloppe(
            button_diameter = button_diameter + correction_button_diameter,
            clips_button_diameter = clips_button_diameter + correction_clips_button_diameter,
            clips_button_thickness = clips_button_thickness + correction_clips_button_thickness,
            foolproof_button_diameter = foolproof_button_diameter + correction_foolproof_button_diameter,
            foolproof_button_thickness = foolproof_button_thickness + correction_foolproof_button_thickness,
            size_z = size_z
        );
        translate([0,0,-1.8])
            paneFixationThrows(
                size_x = size_x,
                size_y = size_y,
                size_z = size_z,
                
                head_throw_diameter = 6.4,
                head_throw_size_z = 1.82,

                throws_diameter = throws_diameter,
                throws_margin = throws_margin
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

buttonHolderPiece();
