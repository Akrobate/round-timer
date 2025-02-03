#!/bin/bash


declare -g PIECES=(
angleHolderPiece
beeperHolderBackPiece
)


# Pieces png generation
for piece in "${PIECES[@]}"; do
    echo "Pièce : $piece"
    openscad --colorscheme="BeforeDawn" --view="axes,scales" -o png_files/pieces/$piece.png pieces/$piece.scad
done

#main preview
openscad --colorscheme="BeforeDawn" -o png_files/main.png main.scad
