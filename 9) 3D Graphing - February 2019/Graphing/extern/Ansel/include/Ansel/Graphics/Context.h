#pragma once

#include "GLObjects.h"

namespace age
{
	class Context
	{
		ContextSettings _settings;
		void* context;

		bool destroyed = false;

		ANSEL_API static Context* current;

	public:
		ANSEL_API Context(ContextSettings settings = ContextSettings());
		ANSEL_API virtual ~Context();

		ANSEL_API void destroy();
		ANSEL_API void makeCurrent();
		ANSEL_API void makeSettings();

		ANSEL_API static Context &getCurrentContext();

		ANSEL_API void close();

		void* getContext() const { return context; }

		ContextSettings &getSettings() { return _settings; }
		bool isDestroyed() const { return destroyed; }
	};
}