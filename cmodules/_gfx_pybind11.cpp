
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>

// #define debug_line // printf("%s:%d %s %s %s \r\n", __FILE__, __LINE__, __FUNCTION__, __DATE__, __TIME__)

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>

PYBIND11_MODULE(m5gfxpy, m)
{
    m.doc() = "Graphics library for M5Stack series  \n";
    m.def("delay", lgfx::delay, pybind11::arg("milliseconds"));
    // pybind11::class_<LGFX>(m, "_LGFX")
    //     .def(pybind11::init<int, int, std::string &>())
    //     .def("fillCircle", &LGFX::fillCircle, pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("r"))
    //     ;
}
