use <../pieces/espFacadeHolderPiece.scad>
use <../pieces/espFixationHolderPiece.scad>

/**
 * holder8266D1Component
 * @name holder8266D1Component
 * @description Full 8266 facade and holder
 * @type component
 */
 module holder8266D1Component(
   fixation_holder_position_y = 0.1,
   fixation_holder_position_z = 2,
   fixation_holder_position_x = 0
) {

   espFacadeHolderPiece();
   translate([
      fixation_holder_position_x,
      fixation_holder_position_y,
      fixation_holder_position_z
   ])
      espFixationHolderPiece();
}

holder8266D1Component();
