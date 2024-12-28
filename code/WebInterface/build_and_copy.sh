#!/bin/bash

DIST_DIR="dist"

if [ -d "$DIST_DIR" ]; then
    rm -rf "$DIST_DIR"
fi

mkdir -p "$DIST_DIR"

cp index.html $DIST_DIR/index.html
cp style.css $DIST_DIR/style.css
cp repository.js $DIST_DIR/repository.js
cp index.js $DIST_DIR/index.js

SEARCH_STRING='<script src="mock-server.js"></script>'
REPLACE_STRING='<script src="repository.js"></script>'

ESCAPED_SEARCH_STRING=$(printf '%s\n' "$SEARCH_STRING" | sed -e 's/[\/&]/\\&/g' -e 's/"/\\\"/g')
ESCAPED_REPLACE_STRING=$(printf '%s\n' "$REPLACE_STRING" | sed -e 's/[\/&]/\\&/g' -e 's/"/\\\"/g')

sed -i "s/$ESCAPED_SEARCH_STRING/$ESCAPED_REPLACE_STRING/g" $DIST_DIR/index.html

generateFile() {
    input_file=$1
    output_file=$2
    var_name=$3

    header=$(cat <<EOF
#include <Arduino.h>

const char $var_name[] PROGMEM = R"rawliteral(
EOF
)

    footer=$(cat <<'EOF'
)rawliteral";
EOF
)
    file_content=$(cat $input_file)    
    echo -e "$header\n$file_content\n$footer\n" > $output_file
}


STATIC_H_FOLDER="../RoundTimerV2/lib/RoundTimerServer/static"

generateFile "$DIST_DIR/index.html" "$STATIC_H_FOLDER/round_timer_server_static_index_html.h" "round_timer_server_static_index_html"
generateFile "$DIST_DIR/style.css" "$STATIC_H_FOLDER/round_timer_server_static_style_css.h" "round_timer_server_static_style_css"
generateFile "$DIST_DIR/index.js" "$STATIC_H_FOLDER/round_timer_server_static_index_js.h" "round_timer_server_static_index_js"
generateFile "$DIST_DIR/repository.js" "$STATIC_H_FOLDER/round_timer_server_static_repository_js.h" "round_timer_server_static_repository_js"



