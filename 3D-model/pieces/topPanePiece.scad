include <../configurations/global.scad>
use <subpieces/squareThrowedPaneSubpiece.scad>
use <../openscad_modules/commons/forEachCoord.scad>


module topPanePiece(
    x_size = external_size.x - (case_external_panes_thickness * 2),
    y_size = external_size.y - (case_external_panes_thickness * 2),
    z_size = case_external_panes_thickness,
    x_throw_margin = angleHolderPiece_insert_generic_offset,
    y_throw_margin = angleHolderPiece_insert_generic_offset,
    space_between_lamps = space_between_lamps,
    cable_throw_margin = topPanePiece_cable_throw_margin,
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

        throws_coords = [
            [x_size / 2, y_size / 2],
            [x_size / 2 + space_between_lamps, y_size / 2],
            [x_size / 2 - space_between_lamps, y_size / 2],
        ];

        forEachCoord(throws_coords)
            forEachCoord([[-cable_throw_margin, 0], [0,0], [cable_throw_margin,0]])
                cylinder(d = throw_diameter, h = z_size * 3, center = true);
    }
}


topPanePiece();