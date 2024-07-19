
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

   public:
    _gfxpy() {
        _lcd = NULL;
        _lcd = new LGFX(320, 240, "/dev/fb1");
    }
    inline void init() { _lcd->init(); }
    inline void setColor(int r, int g, int b) { _lcd->setColor(r, g, b); }
    inline void fillCircle(int x, int y, int r) { _lcd->fillCircle(x, y, r); }

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
        .def(pybind11::init())
        .def("init", &_gfxpy::init)
        .def("setColor", &_gfxpy::setColor, pybind11::arg("r"), pybind11::arg("g"), pybind11::arg("b"))
        .def("fillCircle", &_gfxpy::fillCircle, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("r"));
}
