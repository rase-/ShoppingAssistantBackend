Remember to check that your linker can find your opencv libs, zxing libs (cpp
version compiled), and tesseract libs. These need to be installed and in your
linker's library path

I advice you to install both opencv and tesseract with your package manager. On
OS X you can find these from Homebrew (or Macports if you're into that).

Zxing can be installed anywhere, but remember to replace the path to it in
binding.gyp. This is given with -L to the linker, so look for that switch.
