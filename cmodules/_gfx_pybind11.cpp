
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// #define debug_line // printf("%s:%d %s %s %s \r\n", __FILE__, __LINE__, __FUNCTION__, __DATE__, __TIME__)

#define LGFX_USE_V1
#include <LGFX_AUTODETECT.hpp>
#include <LovyanGFX.hpp>

class _gfxpy {
   private:
    LGFX *_lcd;
    int _width;
    int _height;
    std::string _device_name;

   public:
    _gfxpy() : _lcd(NULL), _width(0), _height(0) {}
    _gfxpy(int width, int height, const std::string &device_name)
        : _lcd(NULL), _width(width), _height(height), _device_name(device_name) {}
    inline void init() {
        if ((_lcd == NULL) && (_width != 0) && (_height != 0) && (!_device_name.empty())) {
            _lcd = new LGFX(_width, _height, _device_name.c_str());
            _lcd->init();
        } else {
            pybind11::print("Please check the parameters of the display: \n    width:", _width, ", height:", _height,
                            ", device_name:", _device_name);
        }
    }
    inline void setRotation(int rotation) { _lcd->setRotation(rotation); }
    inline void setColorDepth(int bits) { _lcd->setColorDepth(bits); }
    inline void fillScreen() { _lcd->fillScreen(); }
    inline void drawPixel(int x, int y) { _lcd->drawPixel(x, y); }
    inline void drawFastVLine(int x, int y, int h) { _lcd->drawFastVLine(x, y, h); }
    inline void drawFastHLine(int x, int y, int w) { _lcd->drawFastHLine(x, y, w); }
    inline void drawRect(int x, int y, int w, int h) { _lcd->drawRect(x, y, w, h); }
    inline void fillRect(int x, int y, int w, int h) { _lcd->fillRect(x, y, w, h); }
    inline void drawRoundRect(int x, int y, int w, int h, int r) { _lcd->drawRoundRect(x, y, w, h, r); }
    inline void fillRoundRect(int x, int y, int w, int h, int r) { _lcd->fillRoundRect(x, y, w, h, r); }
    inline void drawCircle(int x, int y, int r) { _lcd->drawCircle(x, y, r); }
    inline void fillCircle(int x, int y, int r) { _lcd->fillCircle(x, y, r); }
    inline void drawEllipse(int x, int y, int rx, int ry) { _lcd->drawEllipse(x, y, rx, ry); }
    inline void fillEllipse(int x, int y, int rx, int ry) { _lcd->fillEllipse(x, y, rx, ry); }
    inline void drawLine(int x0, int y0, int x1, int y1) { _lcd->drawLine(x0, y0, x1, y1); }
    inline void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2) {
        _lcd->drawTriangle(x0, y0, x1, y1, x2, y2);
    }
    inline void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2) {
        _lcd->fillTriangle(x0, y0, x1, y1, x2, y2);
    }
    inline void drawBezier(int x0, int y0, int x1, int y1, int x2, int y2) { _lcd->drawBezier(x0, y0, x1, y1, x2, y2); }
    inline void drawArc(int x, int y, int r0, int r1, float angle0, float angle1) {
        _lcd->drawArc(x, y, r0, r1, angle0, angle1);
    }
    inline void fillArc(int x, int y, int r0, int r1, float angle0, float angle1) {
        _lcd->fillArc(x, y, r0, r1, angle0, angle1);
    }
    inline void startWrite(bool transaction) { _lcd->startWrite(transaction); }
    inline void endWrite() { _lcd->endWrite(); }

    inline void setColor(int r, int g, int b) { _lcd->setColor(r, g, b); }

    inline void setColor(int c) { _lcd->setColor(c, c, c); }

    inline int getRawColor() { return _lcd->getRawColor(); }
    inline void setRawColor(int c) { _lcd->setRawColor(c); }

    inline int height() { return _lcd->height(); }
    inline int width() { return _lcd->width(); }
    inline int getRotation() { return _lcd->getRotation(); }
    inline void getColorDepth() {}
    inline void getCursor() {}

    inline void setFont() {}

    inline void setTextScroll() {}

    inline void setCursor(int x, int y) { _lcd->setCursor(x, y); }
    inline void clear() { _lcd->clear(); }

    inline void drawEllipseArc() {}
    inline void fillEllipseArc() {}
    inline void drawQR() {}
    inline void drawJpg() {}
    inline void drawPng() {}
    inline void drawBmp() {}
    inline void drawImage() {}
    inline void drawRawBuf() {}
    inline void print() {}
    inline void printf() {}
    inline void newCanvas() {}

    inline void read() {}
    inline void write() {}
    inline void close() {}
    inline void setTextColor(int color) { _lcd->setTextColor(color); }
    inline void setTextColor(int fgcolor, int bgcolor) { _lcd->setTextColor(fgcolor, bgcolor); }
    inline void setTextSize(float size) { _lcd->setTextSize(size, size); }
    inline void setTextSize(float sx, float sy) { _lcd->setTextSize(sx, sy); }
    inline int drawString(const std::string &text, int x, int y) { return _lcd->drawString(text.c_str(), x, y); }

    inline void qrcode(const std::string &text, int x, int y, int w, int version) {
        _lcd->qrcode(text.c_str(), x, y, w, version);
    }

    inline void setTextStyle() {}

    void close_lcd() {
        if (_lcd) delete (_lcd);
        _lcd = NULL;
    };
    ~_gfxpy() { close_lcd(); }
};

