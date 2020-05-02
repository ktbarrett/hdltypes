#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include <hdltypes/logic.hpp>

#include <string>

using namespace hdltypes;


PYBIND11_MODULE(pyhdltypes, m)
{
    pybind11::class_<Logic>(m, "Logic")
        .def(pybind11::init<>())
        .def(pybind11::init<long>())
        .def(pybind11::init<bool>())
        .def(pybind11::init([](const std::string& s){
            if (s.length() != 1) {
                throw pybind11::value_error("Given value is not a Logic");
            }
            return Logic(s[0]);
        }))

        .def_property_readonly("value", &Logic::value)

        .def(pybind11::self == pybind11::self)
        .def(pybind11::self != pybind11::self)

        .def(pybind11::self & pybind11::self)
        .def(pybind11::self | pybind11::self)
        .def(pybind11::self ^ pybind11::self)
        .def(~pybind11::self)

        .def("__repr__", [](const Logic& l) {
            std::string res = "Logic(";
            res.push_back(l.value());
            res.push_back(')');
            return res;
        });

    m.def("is01", [](const Logic& l) {
        return is01(l);
    });
}
