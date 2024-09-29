#define DECLARE_DOUBLE_ARG_OPERATION(operation, name) template <typename T> \
    PF::TFunctionPtr<T> operation(const PF::TFunctionPtr<T>& first, const PF::TFunctionPtr<T>& second) { \
        return MakeShared<PF::TPFunction##name<T>>(first, second); \
    } \
    template <typename T, typename U> \
    PF::TFunctionPtr<T> operation(const PF::TFunctionPtr<T>& first, const U& second) { \
        return MakeShared<PF::TPFunction##name<T>>(first, PF::TFunctionPtr<T>(second)); \
    } \
    template <typename T, typename U> \
    PF::TFunctionPtr<T> operation(const U& first, const PF::TFunctionPtr<T>& second) { \
        return MakeShared<PF::TPFunction##name<T>>(PF::TFunctionPtr<T>(first), second); \
    }

#define DECLARE_SINGLE_ARG_OPERATION(operation, name) template <typename T> \
    PF::TFunctionPtr<T> operation(const PF::TFunctionPtr<T>& func) { \
        return MakeShared<PF::TPFunction##name<T>>(func); \
    } \
    template <typename T, typename U> \
    PF::TFunctionPtr<T> operation(const U& val) { \
        return MakeShared<PF::TPFunction##name<T>>(PF::TFunctionPtr<T>(val)); \
    }

#define DECLARE_SINGLE_ARG_FUNCTION_CLASS(name, lambda) namespace PF { template <typename T> \
class TPFunction##name : public IPFunctionBase<T> { \
  public: \
    using Base = IPFunctionBase<T>; \
    explicit TPFunction##name(TFunctionPtr<T> func) : Func_(func) {} \
    ~TPFunction##name() override = default; \
    Base::Domain Eval(Base::Domain arg) const override { return lambda; } \
    TagStream Tag() const override { return {{#name, 1}, {Func_->Tag()}}; } \
  private: \
    TFunctionPtr<T> Func_; \
};}

#define DECLARE_DOUBLE_ARG_FUNCTION_CLASS(name, lambda) namespace PF { template <typename T> \
class TPFunction##name : public IPFunctionBase<T> { \
  public: \
    using Base = IPFunctionBase<T>; \
    TPFunction##name(TFunctionPtr<T> first, TFunctionPtr<T> second) : First_(first), Second_(second) {} \
    ~TPFunction##name() override = default; \
    Base::Domain Eval(Base::Domain arg) const override { return lambda; } \
    TagStream Tag() const override { return {{#name, 2}, {First_->Tag(), Second_->Tag()}}; }\
  private: \
    TFunctionPtr<T> First_; \
    TFunctionPtr<T> Second_; \
}; }

#define DECLARE_DOUBLE_ARG_FUNCTION(name, operation, lambda) \
    DECLARE_DOUBLE_ARG_FUNCTION_CLASS(name, lambda) \
    DECLARE_DOUBLE_ARG_OPERATION(operation, name)

#define DECLARE_SINGLE_ARG_FUNCTION(name, operation, lambda) \
    DECLARE_SINGLE_ARG_FUNCTION_CLASS(name, lambda) \
    DECLARE_SINGLE_ARG_OPERATION(operation, name)

#define DOUBLE_ARG_FUNCTION(name, func) DECLARE_DOUBLE_ARG_FUNCTION(name, name, func(First_->Eval(arg), Second->Eval(arg)))
#define SINGLE_ARG_FUNCTION(name, func) DECLARE_SINGLE_ARG_FUNCTION(name, name, func(Func_->Eval(arg)))

//#define REGISTER(name) SINGLE_ARG_FUNCTION(name, func)

#define EVAL_FOR_TYPE

#define REGISTER_FUNCTION(type, name) namespace PF { template<typename... Args> \
class TPFunction##name : public IPFunctionBase<type> { \
  public: \
    using Base = IPFunctionBase<type>; \
    TPFunction##name(Args... args) : parameters(std::make_tuple(args...)) {} \
    Base::Domain Eval(Base::Domain arg) const override { return Call##name(arg, parameters, std::index_sequence_for<Args...>{}); } \
    template<typename Tuple, std::size_t... Is> \
    static Base::Domain Call##name(Base::Domain arg, Tuple &&tuple, std::index_sequence<Is...>) { return name(EvalHelpers(std::get<Is>(tuple), arg)...); } \
    TagStream Tag() const override { return {{#name, 8}, {}}; } \
    ~TPFunction##name() override = default; \
  private: \
    std::tuple<Args...> parameters; \
};} \
template<typename... Args> \
PF::TFunctionPtr<type> name(Args...args) { return MakeShared<PF::TPFunction##name<Args...>, Args&&...>(std::forward<Args>(args)...); } \