PYBIND11_MODULE(gfxpy, m) {
    m.doc() = "Graphics library for M5Stack series  \n";
    m.def("delay", lgfx::delay, pybind11::arg("milliseconds"));
    pybind11::class_<_gfxpy>(m, "lgxfpy")
        .def(pybind11::init<int, int, const std::string &>())
        .def("init", &_gfxpy::init)
        .def("setRotation", &_gfxpy::setRotation, pybind11::arg("rotation"))
        .def("setColorDepth", &_gfxpy::setColorDepth, pybind11::arg("bits"))
        .def("fillScreen", &_gfxpy::fillScreen)
        .def("drawPixel", &_gfxpy::drawPixel, pybind11::arg("x"), pybind11::arg("y"))
        .def("drawFastVLine", &_gfxpy::drawFastVLine, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("h"))
        .def("drawFastHLine", &_gfxpy::drawFastHLine, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("w"))
        .def("drawRect", &_gfxpy::drawRect, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("w"),
             pybind11::arg("h"))
        .def("fillRect", &_gfxpy::fillRect, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("w"),
             pybind11::arg("h"))
        .def("drawRoundRect", &_gfxpy::drawRoundRect, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("w"),
             pybind11::arg("h"), pybind11::arg("r"))
        .def("fillRoundRect", &_gfxpy::fillRoundRect, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("w"),
             pybind11::arg("h"), pybind11::arg("r"))
        .def("drawCircle", &_gfxpy::drawCircle, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("r"))
        .def("fillCircle", &_gfxpy::fillCircle, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("r"))
        .def("drawEllipse", &_gfxpy::drawEllipse, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("rx"),
             pybind11::arg("ry"))
        .def("fillEllipse", &_gfxpy::fillEllipse, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("rx"),
             pybind11::arg("ry"))
        .def("drawLine", &_gfxpy::drawLine, pybind11::arg("x0"), pybind11::arg("y0"), pybind11::arg("x1"),
             pybind11::arg("y1"))
        .def("drawTriangle", &_gfxpy::drawTriangle, pybind11::arg("x0"), pybind11::arg("y0"), pybind11::arg("x1"),
             pybind11::arg("y1"), pybind11::arg("x2"), pybind11::arg("y2"))
        .def("fillTriangle", &_gfxpy::fillTriangle, pybind11::arg("x0"), pybind11::arg("y0"), pybind11::arg("x1"),
             pybind11::arg("y1"), pybind11::arg("x2"), pybind11::arg("y2"))
        .def("drawBezier", &_gfxpy::drawBezier, pybind11::arg("x0"), pybind11::arg("y0"), pybind11::arg("x1"),
             pybind11::arg("y1"), pybind11::arg("x2"), pybind11::arg("y2"))
        .def("drawArc", &_gfxpy::drawArc, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("r0"),
             pybind11::arg("r1"), pybind11::arg("angle0"), pybind11::arg("angle1"))
        .def("fillArc", &_gfxpy::fillArc, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("r0"),
             pybind11::arg("r1"), pybind11::arg("angle0"), pybind11::arg("angle1"))
        .def("height", &_gfxpy::height)
        .def("width", &_gfxpy::width)
        .def("getRawColor", &_gfxpy::getRawColor)
        .def("setRawColor", &_gfxpy::setRawColor, pybind11::arg("c"))
        .def("getRotation", &_gfxpy::getRotation)
        .def("setCursor", &_gfxpy::setCursor, pybind11::arg("x"), pybind11::arg("y"))
        .def("clear", &_gfxpy::clear)
        .def("setColor", pybind11::overload_cast<int, int, int>(&_gfxpy::setColor), pybind11::arg("r"),
             pybind11::arg("g"), pybind11::arg("b"))
        .def("setColor", pybind11::overload_cast<int>(&_gfxpy::setColor), pybind11::arg("c"))

        .def("setTextColor", pybind11::overload_cast<int>(&_gfxpy::setTextColor), pybind11::arg("color"))
        .def("setTextColor", pybind11::overload_cast<int, int>(&_gfxpy::setTextColor), pybind11::arg("fgcolor"),
             pybind11::arg("bgcolor"))
        .def("setTextSize", pybind11::overload_cast<float>(&_gfxpy::setTextSize), pybind11::arg("size"))
        .def("setTextSize", pybind11::overload_cast<float, float>(&_gfxpy::setTextSize), pybind11::arg("sx"),
             pybind11::arg("sx"))
        .def("drawString", &_gfxpy::drawString, pybind11::arg("text"), pybind11::arg("x"), pybind11::arg("y"))

        .def("qrcode", &_gfxpy::qrcode, pybind11::arg("text"), pybind11::arg("x"), pybind11::arg("y"),
             pybind11::arg("w"), pybind11::arg("version"))

        .def("fillCircle", &_gfxpy::fillCircle, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("r"));
}

// #include <pybind11/pybind11.h>

// namespace py = pybind11;

// class _gfxpy {
// public:
//     void someMethod() {
//         // 实现你的方法
//     }
// };

// PYBIND11_MODULE(example, m) {
//     py::class_<_gfxpy>(m, "lgxfpy")
//         .def("some_method", [](_gfxpy &self) {
//             // 在这里调用 _gfxpy 对象的方法
//             self.someMethod();
//         });
// }