// insert sizes
// * diam = 4.6
// * length = 5.7


module angleHolderPiece(
    size_x = 25,
    size_y = 25,
    size_z = 8,
    round_border_radius = 0.2,
    round_corner_radius = 0.1,
    insert_throw_diameter = 4.2,
    insert_throw_length = 6,
    _fn = 500
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

    if (false) {
        insertThrows(
            half_size_x = half_size_x,
            half_size_y = half_size_y,
            half_size_z = half_size_z,
            insert_throw_diameter = insert_throw_diameter,
            insert_throw_length = insert_throw_length,

            insert_x_offset = insert_x_offset,
            insert_y_offset = insert_y_offset,

            insert_z_offset_x = insert_z_offset_x,
            insert_z_offset_y = insert_z_offset_y,
            _fn = _fn
        );
    }

    difference() {
        color(alpha = 0.1)
            hull() {
                translate([-(half_size_x - round_corner_radius), -(half_size_y - round_corner_radius), 0])
                    cylinder(r = round_corner_radius, h = size_z, center = true, $fn = _fn);

                translate([-half_size_x_without_radius, half_size_y_without_radius, 0])
                    cylinder(r = round_border_radius, h = size_z, center = true, $fn = _fn);
                
                translate([half_size_x_without_radius, -half_size_y_without_radius, 0])
                    cylinder(r = round_border_radius, h = size_z, center = true, $fn = _fn);
            }
        
        if (true) {
            insertThrows(
                half_size_x = half_size_x,
                half_size_y = half_size_y,
                half_size_z = half_size_z,
                insert_throw_diameter = insert_throw_diameter,
                insert_throw_length = insert_throw_length,

                insert_x_offset = insert_x_offset,
                insert_y_offset = insert_y_offset,

                insert_z_offset_x = insert_z_offset_x,
                insert_z_offset_y = insert_z_offset_y,

                _fn = _fn
            );
        }
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
    insert_z_offset_y,
    _fn
) {
    throw_offset = 0.01;

    // Y throw
    translate(
        [
            -half_size_x + insert_y_offset,
            (insert_throw_length / 2) - half_size_y - (throw_offset / 2),
            0
        ]
    )
        rotate([90, 0, 0])
            cylinder(d = insert_throw_diameter, h = insert_throw_length + throw_offset, center = true, $fn = _fn);

    // X throw
    translate(
        [
            (insert_throw_length / 2) - half_size_x - (throw_offset / 2),
            -half_size_y + insert_x_offset,
            0
        ]
    )
        rotate([0, 90, 0])
            cylinder(d = insert_throw_diameter, h = insert_throw_length + throw_offset, center = true, $fn = _fn);

    // Z throw
    translate(
        [
            -half_size_x + insert_z_offset_x,
            -half_size_y + insert_z_offset_y,
            -(insert_throw_length / 2) + half_size_z + (throw_offset / 2)
        ]
    )
        rotate([0, 0, 90])
            cylinder(d = insert_throw_diameter, h = insert_throw_length + throw_offset, center = true, $fn = _fn);
}



angleHolderPiece();