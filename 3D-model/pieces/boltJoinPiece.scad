
boltJoinPiece(
    internal_diameter = 3.5,
    external_diameter = 3.5 + (0.4 * 2),
    height = 3,
    _fn = 500
);

module boltJoinPiece(
    internal_diameter = 3.5,
    external_diameter = 3.5 + (0.4 * 6),
    height = 3,
    _fn = 500
) {

    difference() {
        cylinder(d = external_diameter, h = height, center = true, $fn = _fn);

        cylinder(d = internal_diameter, h = height * 2, center = true, $fn = _fn);
    }

}