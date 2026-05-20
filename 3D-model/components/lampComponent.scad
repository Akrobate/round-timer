use <../pieces/lampshadeHolderPiece.scad>
use <../pieces/lampshadePiece.scad>

module lampComponent() {
    color("DarkSlateGray") lampshadeHolderPiece();
    color("PaleTurquoise", alpha = 0.5) lampshadePiece();
}

lampComponent();