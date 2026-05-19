use <./components/lampSetComponent.scad>

$fn = 150;

holder_diameter = 75;
holder_spaces = 10;
lamp_set_margins = 10;
face_thickness = 60;

translate([0, 0, face_thickness])
    lampSetComponent(
        holder_diameter = holder_diameter,
        holder_spaces = holder_spaces
    );
topFace(
    holder_diameter = holder_diameter,
    holder_spaces = holder_spaces,
    lamp_set_margins = lamp_set_margins,
    face_thickness = face_thickness
);


module topFace(
    holder_diameter = 75,
    holder_spaces = 10,
    lamp_set_margins = 10,
    face_thickness = 4,
) {

    x_size = (holder_diameter * 3) + (holder_spaces * 2) + (lamp_set_margins * 2);
    y_size = holder_diameter + (lamp_set_margins * 2);
    echo("TopFace x size ", x_size, "mm");
    echo("TopFace y size ", y_size, "mm");
    color("Chocolate")
        translate([
            0,
            0,
            face_thickness / 2
        ])
        cube(
            [
                x_size,
                y_size,
                face_thickness
            ], 
            center = true
        );
}

