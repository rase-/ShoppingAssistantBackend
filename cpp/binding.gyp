{
  "targets": [
    {
      "target_name": "imgproc",
      "sources": [ "main.cpp", "src/barcode/ImageReaderSource.cpp", "src/barcode/jpgd.cpp", "src/barcode/lodepng.cpp" , "src/barcode/barcode_scanner.cpp", "src/ocr/optical_character_recognition.cpp", "src/logo/logo_matcher.cpp"],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "conditions": [[ 'OS=="mac"', { 
        "xcode_settings": { 
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
            "OTHER_CFLAGS": [ '-g', '-mmacosx-version-min=10.7', '-std=c++11', '-stdlib=libc++', '-O3', '-D__STDC_CONSTANT_MACROS', '-D_FILE_OFFSET_BITS=64', '-D_LARGEFILE_SOURCE', '-Wall' ],
            'OTHER_CPLUSPLUSFLAGS': [ '-g', '-mmacosx-version-min=10.7', '-std=c++11', '-stdlib=libc++', '-O3', '-D__STDC_CONSTANT_MACROS', '-D_FILE_OFFSET_BITS=64', '-D_LARGEFILE_SOURCE', '-Wall' ]
        },
        "libraries": ["-framework OpenCL", "-lc++ -lc++abi"]
      } ]],
      "include_dirs": [ "/usr/local/include/", '/Users/tonykovanen/workspace/zxing/build/core/src'],  
      "link_settings": {
                        'libraries':    ['<!@(pkg-config --libs opencv) -llept -ltesseract -L/Users/tonykovanen/workspace/zxing/build/ -lzxing'],
                        'library_dirs': ['/usr/local/lib/', '/Users/tonykovanen/workspace/zxing/build/'],
                       },
    }
  ]
}
