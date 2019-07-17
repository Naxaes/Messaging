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


static HANDLE mutex_lock;
static volatile SOCKET clients[256];
static volatile unsigned current_client_index;


DWORD WINAPI HandleClient(void* parameter)
{
	#define DEFAULT_BUFFER_SIZE 512

	SOCKET client_socket = *(SOCKET*)parameter;
	char buffer[DEFAULT_BUFFER_SIZE];
	char log_in_code[] = "1234";
	
	char client_id[7];  // [1234]\0 == 7 characters
	size_t client_id_size = 7;
	if (sprintf_s(client_id, client_id_size, "[%4d]", client_socket) <= 0)
	{
		printf("Couldn't format client id.\n");
		return 1;
	}

	printf("Accepting client %d.\n", client_socket);

	// Log in
	bool logged_in = false;
	while (!logged_in)
	{
		int bytes_recieved = recv(client_socket, buffer, DEFAULT_BUFFER_SIZE, 0);
	    if (bytes_recieved > 0) 
	    {
	        printf("[Client %d : Code %s]\n", client_socket, buffer);

	        size_t message_size = 0;
	        if (strncmp(buffer, log_in_code, sizeof(log_in_code)) == 0)
	        {
	        	char message[] = "Logged in!";
	        	message_size = sizeof(message);
	        	strncpy_s(buffer, message, message_size);
	        	logged_in = true;
	        }
	        else
	        {
	        	char message[] = "Invalid pin";
	        	message_size = sizeof(message);
	        	strncpy_s(buffer, message, message_size);
	        }

	        int bytes_sent = send(client_socket, buffer, (int)message_size, 0);
	        if (bytes_sent == SOCKET_ERROR) 
	        {
	            int error_code = WSAGetLastError();
				WSASendError(error_code);
	            closesocket(client_socket);
	            return (DWORD)error_code;
	        }
	    }
	   	else if (bytes_recieved == 0)
	    {
	    	printf("[%4d logging out...]\n", client_socket);
	    	break;  // Use goto here?
	    }
	    else if (bytes_recieved == SOCKET_ERROR)
	    {
            int error_code = WSAGetLastError();
			WSARecvError(error_code);
            closesocket(client_socket);
            return (DWORD)error_code;
	    }
	    else
	    {
	    	// Should never happen.
	    	printf("INVALID CODE PATH [%d]\n", bytes_recieved);
	    }
	}

	// TODO(ted): Don't know what the 'wait_result' is.
	while (true)
	{
	    DWORD wait_result = WaitForSingleObject(mutex_lock, INFINITE);
	    if (wait_result == WAIT_OBJECT_0)
	    {
	   		clients[current_client_index] = client_socket;
			InterlockedExchangeAdd(&current_client_index, 1);
			ReleaseMutex(mutex_lock);  // TODO(ted): Handle error.
			break;
	    }
	}

	
	while (true)
	{
	    int bytes_recieved = recv(client_socket, buffer, DEFAULT_BUFFER_SIZE, 0);
	    if (bytes_recieved > 0) 
	    {
	        char exit_command[] = "exit";
	        if (strncmp(buffer, exit_command, sizeof(exit_command)) == 0)
	        {
	        	printf("[%4d logging out...]\n", client_socket);
	        	break;
	        }
	        else
	        {
	        	printf("[%4d] %s\n", client_socket, buffer);


	        	// TODO(ted): FIX ALL THESE COPIES!


				while (true)
				{
				    DWORD wait_result = WaitForSingleObject(mutex_lock, INFINITE);
				    if (wait_result == WAIT_OBJECT_0)
				    {
				    	for (unsigned i = 0; i < current_client_index; ++i)
				    	{
				    		if (clients[i] == client_socket)
				    		{
				    			continue;
				    		}

				    		int bytes_sent = send(clients[i], buffer, bytes_recieved, 0);
					        if (bytes_sent == SOCKET_ERROR) 
					        {
					            int error_code = WSAGetLastError();
								WSASendError(error_code);
					        }
				    	}
				    	ReleaseMutex(mutex_lock);  // TODO(ted): Handle error.
				    	break;
				    }
				}

	        }
	    }
	    else if (bytes_recieved == 0)
	    {
	    	printf("[%4d logging out...]\n", client_socket);
	    	break;
	    }
	    else if (bytes_recieved == SOCKET_ERROR)
	    {
            int error_code = WSAGetLastError();
			WSARecvError(error_code);
            closesocket(client_socket);
            return (DWORD)error_code;
	    }
	    else
	    {
	    	// Should never happen.
	    	printf("INVALID CODE PATH [%d]\n", bytes_recieved);
	    }
	}


	int result = shutdown(client_socket, SD_BOTH);
	if (result == SOCKET_ERROR) 
	{
        int error_code = WSAGetLastError();
		WSAShutdownError(error_code);
	    closesocket(client_socket);
	    return (DWORD)error_code;
	}

	closesocket(client_socket);

	return 0;

	#undef DEFAULT_BUFFER_SIZE
}


// https://docs.microsoft.com/en-us/cpp/cpp/cdecl?view=vs-2019
int __cdecl main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: <port>\n");
		return 1;
	}

	mutex_lock = CreateMutex(NULL, FALSE, NULL);
    if (mutex_lock == NULL) 
    {
        printf("CreateMutex error: %ld\n", GetLastError());
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
	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags 	  = AI_PASSIVE;


	// Resolve the server address and port
	const char* port = argv[1];
	struct addrinfo* address_info;
	result = getaddrinfo(NULL, port, &hints, &address_info);
	if (result != 0) 
	{
		WSAGetAddressInfoError(result);
	    WSACleanup();
	    return result;
	}


	// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
	SOCKET listen_socket = socket(address_info->ai_family, address_info->ai_socktype, address_info->ai_protocol);
	if (listen_socket == INVALID_SOCKET) 
	{
		result = WSAGetLastError();
		WSASocketError(result);
	    freeaddrinfo(address_info);
	    WSACleanup();
	    return result;
	}



    // Setup the TCP listening socket
    // https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-bind
    result = bind(listen_socket, address_info->ai_addr, (int)address_info->ai_addrlen);
    if (result == SOCKET_ERROR) 
    {
		result = WSAGetLastError();
		WSABindError(result);
	    freeaddrinfo(address_info);
	    closesocket(listen_socket);
	    WSACleanup();
        return result;
    }

    freeaddrinfo(address_info);

    // https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-listen
    result = listen(listen_socket, SOMAXCONN);
    if (result == SOCKET_ERROR) 
    {
    	result = WSAGetLastError();
		WSAListenError(result);
	    closesocket(listen_socket);
	    WSACleanup();
	    return result;
	}



	// Accept clients
	while (true)
	{
		SOCKET client_socket = accept(listen_socket, NULL, NULL);
		if (client_socket == INVALID_SOCKET) 
		{
		    result = WSAGetLastError();
			WSAAcceptError(result);
		}
		else
		{
			HANDLE thread_handle = CreateThread(0, 0, HandleClient, (void*)&client_socket, 0, NULL);
			if (thread_handle == NULL)
			{
				fprintf(stderr, "Failed to create thread for client %d. Error code %ld.\n", client_socket, GetLastError());
			}
			else
			{
				if (!CloseHandle(thread_handle))
				{
					fprintf(stderr, "Failed to close thread handle for client %d. Error code %ld.\n", client_socket, GetLastError());
				}
			}
		}
	}


	closesocket(listen_socket);
	WSACleanup();

	return 0;
}

