#!/bin/bash

# Default values
INPUT=""
OUTPUT=""
FPS=20        # Slightly higher for smoother motion
DURATION=-1

while getopts "i:o:d:f:" opt; do
  case $opt in
    i) INPUT="$OPTARG" ;;
    o) OUTPUT="$OPTARG" ;;
    d) DURATION="$OPTARG" ;;
    f) FPS="$OPTARG" ;;
    *) echo "Usage: $0 -i input.mp4 -o output.gif -d 10 -f 20"; exit 1 ;;
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


if [[ $DURATION -gt 0 ]]; then
    echo "Trimming video to $DURATION seconds..."
    ffmpeg -i "$INPUT" -ss 0 -t $DURATION -vf "fps=$FPS,split[s0][s1];[s0]palettegen=stats_mode=diff:max_colors=64[p];[s1][p]paletteuse=dither=sierra2_4a" -y "$OUTPUT"
else
    echo "Using full video duration."
    ffmpeg -i "$INPUT" -vf "fps=$FPS,split[s0][s1];[s0]palettegen=stats_mode=diff:max_colors=64[p];[s1][p]paletteuse=dither=sierra2_4a" -y "$OUTPUT"
fi

echo "Success: $OUTPUT"
