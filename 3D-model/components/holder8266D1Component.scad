use <../openscad_modules/esp-module-holder-3d-model/pieces/facade-holder-8266-D1-piece.scad>
use <../openscad_modules/esp-module-holder-3d-model/pieces/fixation-holder-8266-D1-piece.scad>

// @todo: Move pieces to real local pieces

/**
 * holder8266D1Component
 * @name holder8266D1Component
 * @description Full 8266 facade and holder
 * @type component
 */
 module holder8266D1Component(
   fixation_holder_position_y = 0.1,
   fixation_holder_position_z = 2,
   fixation_holder_position_x = 0,

   face_holder_piece_color = "lightgreen",
   fixation_holder_piece_color = "yellow",
) {

   color(face_holder_piece_color)
      facadeHolder8266D1Piece();

   color(fixation_holder_piece_color)
      translate([
         fixation_holder_position_x,
         fixation_holder_position_y,
         fixation_holder_position_z
      ])
         fixationHolder8266D1Piece();
}

holder8266D1Component();
