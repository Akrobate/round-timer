use <lampComponent.scad>
use <../openscad_modules/commons/forEachCoord.scad>

include <../configurations/global.scad>


/**
 * lampSetComponent
 * @name lampSetComponent
 * @description lampSetComponent
 * @type component
 */
module lampSetComponent() {
    translate([
        external_size.x / 2,
        external_size.y / 2,
        0
    ])
        forEachCoord([
            [-space_between_lamps, 0, 0],
            [-0, 0, 0],
            [space_between_lamps, 0, 0]
        ])
            lampComponent();
}


/**
 * @png
 * @colorscheme BeforeDawn
 * @view axes,scales
 */
lampSetComponent();