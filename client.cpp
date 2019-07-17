/*

---- Server ----
	* Initialize Winsock.
	* Create a socket.
	* Bind the socket.
	* Listen on the socket for a client.
	* Accept a connection from a client.
	* Receive and send data.
	* Disconnect.

----- Client ----
	* Initialize Winsock.
	* Create a socket.
	* Connect to the server.
	* Send and receive data.
	* Disconnect.

*/

// The Winsock2.h header file internally includes core elements from the Windows.h header file.
// Therefore, the includes should be preceded with the #define WIN32_LEAN_AND_MEAN macro.
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#pragma warning(push, 0)  // Disable warnings from windows headers.

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#include <stdio.h>
#include <time.h>

// The #pragma comment indicates to the linker what .lib file is needed.
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#pragma warning(pop)  // Enable warnings again.


#include "errors.cpp"


DWORD WINAPI Send(void* parameter)
{
	#define DEFAULT_BUFFER_SIZE 512
	char message[DEFAULT_BUFFER_SIZE];

	SOCKET server_socket = *(SOCKET*)parameter;

	// Receive data until the server closes the connection
	while (true) 
	{
	    int character;
	    int index = 0;
		while ((character = getchar()) != '\n' && character != EOF)
		{
		    message[index++] = (char)character;
	    }
	    message[index++] = '\0';

		int result = send(server_socket, message, index, 0);
		if (result == SOCKET_ERROR) 
		{
			result = WSAGetLastError();
			WSASendError(result);
			closesocket(server_socket);
		    WSACleanup();
		    return (DWORD)result;
		}
	}

	return 0;

	#undef DEFAULT_BUFFER_SIZE
}

DWORD WINAPI Receive(void* parameter)
{
	#define DEFAULT_BUFFER_SIZE 512
	char buffer[DEFAULT_BUFFER_SIZE];

	SOCKET server_socket = *(SOCKET*)parameter;

	int bytes_recieved = 0;
	do {
	    bytes_recieved = recv(server_socket, buffer, DEFAULT_BUFFER_SIZE, 0);
	    if (bytes_recieved > 0) 
	    {
	        printf(">>> %s\n", buffer);
	    } 
	    else 
	    {
            int error_code = WSAGetLastError();
			WSARecvError(error_code);
            closesocket(server_socket);
            return (DWORD)error_code;
	    }

	} while (bytes_recieved > 0);


	int result = shutdown(server_socket, SD_BOTH);
	if (result == SOCKET_ERROR) 
	{
        int error_code = WSAGetLastError();
		WSAShutdownError(error_code);
	    closesocket(server_socket);
	    return (DWORD)error_code;
	}

	closesocket(server_socket);

	return 0;

	#undef DEFAULT_BUFFER_SIZE
}


// https://docs.microsoft.com/en-us/cpp/cpp/cdecl?view=vs-2019
int __cdecl main(int argc, char** argv) 
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: <IP-address> <port>\n");
		return 1;
	}

	// The WSADATA structure contains information about the Windows Sockets implementation.
	// https://docs.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-wsadata
	WSADATA socket_data;
	int result;  // For error checking.

	// Initialize Winsock
	// https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
	WORD version_required = MAKEWORD(2, 2);
	result = WSAStartup(version_required, &socket_data);
	if (result != 0) 
	{
	    WSAStartupError(result);
	    return result;
	}


	// Create socket.
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;


	// Resolve the server address and port
	const char* port = argv[2];
	const char* numeric_host_address = argv[1];
	struct addrinfo* address_info_start;
	result = getaddrinfo(numeric_host_address, port, &hints, &address_info_start);
	if (result != 0) 
	{
		WSAGetAddressInfoError(result);
	    WSACleanup();
	    return result;
	}


	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	struct addrinfo* address_info = address_info_start;
	SOCKET server_socket = INVALID_SOCKET;
	while (true)
	{
		// Create a SOCKET for connecting to server
		// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
		server_socket = socket(address_info->ai_family, address_info->ai_socktype, address_info->ai_protocol);
		if (server_socket == INVALID_SOCKET) 
		{
			result = WSAGetLastError();
			WSASocketError(result);
		    freeaddrinfo(address_info_start);
		    WSACleanup();
		    return result;
		}


		// Connect to server.
		// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-connect
		result = connect(server_socket, address_info->ai_addr, (int)address_info->ai_addrlen);
		if (result == SOCKET_ERROR) 
		{
		    address_info = address_info->ai_next;

			if (address_info == NULL)
			{
				result = WSAGetLastError();
			    WSAConnectError(result);
			    WSACleanup();
			    return result;
			}
			
		    closesocket(server_socket);
		    server_socket = INVALID_SOCKET;
		}
		else
		{
			break;
		}
	}

	freeaddrinfo(address_info_start);



	// ---- SEND AND RECEIVE ----
	/*
	time_t raw_time = time(NULL);
    struct tm info;
	gmtime_s(&info, &raw_time);
	char connection_message[200];
	strftime(connection_message, 200, "Requesting connection... %a, %d %b %Y %X GMT", &info);
	*/

	HANDLE send_thread_handle = CreateThread(0, 0, Send, (void*)&server_socket, 0, NULL);
	if (send_thread_handle == NULL)
	{
		fprintf(stderr, "Failed to create thread for client %d. Error code %ld.\n", server_socket, GetLastError());
	}

	HANDLE recieve_thread_handle = CreateThread(0, 0, Receive, (void*)&server_socket, 0, NULL);
	if (recieve_thread_handle == NULL)
	{
		fprintf(stderr, "Failed to create thread for client %d. Error code %ld.\n", server_socket, GetLastError());
	}

	WaitForSingleObject(send_thread_handle,    INFINITE);
	WaitForSingleObject(recieve_thread_handle, INFINITE);
	

	// Shutdown the send half of the connection since no more data will be sent
	result = shutdown(server_socket, SD_SEND);
	if (result == SOCKET_ERROR) 
	{
		result = WSAGetLastError();
	    WSAShutdownError(result);
	    closesocket(server_socket);
	    WSACleanup();
	    return result;
	}

	// Cleanup
	closesocket(server_socket);
	WSACleanup();

	return 0;
}
