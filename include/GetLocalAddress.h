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
 * @file GetLocalAddress.h.h
 *
 * @brief Get the local IPv4 address 
 *
 * @author Adama Zouma
 * 
 * @Contact: stargue49@gmail.com
 *
 */
#include <iostream>
#include <iostream>     ///< cout
#include <cstring>      ///< memset
#include <errno.h>      ///< errno
#include <sys/socket.h> ///< socket
#include <netinet/in.h> ///< sockaddr_in
#include <arpa/inet.h>  ///< getsockname
#include <unistd.h>     ///< close
#include<string.h>
#include<netinet/in.h> //#define INET_ADDRSTRLEN 16 #define INET6_ADDRSTRLEN 46
#include <cstring>      ///< memset

namespace za{
/* ============================================================================
 * Function Declaration
 * ============================================================================
 */

/**
 * \brief Get local IPv4 address.
 *
 * \details Send a request to google DNS erver, then use the retunned 
 * response to fetch the local IP address
 *
 * \param myIP [in] buffer passed by reference to store the IP, type is string
 *
* \return #0 if create successfully
 * \return Error code if return value < 0
 * 
 * 
 */
int getLocalAddress(std::string& myIP);
}