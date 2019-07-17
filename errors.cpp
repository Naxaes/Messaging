void WSAStartupError(int code)
{
	fprintf(stderr, "[WSA Startup] Error code %d ", code);

	switch (code)
	{
		case WSASYSNOTREADY:
		{
			fprintf(stderr, "(WSASYSNOTREADY). The underlying network subsystem is not ready for network communication.\n");
		} break;
		case WSAVERNOTSUPPORTED:
		{
			fprintf(stderr, "(WSAVERNOTSUPPORTED). The version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation.\n");
		} break;
		case WSAEINPROGRESS:
		{
			fprintf(stderr, "(WSAEINPROGRESS). A blocking Windows Sockets 1.1 operation is in progress.\n");
		} break;
		case WSAEPROCLIM:
		{
			fprintf(stderr, "(WSAEPROCLIM). A limit on the number of tasks supported by the Windows Sockets implementation has been reached.\n");
		} break;
		case WSAEFAULT:
		{
			fprintf(stderr, "(WSAEFAULT). The lpWSAData parameter is not a valid pointer.\n");
		} break;
		default:
		{
			fprintf(stderr, "Unknown error.\n");
		}
	}
}

void WSAGetAddressInfoError(int code)
{
	fprintf(stderr, "[WSA GetAddressInfo] Error code %d ", code);

	switch (code)
	{
		case WSATRY_AGAIN:
		{
			fprintf(stderr, "(WSATRY_AGAIN). A temporary failure in name resolution occurred.\n");
		} break;
		case WSAEINVAL:
		{
			fprintf(stderr, "(WSAEINVAL). An invalid value was provided for the ai_flags member of the pHints parameter.\n");
		} break;
		case WSANO_RECOVERY:
		{
			fprintf(stderr, "(WSANO_RECOVERY). A nonrecoverable failure in name resolution occurred.\n");
		} break;
		case WSAEAFNOSUPPORT:
		{
			fprintf(stderr, "(WSAEAFNOSUPPORT). The ai_family member of the pHints parameter is not supported.\n");
		} break;
		case WSA_NOT_ENOUGH_MEMORY:
		{
			fprintf(stderr, "(WSA_NOT_ENOUGH_MEMORY). A memory allocation failure occurred.\n");
		} break;
		case WSAHOST_NOT_FOUND:
		{
			fprintf(stderr, "(WSAHOST_NOT_FOUND). The name does not resolve for the supplied parameters or the pNodeName and pServiceName parameters were not provided.\n");
		} break;
		case WSATYPE_NOT_FOUND:
		{
			fprintf(stderr, "(WSATYPE_NOT_FOUND). The pServiceName parameter is not supported for the specified ai_socktype member of the pHints parameter.\n");
		} break;
		case WSAESOCKTNOSUPPORT:
		{
			fprintf(stderr, "(WSAESOCKTNOSUPPORT). The ai_socktype member of the pHints parameter is not supported.\n");
		} break;
		default:
		{
			fprintf(stderr, "Unknown error.\n");
		}
	}
}

