#!/bin/bash

# Default values
INPUT=""
OUTPUT=""
FPS=20        # Slightly higher for smoother motion
WIDTH=1080    # High definition width

while getopts "i:o:" opt; do
  case $opt in
    i) INPUT="$OPTARG" ;;
    o) OUTPUT="$OPTARG" ;;
    *) echo "Usage: $0 -i input.mp4 -o output.gif"; exit 1 ;;
  esac
done

if [[ ! -f "$INPUT" ]]; then
    echo "Error: Input file '$INPUT' not found."
    exit 1
fi

if [[ -z "$OUTPUT" ]]; then
    OUTPUT="${INPUT%.*}.gif"
fi

echo "Generating high-quality GIF..."

# Complex filter explanation:
# 1. split: creates two streams of the input
# 2. [0:v]palettegen: takes the first stream and creates a global palette
# 3. [1:v][p]paletteuse: takes the second stream and applies the palette
# stats_mode=diff: optimizes palette for moving parts vs static backgrounds
ffmpeg -i "$INPUT" -vf "fps=$FPS,scale=$WIDTH:-1:flags=lanczos,split[s0][s1];[s0]palettegen=stats_mode=diff[p];[s1][p]paletteuse=dither=sierra2_4a" -y "$OUTPUT"

echo "Success: $OUTPUT"
