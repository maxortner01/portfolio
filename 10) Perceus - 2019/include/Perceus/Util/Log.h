#pragma once

#include <iostream>
#include "spdlog/spdlog.h"

#include "Perceus/Data/Singleton.h"
#include "Perceus/Data/Inc.h"

namespace pcs
{
    class PERC_API Log : public Data::Singleton<Log>
    {
        spdlog::logger* coreLogger   = nullptr;
        spdlog::logger* clientLogger = nullptr;

    public:
        bool init();

		spdlog::logger* getCore()   { return coreLogger; }
        spdlog::logger* getClient() { return clientLogger; }
    };
}

// Core Logger Macros
#define PS_CORE_INFO(...)  ::pcs::Log::get().getCore()->info(__VA_ARGS__)
#define PS_CORE_WARN(...)  ::pcs::Log::get().getCore()->warn(__VA_ARGS__)
#define PS_CORE_ERROR(...) ::pcs::Log::get().getCore()->error(__VA_ARGS__)
#define PS_CORE_TRACE(...) ::pcs::Log::get().getCore()->trace(__VA_ARGS__)
#define PS_CORE_DEBUG(...) ::pcs::Log::get().getCore()->debug(__VA_ARGS__)

#define PS_CORE_SET_LEVEL(...) ::pcs::Log::get().getCore()->set_level(__VA_ARGS__)

// Client Logger Macros
#define PS_CLIENT_INFO(...)  ::pcs::Log::get().getClient()->info(__VA_ARGS__)
#define PS_CLIENT_WARN(...)  ::pcs::Log::get().getClient()->warn(__VA_ARGS__)
#define PS_CLIENT_ERROR(...) ::pcs::Log::get().getClient()->error(__VA_ARGS__)
#define PS_CLIENT_TRACE(...) ::pcs::Log::get().getClient()->trace(__VA_ARGS__)