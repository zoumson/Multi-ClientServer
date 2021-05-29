
/*
* License plate detection
* See COPYRIGHT file at the top of the source tree.
*
* This product includes software developed by the
* STARGUE Project (http://www.stargue.org/).
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the STARGUE License Statement and
* the GNU General Public License along with this program. If not,
* see <http://www.lsstcorp.org/LegalNotices/>.
*/

/**
 * @file Clock.h
 *
 * @brief Provide current time
 *
 * @author Adama Zouma
 * 
 * @Contact: stargue49@gmail.com
 *
 */


#ifndef CLOCK_H
#define CLOCK_H

#include <string>
#include <stdio.h>
#include <time.h>

/**
 * Implementation of a clock
 * This clock provides current time in a string format.
 * the time format is hh:MM:SS
 *
 */
class Clock
{
        /* ============================================================================
        * Data Memeber Declaration
        * ============================================================================
        */
        // None


    
public:

        /* ============================================================================
        * Member Function Declaration
        * ============================================================================
        */

        /**
        * \brief Provide current time
        *
        * \param #void
        *      *
        * \return #string
        * 
        */
        std::string currentDateTime(void);

         /**
        * \brief Destructor
        *
        * 
        */       
        virtual ~Clock();
};
#endif // CLOCK_H

