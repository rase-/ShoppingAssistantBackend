{
  "targets": [
    {
      "target_name": "cv",
      "sources": [ "main.cpp", "src/product_finder.cpp", "src/product_matcher.cpp" ],
      "include_dirs": [ "/usr/local/include/" ],  
      "link_settings": {
                        'libraries':    ['-lopencv_core -lopencv_features2d -lopencv_nonfree -lopencv_contrib', '~/workspace/zxing/build/libzxing.a'],
                        'library_dirs': ['/usr/local/lib/', '~/workspace/zxing/build/core/src'],
                       },
    }
  ]
}
