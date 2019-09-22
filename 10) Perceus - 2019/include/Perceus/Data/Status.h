#pragma once

#include "Inc.h"

namespace pcs
{
namespace Data
{

	// Takes an enum class as as a template argument. This is
	// used to store and retreive various status codes and their
	// corresponding string values.
    template<class E>
    class Status
    {
        E status;

	protected:
		// Static storage for the string values corresponding
		// to each of the enum values
    	static std::vector<std::string> &getValues()
		{
			static std::vector<std::string> values;

			return values;
		}

		// Set the current Status
        void setStatus(E s) { status = s; }

    public:
		Status() {}
		Status(E s) :
			status(s)
		{
			
		}

		// Returns the status
        E getStatus() const { return status; }

		std::string getStatusValue() const
		{
			return getValues()[(int)getStatus()];
		}
		
        // Strings for window status codes
        static std::string getStatusFromEnum(int enumVal) {
            return getValues()[enumVal];
        }
    };
}
}
