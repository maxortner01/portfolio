#pragma once

#include "../../DLL/dll.h"
#include "Event.h"

#include <vector>

namespace age
{
	struct KeyState
	{
		bool pressed = false;
		bool down = false;
	};

	class KeyEvent : public _Event
	{
		friend class Event;

		std::vector<KeyState> keyStates;

	protected:
		void setCallbacks() override;
		void updateKeyStates();

	public:
		enum
		{
			A = static_cast<int>('A'),
			B = static_cast<int>('B'),
			C = static_cast<int>('C'),
			D = static_cast<int>('D'),
			E = static_cast<int>('E'),
			F = static_cast<int>('F'),
			G = static_cast<int>('G'),
			H = static_cast<int>('H'),
			I = static_cast<int>('I'),
			J = static_cast<int>('J'),
			K = static_cast<int>('K'),
			L = static_cast<int>('L'),
			M = static_cast<int>('M'),
			N = static_cast<int>('N'),
			O = static_cast<int>('O'),
			P = static_cast<int>('P'),
			Q = static_cast<int>('Q'),
			R = static_cast<int>('R'),
			S = static_cast<int>('S'),
			T = static_cast<int>('T'),
			U = static_cast<int>('U'),
			V = static_cast<int>('V'),
			W = static_cast<int>('W'),
			X = static_cast<int>('X'),
			Y = static_cast<int>('Y'),
			Z = static_cast<int>('Z'),
			L_SHIFT = 340,
			SPACE = 32,
			ESCAPE = 256,
			LCTRL  = 341,
			TOTAL = 400
		} typedef Key;

		ANSEL_API KeyEvent(void* window);

		ANSEL_API bool isKeyDown(Key key);
		ANSEL_API bool isKeyPressed(Key key);
	};
}