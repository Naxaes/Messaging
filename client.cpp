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
#include <stdlib.h>  // exit

// The #pragma comment indicates to the linker what .lib file is needed.
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#pragma warning(pop)  // Enable warnings again.

#include "errors.cpp"


#define SENDING_BUFFER_SIZE   512
#define RECIEVING_BUFFER_SIZE 512

#define InvalidCodePath { fprintf(stderr, "Code path is invalid!\nFile: %sLine:%d\n", __FILE__, __LINE__); exit(1); }


#define ConstantString(literal) String(sizeof(literal)-1, literal)
struct String
{
	size_t count;
	char*  data;

	String(size_t count, char* data) : count(count), data(data) {}
};


size_t ReadUntilEnter(char* buffer, size_t capacity)
{
	int    character;
    size_t count = 0;

	while (true)
	{
		character = getchar();

		if (character == '\n' || character == EOF || count >= capacity)
			break;
		else
			buffer[count++] = (char)character;
    }

    return count;
}

int PromptYesOrNo(const char* prompt)
{
	while (true)
	{
		printf("%s", prompt);

		char buffer = 0;
		ReadUntilEnter(&buffer, 1);

		if (buffer == 'y')
		{
			return 1;
		}
		else if (buffer == 'n')
		{
			return 0;
		}
		else
		{
			printf("Invalid answer. Type 'y' or 'n', and then enter.\n");
		}
	}
}


DWORD WINAPI Send(void* parameter)
{
	SOCKET server_socket = *(SOCKET*)parameter;
	
	char message[SENDING_BUFFER_SIZE];

	String command_exit = ConstantString("/exit");
	String command_them = ConstantString("/them");
	

	while (true)
	{
	    size_t bytes_written = ReadUntilEnter(message, SENDING_BUFFER_SIZE);

	    // Continue if no message is to be sent.
		if (bytes_written == 0)
			continue;

		// Check if message is client command
		if (message[0] == '/')
		{
			if (bytes_written == command_exit.count && strncmp(message, command_exit.data, command_exit.count) == 0)
			{
				printf("[Exiting program...]\n");
				return 0;
			}
			else if (bytes_written == command_them.count && strncmp(message, command_them.data, command_them.count) == 0)
			{
				printf("[%4d]\n", server_socket);
			}
			else
			{
				printf("[Unknown command '%s']\n", message);
			}
		}
		else
		{
			// Send message.
			message[bytes_written++] = '\0';
			int bytes_sent = send(server_socket, message, (int)bytes_written, 0);

			// Error checking.
			if (bytes_sent == SOCKET_ERROR) 
			{
				int exit_code = WSAGetLastError();
				return (DWORD)exit_code;
			}
			else if (bytes_sent != (int)bytes_written)
			{
				fprintf(stderr, "Could only send %d bytes of %zu.\n", bytes_sent, bytes_written);
			}
		}
	}
}


DWORD WINAPI Receive(void* parameter)
{
	SOCKET server_socket = *(SOCKET*)parameter;
	
	char buffer[SENDING_BUFFER_SIZE];

	// Recieve messages from server.
	while (true)
	{
		int bytes_recieved = recv(server_socket, buffer, RECIEVING_BUFFER_SIZE, 0);

		if (bytes_recieved > 0) 
	    {
	        printf(">>> %s\n", buffer);
	    } 
	    else if (bytes_recieved == SOCKET_ERROR)
	    {
            int exit_code = WSAGetLastError();
            return (DWORD)exit_code;
	    }
	    else
	    {
	    	return 0;
	    }
	}
}


int ConnectToServer(const char* address, const char* port, addrinfo* hints, SOCKET* server_socket)
{
	int result;  // For error checking.

	// Resolve the server address and port
	struct addrinfo* address_info_start;
	result = getaddrinfo(address, port, hints, &address_info_start);
	if (result != 0) 
	{
		WSAGetAddressInfoError(result);
	    WSACleanup();
	    return result;
	}

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	struct addrinfo* address_info = address_info_start;
	*server_socket = INVALID_SOCKET;
	while (true)
	{
		// Create a SOCKET for connecting to server
		// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
		*server_socket = socket(address_info->ai_family, address_info->ai_socktype, address_info->ai_protocol);
		if (*server_socket == INVALID_SOCKET) 
		{
			result = WSAGetLastError();
			WSASocketError(result);
		    freeaddrinfo(address_info_start);
		    WSACleanup();
		    return result;
		}


		// Connect to server.
		// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-connect
		result = connect(*server_socket, address_info->ai_addr, (int)address_info->ai_addrlen);
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
			
		    closesocket(*server_socket);
		    *server_socket = INVALID_SOCKET;
		}
		else
		{
			break;
		}
	}

	freeaddrinfo(address_info_start);

	return 0;
}


