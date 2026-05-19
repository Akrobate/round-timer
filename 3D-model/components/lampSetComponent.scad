use <lampComponent.scad>

module lampSetComponent(
    holder_diameter = 75,
    holder_spaces = 10,
) {

    translate([-holder_diameter - holder_spaces, 0, 0])
        lampComponent();

    translate([0,0,0])
        lampComponent();

    translate([holder_diameter + holder_spaces, 0, 0])
        lampComponent();

}

lampSetComponent();