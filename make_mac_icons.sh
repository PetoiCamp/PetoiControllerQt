ICON_FILE=$1

mkdir logo.iconset

sips -z 16 16 $ICON_FILE --out logo.iconset/icon_16.png
sips -z 16 16 $ICON_FILE --out logo.iconset/icon_16@2x.png

sips -z 32 32 $ICON_FILE --out logo.iconset/icon_32.png
sips -z 32 32 $ICON_FILE --out logo.iconset/icon_32@2x.png

sips -z 64 64 $ICON_FILE --out logo.iconset/icon_64.png
sips -z 64 64 $ICON_FILE --out logo.iconset/icon_64@2x.png

sips -z 128 128 $ICON_FILE --out logo.iconset/icon_128.png
sips -z 128 128 $ICON_FILE --out logo.iconset/icon_128@2x.png

sips -z 256 256 $ICON_FILE --out logo.iconset/icon_256.png
sips -z 256 256 $ICON_FILE --out logo.iconset/icon_256@2x.png

sips -z 512 512 $ICON_FILE --out logo.iconset/icon_512.png
sips -z 512 512 $ICON_FILE --out logo.iconset/icon_512@2x.png

iconutil -c icns logo.iconset