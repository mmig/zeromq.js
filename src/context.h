/* Copyright (c) 2017-2019 Rolf Timmermans */
#pragma once

#include "binding.h"

#include <unordered_set>

namespace zmq {
extern Napi::ObjectReference GlobalContext;

class Context : public Napi::ObjectWrap<Context> {
public:
    static Napi::FunctionReference Constructor;
    static std::unordered_set<void*> ActivePtrs;
    static void Initialize(Napi::Env& env, Napi::Object& exports);

    explicit Context(const Napi::CallbackInfo& info);
    ~Context();

    Context(Context&&) = delete;
    Context& operator=(Context&&) = delete;

protected:
    template <typename T>
    inline Napi::Value GetCtxOpt(const Napi::CallbackInfo& info);

    template <typename T>
    inline void SetCtxOpt(const Napi::CallbackInfo& info);

private:
    void* context = nullptr;

    friend class Socket;
    friend class Observer;
    friend class Proxy;
};
}

static_assert(!std::is_copy_constructible<zmq::Context>::value, "not copyable");
static_assert(!std::is_move_constructible<zmq::Context>::value, "not movable");