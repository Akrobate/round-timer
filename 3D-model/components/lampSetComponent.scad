use <lampComponent.scad>
include <../configurations/global.scad>


module lampSetComponent() {

    translate([external_size.x / 2, external_size.y / 2, 0]) {
        translate([-space_between_lamps, 0, 0])
            lampComponent();

        translate([0,0,0])
            lampComponent();

        translate([space_between_lamps, 0, 0])
            lampComponent();
    }
}

lampSetComponent();