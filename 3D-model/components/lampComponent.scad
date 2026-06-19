use <../pieces/lampshadeHolderPiece.scad>
use <../pieces/lampshadePiece.scad>
use <../pieces/boltJoinPiece.scad>
use <../openscad_modules/led/ledWS2812/ledWS2812.scad>

include <../configurations/global.scad>


module lampComponent() {

    translate([0, 0, boltJoinPiece_height])
        ledWS2812Grid();

    boltJoinPiece();
    
    color("DarkSlateGray")
        lampshadeHolderPiece();

    color("PaleTurquoise", alpha = 0.5)
        lampshadePiece();
}

lampComponent();