use <../openscad_modules/esp-module-holder-3d-model/pieces/fixation-holder-8266-D1-piece.scad>


module espFixationHolderPiece() {
    fixation_holder_piece_color = "yellow";
    color(fixation_holder_piece_color)
        fixationHolder8266D1Piece();
}

espFixationHolderPiece();
