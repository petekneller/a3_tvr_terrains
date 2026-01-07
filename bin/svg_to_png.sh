#! /bin/env sh

# Converts the SVG map image to a PNG suitable for use in Tacview
#
# Has dependency on python lib `cairosvg` which in turn depends on a native installation of Cairo

MAP_NAME=$1

export INPUT_REGEX='<style type=\"text/css"><!\[CDATA\[ polyline{ fill: none; }; ellipse{ stroke:url(#colorForest); fill: none; stroke-width: 4; } \]\]>'
export OUTPUT='<style type="text/css"><![CDATA[ polyline{ fill: none; }; ]]></style><style type="text/css"><![CDATA[ ellipse{ stroke:url(#colorForest); fill: none; stroke-width: 4; } ]]>'

unzip -p src/${MAP_NAME}.svg.zip | sed "s|${INPUT_REGEX}|${OUTPUT}|" | python -m cairosvg -o out/tacview/${MAP_NAME}.png -
