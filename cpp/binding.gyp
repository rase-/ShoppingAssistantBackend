{
  "targets": [
    {
      "target_name": "cv",
      "sources": [ "main.cpp", "src/product_finder.cpp", "src/product_matcher.cpp", "src/barcode/ImageReaderSource.cpp", "src/barcode/jpgd.cpp", "src/barcode/lodepng.cpp" , "src/barcode/barcode_scanner.cpp", "strc/ocr/optical_character_recognition.cpp"],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "conditions": [[ 'OS=="mac"', { "xcode_settings": { "GCC_ENABLE_CPP_EXCEPTIONS": "YES" } } ]],
      "include_dirs": [ "/usr/local/include/", '/Users/tonykovanen//workspace/zxing/build/core/src'],  
      "link_settings": {
                        'libraries':    ['-lopencv_core -lopencv_features2d -lopencv_nonfree -lopencv_contrib -L/Users/tonykovanen/workspace/zxing/build/ -lzxing -llept -ltesseract'],
                        'library_dirs': ['/usr/local/lib/', '/Users/tonykovanen/workspace/zxing/build/'],
                       },
    }
  ]
}
