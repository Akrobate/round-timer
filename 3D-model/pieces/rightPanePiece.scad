use <subpieces/squareThrowedPaneSubpiece.scad>
use <../enveloppes/beeperHolderThrowsEnveloppe.scad>
include <../configurations/global.scad>


module rightPanePiece(
    x_size = external_size.y - (case_external_panes_thickness * 2),
    y_size = external_size.z,
    z_size = case_external_panes_thickness,
    x_throw_margin = angleHolderPiece_insert_generic_offset,
    y_throw_margin = case_external_panes_thickness + angleHolderPiece_size_z / 2,
    throw_diameter = throw_diameter
) {
    difference() {
        squareThrowedPaneSubpiece(
            x_size = x_size,
            y_size = y_size,
            z_size = z_size,
            x_throw_margin = x_throw_margin,
            y_throw_margin = y_throw_margin,
            throw_diameter = throw_diameter
        );

        translate([x_size, y_size, z_size] / 2)
            beeperHolderThrowsEnveloppe();
    }
}

rightPanePiece();