use <../pieces/lampshadeHolderPiece.scad>
use <../pieces/lampshadePiece.scad>

module lampComponent() {
    color("DarkSlateGray") lampshadeHolderPiece($fn = $fn);
    color("PaleTurquoise", alpha = 0.5) lampshadePiece($fn = $fn);
}

lampComponent();