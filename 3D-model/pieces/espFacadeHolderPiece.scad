use <../openscad_modules/esp-module-holder-3d-model/pieces/facade-holder-8266-D1-piece.scad>


module espFacadeHolderPiece() {
    face_holder_piece_color = "lightgreen";
    color(face_holder_piece_color)
        facadeHolder8266D1Piece();
}

espFacadeHolderPiece();