DWORD StartClientThreads(SOCKET* server_socket, HANDLE* send_thread_handle, HANDLE* recieve_thread_handle)
{
	DWORD status = 0;

	*send_thread_handle = CreateThread(0, 0, Send, (void*)&server_socket, 0, NULL);
	if (*send_thread_handle == NULL)
	{
		status = GetLastError();
		fprintf(stderr, "Failed to create send thread for client %d. Error code %ld.\n", *server_socket, status);
		return status;
	}

	*recieve_thread_handle = CreateThread(0, 0, Receive, (void*)&server_socket, 0, NULL);
	if (*recieve_thread_handle == NULL)
	{
		status = GetLastError();
		fprintf(stderr, "Failed to create receive thread for client %d. Error code %ld.\n", *server_socket, status);
		return status;
	}

	return status;
}


// https://docs.microsoft.com/en-us/cpp/cpp/cdecl?view=vs-2019
int __cdecl main(int argc, char** argv) 
{
	const char* address = argc == 3 ? argv[1] : "127.0.0.1";
	const char* port    = argc == 3 ? argv[2] : "443";

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


	SOCKET server_socket;
	result = ConnectToServer(address, port, &hints, &server_socket);
	if (!result)
		return result;



	// ---- SEND AND RECEIVE ----
	/*
	time_t raw_time = time(NULL);
    struct tm info;
	gmtime_s(&info, &raw_time);
	char connection_message[200];
	strftime(connection_message, 200, "Requesting connection... %a, %d %b %Y %X GMT", &info);
	*/

	HANDLE send_thread_handle; 
	HANDLE recieve_thread_handle;
	DWORD  success = StartClientThreads(&server_socket, &send_thread_handle, &recieve_thread_handle);
	if (!success)
		return (int)success;


	// Wait for threads to exit.
	while (true)
	{
		DWORD wait_in_milliseconds = 200;

		HANDLE handles[] = {send_thread_handle, recieve_thread_handle};
		DWORD status = WaitForMultipleObjects(2, handles, FALSE, wait_in_milliseconds);

		if (status == WAIT_TIMEOUT)
		{
			continue;
		}
		else if (status == WAIT_FAILED)
		{
			fprintf(stderr, "WaitForMultipleObjects failed. Error code %ld.\n", GetLastError());
			break;
		}
		else if (status == WAIT_ABANDONED_0 || status == WAIT_ABANDONED_0 + 1)
		{
			InvalidCodePath;
		}
		else if (status == WAIT_OBJECT_0)
		{
			DWORD exit_code;
			status = (DWORD)GetExitCodeThread(send_thread_handle, &exit_code);
			if (status == 0)
			{
				fprintf(stderr, "Couldn't get send thread's exit status. Error code %ld.\n", GetLastError());
				break;
			}
			if (exit_code == 0)
			{
				break;
			}
			else
			{
				WSASendError((int)exit_code);

				if (PromptYesOrNo("Try to restart server connection? (y/n)\n"))
				{
					result = ConnectToServer(address, port, &hints, &server_socket);
					if (!result)
						return result;

					success = StartClientThreads(&server_socket, &send_thread_handle, &recieve_thread_handle);
					if (!success)
						return (int)success;
				}
			}
		}
		else if (status == WAIT_OBJECT_0 + 1)
		{
			DWORD exit_code;
			status = (DWORD)GetExitCodeThread(recieve_thread_handle, &exit_code);
			if (status == 0)
			{
				fprintf(stderr, "Couldn't get recieve thread's exit status. Error code %ld.\n", GetLastError());
				break;
			}
			if (exit_code == 0)
			{
				break;
			}
			else
			{
				WSARecvError((int)exit_code);

				if (PromptYesOrNo("Try to restart server connection? (y/n)\n"))
				{
					result = ConnectToServer(address, port, &hints, &server_socket);
					if (!result)
						return result;

					success = StartClientThreads(&server_socket, &send_thread_handle, &recieve_thread_handle);
					if (!success)
						return (int)success;
				}
			}
		}
		else
		{
			InvalidCodePath;
		}
	}

	


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