void WSASocketError(int code)
{
	fprintf(stderr, "[WSA Socket] Error code %d ", code);

	switch (code)
	{
		case WSANOTINITIALISED:
		{
			fprintf(stderr, "(WSANOTINITIALISED). A successful WSAStartup call must occur before using this function.\n");
		} break;
		case WSAENETDOWN:
		{
			fprintf(stderr, "(WSAENETDOWN). The network subsystem or the associated service provider has failed.\n");
		} break;
		case WSAEAFNOSUPPORT:
		{
			fprintf(stderr, "(WSAEAFNOSUPPORT). The specified address family is not supported. For example, an application tried to create a socket for the AF_IRDA address family but an infrared adapter and device driver is not installed on the local computer.\n");
		} break;
		case WSAEINPROGRESS:
		{
			fprintf(stderr, "(WSAEINPROGRESS). A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.\n");
		} break;
		case WSAEMFILE:
		{
			fprintf(stderr, "(WSAEMFILE). No more socket descriptors are available.\n");
		} break;
		case WSAEINVAL:
		{
			fprintf(stderr, "(WSAEINVAL). An invalid argument was supplied. This error is returned if the af parameter is set to AF_UNSPEC and the type and protocol parameter are unspecified.\n");
		} break;
		case WSAEINVALIDPROVIDER:
		{
			fprintf(stderr, "(WSAEINVALIDPROVIDER). The service provider returned a version other than 2.2.\n");
		} break;
		case WSAEINVALIDPROCTABLE:
		{
			fprintf(stderr, "(WSAEINVALIDPROCTABLE). The service provider returned an invalid or incomplete procedure table to the WSPStartup.\n");
		} break;
		case WSAENOBUFS:
		{
			fprintf(stderr, "(WSAENOBUFS). No buffer space is available. The socket cannot be created.\n");
		} break;
		case WSAEPROTONOSUPPORT:
		{
			fprintf(stderr, "(WSAEPROTONOSUPPORT). The specified protocol is not supported.\n");
		} break;
		case WSAEPROTOTYPE:
		{
			fprintf(stderr, "(WSAEPROTOTYPE). The specified protocol is the wrong type for this socket.\n");
		} break;
		case WSAEPROVIDERFAILEDINIT:
		{
			fprintf(stderr, "(WSAEPROVIDERFAILEDINIT). The service provider failed to initialize. This error is returned if a layered service provider (LSP) or namespace provider was improperly installed or the provider fails to operate correctly.\n");
		} break;
		case WSAESOCKTNOSUPPORT:
		{
			fprintf(stderr, "(WSAESOCKTNOSUPPORT). The specified socket type is not supported in this address family.\n");
		} break;
		default:
		{
			fprintf(stderr, "Unknown error.\n");
		}
	}
}


void WSAConnectError(int code)
{
	fprintf(stderr, "[WSA Connect] Error code %d ", code);

	switch (code)
	{
		case WSANOTINITIALISED:
		{
			fprintf(stderr, "(WSANOTINITIALISED). A successful WSAStartup call must occur before using this function.\n");
		} break;
		case WSAENETDOWN:
		{
			fprintf(stderr, "(WSAENETDOWN). The network subsystem has failed.\n");
		} break;
		case WSAEADDRINUSE:
		{
			fprintf(stderr, "(WSAEADDRINUSE). The socket's local address is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs when executing bind, but could be delayed until the connect function if the bind was to a wildcard address (INADDR_ANY or in6addr_any) for the local IP address. A specific address needs to be implicitly bound by the connect function.\n");
		} break;
		case WSAEINTR:
		{
			fprintf(stderr, "(WSAEINTR). The blocking Windows Socket 1.1 call was canceled through WSACancelBlockingCall.\n");
		} break;
		case WSAEINPROGRESS:
		{
			fprintf(stderr, "(WSAEINPROGRESS). A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.\n");
		} break;
		case WSAEALREADY:
		{
			fprintf(stderr, "(WSAEALREADY). A nonblocking connect call is in progress on the specified socket.\nNote: In order to preserve backward compatibility, this error is reported as WSAEINVAL to Windows Sockets 1.1 applications that link to either Winsock.dll or Wsock32.dll.\n");
		} break;
		case WSAEADDRNOTAVAIL:
		{
			fprintf(stderr, "(WSAEADDRNOTAVAIL). The remote address is not a valid address (such as INADDR_ANY or in6addr_any) .\n");
		} break;
		case WSAEAFNOSUPPORT:
		{
			fprintf(stderr, "(WSAEAFNOSUPPORT). Addresses in the specified family cannot be used with this socket.\n");
		} break;
		case WSAECONNREFUSED:
		{
			fprintf(stderr, "(WSAECONNREFUSED). The attempt to connect was forcefully rejected.\n");
		} break;
		case WSAEFAULT:
		{
			fprintf(stderr, "(WSAEFAULT). The sockaddr structure pointed to by the name contains incorrect address format for the associated address family or the namelen parameter is too small. This error is also returned if the sockaddr structure pointed to by the name parameter with a length specified in the namelen parameter is not in a valid part of the user address space.\n");
		} break;
		case WSAEINVAL:
		{
			fprintf(stderr, "(WSAEINVAL). The parameter s is a listening socket.\n");
		} break;
		case WSAEISCONN:
		{
			fprintf(stderr, "(WSAEISCONN). The socket is already connected (connection-oriented sockets only).\n");
		} break;
		case WSAENETUNREACH:
		{
			fprintf(stderr, "(WSAENETUNREACH). The network cannot be reached from this host at this time.\n");
		} break;
		case WSAEHOSTUNREACH:
		{
			fprintf(stderr, "(WSAEHOSTUNREACH). A socket operation was attempted to an unreachable host.\n");
		} break;
		case WSAENOBUFS:
		{
			fprintf(stderr, "(WSAENOBUFS). Note  No buffer space is available. The socket cannot be connected.\n");
		} break;
		case WSAENOTSOCK:
		{
			fprintf(stderr, "(WSAENOTSOCK). The descriptor specified in the s parameter is not a socket.\n");
		} break;
		case WSAETIMEDOUT:
		{
			fprintf(stderr, "(WSAETIMEDOUT). An attempt to connect timed out without establishing a connection.\n");
		} break;
		case WSAEWOULDBLOCK:
		{
			fprintf(stderr, "(WSAEWOULDBLOCK). The socket is marked as nonblocking and the connection cannot be completed immediately.\n");
		} break;
		case WSAEACCES:
		{
			fprintf(stderr, "(WSAEACCES). An attempt to connect a datagram socket to broadcast address failed because setsockopt option SO_BROADCAST is not enabled.\n");
		} break;
		default:
		{
			fprintf(stderr, "Unknown error.\n");
		}
	}
}

