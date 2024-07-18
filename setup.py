from setuptools import setup, Extension
import pybind11
import glob

c_file_dirs = [
    'cmodules/*.cpp',
    "src/lgfx/Fonts/efont/*.c",
    "src/lgfx/Fonts/IPA/*.c",
    "src/lgfx/utility/*.c",
    "src/lgfx/v1/*.cpp",
    "src/lgfx/v1/misc/*.cpp",
    "src/lgfx/v1/panel/Panel_Device.cpp",
    "src/lgfx/v1/platforms/framebuffer/*.cpp",
]

c_files = []
for c_dir in c_file_dirs:
    c_files += glob.glob(c_dir)

ext_modules = [
    Extension(
        "gfxpy",
        c_files,
        include_dirs=[pybind11.get_include(), "src"],
        language="c++",
        extra_compile_args=["-DLGFX_LINUX_FB"],
    ),
]

setup(
    name="gfxpy",
    version="0.1.0",
    ext_modules=ext_modules,
    description = "M5stack Python3 library.",
    long_description = open("README.md", "r", encoding="UTF-8").read(),
    long_description_content_type = "text/markdown",
    url = "https://www.m5stack.com",
    python_requires = ">=3.11",
    license = "FreeBSD",
    author = "Lovyan dianjixz",
    author_email = "dianjixz@m5stack.com",
)
