include <../configurations/global.scad>
use <subpieces/squareThrowedPaneSubpiece.scad>


/**
 * bottomPanePiece
 * @name bottomPanePiece
 * @description bottomPanePiece
 * @type piece
 * @parent housingComponent
 */
module bottomPanePiece(
    x_size = external_size.x - (case_external_panes_thickness * 2),
    y_size = external_size.y - (case_external_panes_thickness * 2),
    z_size = case_external_panes_thickness,
    x_throw_margin = angleHolderPiece_insert_generic_offset,
    y_throw_margin = angleHolderPiece_insert_generic_offset,
    throw_diameter = throw_diameter
) {
    squareThrowedPaneSubpiece(
        x_size = x_size,
        y_size = y_size,
        z_size = z_size,
        x_throw_margin = x_throw_margin,
        y_throw_margin = y_throw_margin,
        throw_diameter = throw_diameter
    );
}


/**
 * @stl
 * @png
 * @colorscheme BeforeDawn
 * @view axes,scales
 */
bottomPanePiece();