void WSASendError(int code)
{
	fprintf(stderr, "[WSA Send] Error code %d ", code);

	switch (code)
	{
		case WSANOTINITIALISED:
		{
			fprintf(stderr, "(WSANOTINITIALISED). A successful WSAStartup call must occur before using this function.\n");
		} break;
		case WSAENETDOWN:
		{
			fprintf(stderr, "(WSAENETDOWN). The network subsystem has failed.\n");
		} break;
		case WSAEACCES:
		{
			fprintf(stderr, "(WSAEACCES). The requested address is a broadcast address, but the appropriate flag was not set. Call setsockopt with the SO_BROADCAST socket option to enable use of the broadcast address.\n");
		} break;
		case WSAEINTR:
		{
			fprintf(stderr, "(WSAEINTR). A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall.\n");
		} break;
		case WSAEINPROGRESS:
		{
			fprintf(stderr, "(WSAEINPROGRESS). A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.\n");
		} break;
		case WSAEFAULT:
		{
			fprintf(stderr, "(WSAEFAULT). The buf parameter is not completely contained in a valid part of the user address space.\n");
		} break;
		case WSAENETRESET:
		{
			fprintf(stderr, "(WSAENETRESET). The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress.\n");
		} break;
		case WSAENOBUFS:
		{
			fprintf(stderr, "(WSAENOBUFS). No buffer space is available.\n");
		} break;
		case WSAENOTCONN:
		{
			fprintf(stderr, "(WSAENOTCONN). The socket is not connected.\n");
		} break;
		case WSAENOTSOCK:
		{
			fprintf(stderr, "(WSAENOTSOCK). The descriptor is not a socket.\n");
		} break;
		case WSAEOPNOTSUPP:
		{
			fprintf(stderr, "(WSAEOPNOTSUPP). MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only receive operations.\n");
		} break;
		case WSAESHUTDOWN:
		{
			fprintf(stderr, "(WSAESHUTDOWN). The socket has been shut down; it is not possible to send on a socket after shutdown has been invoked with how set to SD_SEND or SD_BOTH.\n");
		} break;
		case WSAEWOULDBLOCK:
		{
			fprintf(stderr, "(WSAEWOULDBLOCK). The socket is marked as nonblocking and the requested operation would block.\n");
		} break;
		case WSAEMSGSIZE:
		{
			fprintf(stderr, "(WSAEMSGSIZE). The socket is message oriented, and the message is larger than the maximum supported by the underlying transport.\n");
		} break;
		case WSAEHOSTUNREACH:
		{
			fprintf(stderr, "(WSAEHOSTUNREACH). The remote host cannot be reached from this host at this time.\n");
		} break;
		case WSAEINVAL:
		{
			fprintf(stderr, "(WSAEINVAL). The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled.\n");
		} break;
		case WSAECONNABORTED:
		{
			fprintf(stderr, "(WSAECONNABORTED). The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable.\n");
		} break;
		case WSAECONNRESET:
		{
			fprintf(stderr, "(WSAECONNRESET). The virtual circuit was reset by the remote side executing a hard or abortive close. For UDP sockets, the remote host was unable to deliver a previously sent UDP datagram and responded with a 'Port Unreachable' ICMP packet. The application should close the socket as it is no longer usable.\n");
		} break;
		case WSAETIMEDOUT:
		{
			fprintf(stderr, "(WSAETIMEDOUT). The connection has been dropped, because of a network failure or because the system on the other end went down without notice.\n");
		} break;
		default:
		{
			fprintf(stderr, "Unknown error.\n");
		}
	}
}

