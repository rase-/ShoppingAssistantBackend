#include <tesseract/baseapi.h>
#include <tesseract/allheaders.h>
#include <string>

using namespace tesseract;

std::string RecognizeTex(std::string file_path) {
    TessBaseAPI api = TessBaseAPI();
    if (api.Init(NULL, "eng")) {
        return "";
    }

    Pix *image = pixRead(file_path.c_str());
    api.SetImage(image);
    std::string out_text = api.GetUTF8Text();
    api.End();
    pixDestroy(&image);
    return out_text;
}