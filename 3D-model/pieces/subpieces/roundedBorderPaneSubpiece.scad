
module roundedBorderPaneSubpiece(
    size_x = 25,
    size_y = 25,
    size_z = 1,

    border_radius = 3,

    $fn = 150
) {

    if (border_radius == 0) {
        cube([size_x, size_y, size_z], center = true);
    } else {

        translation_x = (size_x / 2) - border_radius;
        translation_y = (size_y / 2) - border_radius;

        hull() {
            translate([translation_x, translation_y, 0])
                cylinder(r = border_radius, h = size_z, center = true, $fn = $fn);

            translate([translation_x, -translation_y, 0])
                cylinder(r = border_radius, h = size_z, center = true, $fn = $fn);

            translate([-translation_x, translation_y, 0])
                cylinder(r = border_radius, h = size_z, center = true, $fn = $fn);

            translate([-translation_x, -translation_y, 0])
                cylinder(r = border_radius, h = size_z, center = true, $fn = $fn);
        }
    }
}