void WSARecvError(int code)
{
	fprintf(stderr, "[WSA Recv] Error code %d ", code);

	switch (code)
	{
		case WSANOTINITIALISED:
		{
			fprintf(stderr, "(WSANOTINITIALISED). A successful WSAStartup call must occur before using this function.\n");
		} break;
		case WSAENETDOWN:
		{
			fprintf(stderr, "(WSAENETDOWN). The network subsystem has failed.\n");
		} break;
		case WSAEFAULT:
		{
			fprintf(stderr, "(WSAEFAULT). The buf parameter is not completely contained in a valid part of the user address space.\n");
		} break;
		case WSAENOTCONN:
		{
			fprintf(stderr, "(WSAENOTCONN). The socket is not connected.\n");
		} break;
		case WSAEINTR:
		{
			fprintf(stderr, "(WSAEINTR). The (blocking) call was canceled through WSACancelBlockingCall.\n");
		} break;
		case WSAEINPROGRESS:
		{
			fprintf(stderr, "(WSAEINPROGRESS). A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.\n");
		} break;
		case WSAENETRESET:
		{
			fprintf(stderr, "(WSAENETRESET). For a connection-oriented socket, this error indicates that the connection has been broken due to keep-alive activity that detected a failure while the operation was in progress. For a datagram socket, this error indicates that the time to live has expired.\n");
		} break;
		case WSAENOTSOCK:
		{
			fprintf(stderr, "(WSAENOTSOCK). The descriptor is not a socket.\n");
		} break;
		case WSAEOPNOTSUPP:
		{
			fprintf(stderr, "(WSAEOPNOTSUPP). MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only send operations.\n");
		} break;
		case WSAESHUTDOWN:
		{
			fprintf(stderr, "(WSAESHUTDOWN). The socket has been shut down; it is not possible to receive on a socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH.\n");
		} break;
		case WSAEWOULDBLOCK:
		{
			fprintf(stderr, "(WSAEWOULDBLOCK). The socket is marked as nonblocking and the receive operation would block.\n");
		} break;
		case WSAEMSGSIZE:
		{
			fprintf(stderr, "(WSAEMSGSIZE). The message was too large to fit into the specified buffer and was truncated.\n");
		} break;
		case WSAEINVAL:
		{
			fprintf(stderr, "(WSAEINVAL). The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled or (for byte stream sockets only) len was zero or negative.\n");
		} break;
		case WSAECONNABORTED:
		{
			fprintf(stderr, "(WSAECONNABORTED). The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable.\n");
		} break;
		case WSAETIMEDOUT:
		{
			fprintf(stderr, "(WSAETIMEDOUT). The connection has been dropped because of a network failure or because the peer system failed to respond.\n");
		} break;
		case WSAECONNRESET:
		{
			fprintf(stderr, "(WSAECONNRESET). The virtual circuit was reset by the remote side executing a hard or abortive close. The application should close the socket as it is no longer usable. On a UDP-datagram socket, this error would indicate that a previous send operation resulted in an ICMP 'Port Unreachable' message.\n");
		} break;
		default:
		{
			fprintf(stderr, "Unknown error.\n");
		}
	}
}

