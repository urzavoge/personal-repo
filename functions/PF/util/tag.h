#pragma once

#include "common.h"

struct Tag {
    std::string Name;
    size_t NumArguments = 0;

    Tag() = default;

    Tag(std::string&& name, size_t num) : Name(std::move(name)), NumArguments(num) {}
};

class TagStream {
  public:

    TagStream() = default;

    TagStream(Tag&& self, std::vector<TagStream>&& tags) : Self(std::move(self)), Tags(std::move(tags)) {}

    std::string Parse() const {
        std::stringstream ss;
        Tag real = std::move(FindRealSelf());
        if (real.NumArguments == 0) {
            return real.Name;
        }
        if (real.NumArguments == 1) {
            if (real.Name == "-" && !(Tags[0].Self.Name == "Sum" || Tags[0].Self.Name == "Minus")) {
                ss << "-" << Tags[0].Parse();
                return  ss.str();
            }

            ss << real.Name << "(" << Tags[0].Parse() << ")";
            return ss.str();
        }
        if (real.NumArguments == 2) {
            if (Tags[0].Self.Name == "Sum" || Tags[0].Self.Name == "Minus") {

            }
            if (real.Name == "^") {
                ss << "(";
            }
            ss << real.Name << "(" << Tags[0].Parse() << ", " << Tags[1].Parse() << ")";
            return ss.str();
        }
    }
  private:
    Tag&& FindRealSelf() const {
        Tag real;
        if (Self.Name == "UnMinus") {
            real.Name = "-";
        } else if (Self.Name == "Minus") {
            real.Name = "-";
        } else if (Self.Name == "Sum") {
            real.Name = "+";
        } else if (Self.Name == "Multiply") {
            real.Name = "*";
        } else if (Self.Name == "Divide") {
            real.Name = "/";
        } else if (Self.Name == "Power") {
            real.Name = "^";
        }
        return std::move(real);
    }


  private:
    Tag Self;
    std::vector<TagStream> Tags;
};
