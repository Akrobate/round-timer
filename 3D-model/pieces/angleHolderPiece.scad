include <../configurations/global.scad>


 /**
 * angleHolderPiece
 * @name angleHolderPiece
 * @description Piece to hold panes
 * @type piece
 * @parent housingComponent
 */
module angleHolderPiece(
    size_x = angleHolderPiece_size_x,
    size_y = angleHolderPiece_size_y,
    size_z = angleHolderPiece_size_z,
    round_border_radius = 0.2,
    round_corner_radius = 0.1,
    insert_throw_diameter = 4.2,
    insert_throw_length = 6,
    center = false
) {

    half_size_x = size_x / 2;
    half_size_y = size_y / 2;
    half_size_z = size_z / 2;

    insert_z_offset_x = 10;
    insert_z_offset_y = 10;
    insert_x_offset = 10;
    insert_y_offset = 10;

    half_size_x_without_radius = half_size_x - round_border_radius;
    half_size_y_without_radius = half_size_y - round_border_radius;

    translate([
        center ? 0 : half_size_x,
        center ? 0 : half_size_y,
        center ? 0 : half_size_z,
    ])
    difference() {
        hull() {
            translate([-(half_size_x - round_corner_radius), -(half_size_y - round_corner_radius), 0])
                cylinder(r = round_corner_radius, h = size_z, center = true);

            translate([-half_size_x_without_radius, half_size_y_without_radius, 0])
                cylinder(r = round_border_radius, h = size_z, center = true);
            
            translate([half_size_x_without_radius, -half_size_y_without_radius, 0])
                cylinder(r = round_border_radius, h = size_z, center = true);
        }
        
        insertThrows(
            half_size_x = half_size_x,
            half_size_y = half_size_y,
            half_size_z = half_size_z,
            insert_throw_diameter = insert_throw_diameter,
            insert_throw_length = insert_throw_length,

            insert_x_offset = insert_x_offset,
            insert_y_offset = insert_y_offset,

            insert_z_offset_x = insert_z_offset_x,
            insert_z_offset_y = insert_z_offset_y
        );
    }

}


module insertThrows(
    half_size_x,
    half_size_y,
    half_size_z,
    insert_throw_diameter,
    insert_throw_length,
    insert_x_offset,
    insert_y_offset,
    insert_z_offset_x,
    insert_z_offset_y
) {
    throw_offset = 0.01;

    // Y throw
    translate([
        -half_size_x + insert_y_offset,
        (insert_throw_length / 2) - half_size_y - (throw_offset / 2),
        0
    ])
        rotate([90, 0, 0])
            cylinder(d = insert_throw_diameter, h = insert_throw_length + throw_offset, center = true);

    // X throw
    translate([
        (insert_throw_length / 2) - half_size_x - (throw_offset / 2),
        -half_size_y + insert_x_offset,
        0
    ])
        rotate([0, 90, 0])
            cylinder(d = insert_throw_diameter, h = insert_throw_length + throw_offset, center = true);

    // Z throw
    translate([
        -half_size_x + insert_z_offset_x,
        -half_size_y + insert_z_offset_y,
        -(insert_throw_length / 2) + half_size_z + (throw_offset / 2)
    ])
        rotate([0, 0, 90])
            cylinder(d = insert_throw_diameter, h = insert_throw_length + throw_offset, center = true);
}


/**
 * @stl
 * @png
 * @colorscheme BeforeDawn
 * @view axes,scales
 */
angleHolderPiece($fn = 500);