void WSAShutdownError(int code)
{
	fprintf(stderr, "[WSA Shutdown] Error code %d ", code);

	switch (code)
	{
		case WSAECONNABORTED:
		{
			fprintf(stderr, "(WSAECONNABORTED). The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable.\nThis error applies only to a connection-oriented socket. This error applies only to a connection-oriented socket.\n");	
		} break;
		case WSAECONNRESET:
		{
			fprintf(stderr, "(WSAECONNRESET). The virtual circuit was reset by the remote side executing a hard or abortive close. The application should close the socket as it is no longer usable.\nThis error applies only to a connection-oriented socket. This error applies only to a connection-oriented socket.\n");	
		} break;
		case WSAEINPROGRESS:
		{
			fprintf(stderr, "(WSAEINPROGRESS). A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.\n");	
		} break;
		case WSAEINVAL:
		{
			fprintf(stderr, "(WSAEINVAL). The how parameter is not valid, or is not consistent with the socket type. For example, SD_SEND is used with a UNI_RECV socket type.\n");	
		} break;
		case WSAENETDOWN:
		{
			fprintf(stderr, "(WSAENETDOWN). The network subsystem has failed.\n");	
		} break;
		case WSAENOTCONN:
		{
			fprintf(stderr, "(WSAENOTCONN). The socket is not connected. This error applies only to a connection-oriented socket.\n");	
		} break;
		case WSAENOTSOCK:
		{
			fprintf(stderr, "(WSAENOTSOCK). Note  The descriptor is not a socket.\n");	
		} break;
		case WSANOTINITIALISED:
		{
			fprintf(stderr, "(WSANOTINITIALISED). A successful WSAStartup call must occur before using this function.\n");	
		} break;
		default:
		{
			fprintf(stderr, "Unknown error.\n");
		}
	}
}


void WSABindError(int code)
{
	fprintf(stderr, "[WSA Bind] Error code %d ", code);

	switch (code)
	{
		case WSANOTINITIALISED:
		{
			fprintf(stderr, "(WSANOTINITIALISED). Note  A successful WSAStartup call must occur before using this function.\n");
		} break; 
		case WSAENETDOWN:
		{
			fprintf(stderr, "(WSAENETDOWN). The network subsystem has failed.\n");
		} break;
		case WSAEACCES:
		{
			fprintf(stderr, "(WSAEACCES). An attempt was made to access a socket in a way forbidden by its access permissions.\nThis error is returned if the descriptor in the s parameter is not a socket.\n");
		} break;
		case WSAEADDRINUSE:
		{
			fprintf(stderr, "(WSAEADDRINUSE). Only one usage of each socket address (protocol/network address/port) is normally permitted.\nThis error is returned if the descriptor in the s parameter is not a socket.\n");
		} break;
		case WSAEADDRNOTAVAIL:
		{
			fprintf(stderr, "(WSAEADDRNOTAVAIL). The requested address is not valid in its context.\nThis error is returned if the descriptor in the s parameter is not a socket.\n");
		} break;
		case WSAEFAULT:
		{
			fprintf(stderr, "(WSAEFAULT). The system detected an invalid pointer address in attempting to use a pointer argument in a call.\nThis error is returned if the descriptor in the s parameter is not a socket.\n");
		} break;
		case WSAEINPROGRESS:
		{
			fprintf(stderr, "(WSAEINPROGRESS). A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.\n");
		}
		case WSAEINVAL:
		{
			fprintf(stderr, "(WSAEINVAL). An invalid argument was supplied.\nThis error is returned if the descriptor in the s parameter is not a socket.\n");
		} break;
		case WSAENOBUFS:
		{
			fprintf(stderr, "(WSAENOBUFS). An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.\nThis error is returned if the descriptor in the s parameter is not a socket.\n");
		} break;
		case WSAENOTSOCK:
		{
			fprintf(stderr, "(WSAENOTSOCK). An operation was attempted on something that is not a socket.\nThis error is returned if the descriptor in the s parameter is not a socket.\n;");
		} break;
		default:
		{
			fprintf(stderr, "Unknown error.\n");
		}
	}
}


