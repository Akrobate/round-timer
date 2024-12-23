#!/bin/bash


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

generateFile "index.html" "$STATIC_H_FOLDER/round_timer_server_static_index_html.h" "round_timer_server_static_index_html"
generateFile "style.css" "$STATIC_H_FOLDER/round_timer_server_static_style_css.h" "round_timer_server_static_style_css"
generateFile "index.js" "$STATIC_H_FOLDER/round_timer_server_static_index_js.h" "round_timer_server_static_index_js"



