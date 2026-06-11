include <../configurations/global.scad>

use <../pieces/subpieces/paneFixationThrows.scad>

module beeperHolderThrowsEnveloppe(
    size_x = beeperHolder_size.x,
    size_y = beeperHolder_size.y,
    size_z = beeperHolder_size.z,
    buzzer_throw_diameter = 12.5 + 2 + 1,
    throws_depth = 10,
    throw_diameter = 3.8
) {
    paneFixationThrows(
        size_x = size_x,
        size_y = size_y,
        size_z = throws_depth,
        head_throw_diameter = throw_diameter,
        head_throw_size_z = 0,
        throws_diameter = throw_diameter,
        throws_margin = 3
    );

    translate([0, 0, 0])
        cylinder(
            d = buzzer_throw_diameter,
            h = throws_depth,
            center = true
        );


}


color(alpha = 0.2)
    beeperHolderThrowsEnveloppe($fn = 500);