void WSAListenError(int code)
{
	fprintf(stderr, "[WSA Listen] Error code %d ", code);

	switch (code)
	{
		case WSANOTINITIALISED:
		{
			fprintf(stderr, "(WSANOTINITIALISED). A successful WSAStartup call must occur before using this function.\n");
		} break;
		case WSAENETDOWN:
		{
			fprintf(stderr, "(WSAENETDOWN). The network subsystem has failed.\n");
		} break;
		case WSAEADDRINUSE:
		{
			fprintf(stderr, "(WSAEADDRINUSE). The socket's local address is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs during execution of the bind function, but could be delayed until this function if the bind was to a partially wildcard address (involving ADDR_ANY) and if a specific address needs to be committed at the time of this function.\n");
		} break;
		case WSAEINPROGRESS:
		{
			fprintf(stderr, "(WSAEINPROGRESS). A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.\n");
		} break;
		case WSAEINVAL:
		{
			fprintf(stderr, "(WSAEINVAL). The socket has not been bound with bind.\n");
		} break;
		case WSAEISCONN:
		{
			fprintf(stderr, "(WSAEISCONN). The socket is already connected.\n");
		} break;
		case WSAEMFILE:
		{
			fprintf(stderr, "(WSAEMFILE). No more socket descriptors are available.\n");
		} break;
		case WSAENOBUFS:
		{
			fprintf(stderr, "(WSAENOBUFS). No buffer space is available.\n");
		} break;
		case WSAENOTSOCK:
		{
			fprintf(stderr, "(WSAENOTSOCK). The descriptor is not a socket.\n");
		} break;
		case WSAEOPNOTSUPP:
		{
			fprintf(stderr, "(WSAEOPNOTSUPP). The referenced socket is not of a type that supports the listen operation.\n");
		} break;
		default:
		{
			fprintf(stderr, "Unknown error.\n");
		}
	}
}


void WSAAcceptError(int code)
{
	fprintf(stderr, "[WSA Accept] Error code %d ", code);

	switch (code)
	{
		case WSANOTINITIALISED:
		{
			fprintf(stderr, "(WSANOTINITIALISED). A successful WSAStartup call must occur before using this function.\n");
		} break;
		case WSAECONNRESET:
		{
			fprintf(stderr, "(WSAECONNRESET). An incoming connection was indicated, but was subsequently terminated by the remote peer prior to accepting the call.\n");
		} break;
		case WSAEFAULT:
		{
			fprintf(stderr, "(WSAEFAULT). The addrlen parameter is too small or addr is not a valid part of the user address space.\n");
		} break;
		case WSAEINTR:
		{
			fprintf(stderr, "(WSAEINTR). A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall.\n");
		} break;
		case WSAEINVAL:
		{
			fprintf(stderr, "(WSAEINVAL). The listen function was not invoked prior to accept.\n");
		} break;
		case WSAEINPROGRESS:
		{
			fprintf(stderr, "(WSAEINPROGRESS). A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.\n");
		} break;
		case WSAEMFILE:
		{
			fprintf(stderr, "(WSAEMFILE). The queue is nonempty upon entry to accept and there are no descriptors available.\n");
		} break;
		case WSAENETDOWN:
		{
			fprintf(stderr, "(WSAENETDOWN). The network subsystem has failed.\n");
		} break;
		case WSAENOBUFS:
		{
			fprintf(stderr, "(WSAENOBUFS). No buffer space is available.\n");
		} break;
		case WSAENOTSOCK:
		{
			fprintf(stderr, "(WSAENOTSOCK). The descriptor is not a socket.\n");
		} break;
		case WSAEOPNOTSUPP:
		{
			fprintf(stderr, "(WSAEOPNOTSUPP). The referenced socket is not a type that supports connection-oriented service.\n");
		} break;
		case WSAEWOULDBLOCK:
		{
			fprintf(stderr, "(WSAEWOULDBLOCK). The socket is marked as nonblocking and no connections are present to be accepted.\n");
		} break;
		default:
		{
			fprintf(stderr, "Unknown error.\n");
		}
	}
}
