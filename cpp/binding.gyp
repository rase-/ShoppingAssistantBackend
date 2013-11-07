{
  "targets": [
    {
      "target_name": "cv",
      "sources": [ "main.cpp", "src/product_finder.cpp", "src/product_matcher.cpp", "src/barcode/*.cpp" ],
      "include_dirs": [ "/usr/local/include/", '/Users/tonykovanen//workspace/zxing/build/core/src'],  
      "link_settings": {
                        'libraries':    ['-lopencv_core -lopencv_features2d -lopencv_nonfree -lopencv_contrib -lzxing'],
                        'library_dirs': ['/usr/local/lib/', '/Users/tonykovanen//workspace/zxing/build'],
                       },
    }
  ]
}
