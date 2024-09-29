#pragma once

#include "object.h"
#include "util/defines.h"
#include "util/tag.h"

namespace PF {

    template <typename T>
    class IPFunctionBase {
      public:
        using Domain = T;

        virtual Domain Eval(Domain x) const = 0;

        virtual TagStream Tag() const = 0;

        virtual ~IPFunctionBase() = default;
    };

    template <typename T>
    class TPFunctionConst : public IPFunctionBase<T> {
      public:

        using Base = IPFunctionBase<T>;

        TPFunctionConst(Base::Domain k) : K_(k) {}

        Base::Domain Eval(Base::Domain) const override {
            return K_;
        }

        TagStream Tag() const override {
            return {{std::to_string(K_), 0}, {}};
        }

        ~TPFunctionConst() override = default;

      private:
        const Base::Domain K_;
    };

    template <typename T>
    class TPFunctionId : public IPFunctionBase<T> {
      public:

        using Base = IPFunctionBase<T>;

        TPFunctionId() = default;

        Base::Domain Eval(Base::Domain arg) const override {
            return arg;
        }

        TagStream Tag() const override {
            return {{"x", 0}, {}};
        }

        ~TPFunctionId() override = default;
    };

    template <typename T>
    T EvalHelpers(PF::TFunctionPtr<T> obj, T arg) {return obj.Eval(arg);}
}