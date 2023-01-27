#! /usr/bin/env bash

# $1 Start Range for Slides
# $2 End Range for Slides
# $3 Chapter

SLIDES="src/chapter$3"

mkdir -p "$SLIDES/imgs"

pdftoppm -png -f $1 -l $2 "$SLIDES/hpp_chapter$3.pdf" "$SLIDES/imgs/hpp_chapter$3"

echo "" > "$SLIDES/README.md"
echo -e "# Slides\n" > "$SLIDES/slides$3.md"

for n in $(eval echo {$1..$2})
do
    echo -e "![Slides $n](./imgs/hpp_chapter$3-$n.png)" >> "$SLIDES/slides$3.md"
done
