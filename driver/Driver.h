#pragma once
#include "../includes.h"

class Driver
{
public:
	Driver(const wchar_t* driver_name, int target_process_id);
	~Driver();
	uintptr_t get_base_address(const wchar_t* process_name);
    uintptr_t allocate_virtual_memory(int size, int allocation_type, int protect_type);
    bool protect_virtual_memory(uintptr_t address, int size, int protect_type);
    bool write_memory(uintptr_t destination, uintptr_t source, int size);
    bool read_memory(uintptr_t source, uintptr_t destination, int size);
    HANDLE driver_handle;
    int target_process_id;
private:

    /*
            Driver Structs
    */

    typedef struct _k_get_base_module_request {
        ULONG pid;
        ULONGLONG handle;
        WCHAR name[260];
        char junk[0x1000];
        char junk2[0x512];
        char junk3[0x321];
    } k_get_base_module_request, * pk_get_base_module_request;

    typedef struct _k_rw_request {
        ULONG pid;
        ULONGLONG src;
        ULONGLONG dst;
        ULONGLONG size;
        char junk[0x1000];
        char junk2[0x512];
        char junk3[0x321];
    } k_rw_request, * pk_rw_request;

    typedef struct _k_alloc_mem_request {
        ULONG pid, allocation_type, protect;
        ULONGLONG addr;
        SIZE_T size;
        char junk[0x1000];
        char junk2[0x512];
        char junk3[0x321];
    } k_alloc_mem_request, * pk_alloc_mem_request;

    typedef struct _k_protect_mem_request {
        ULONG pid, protect;
        ULONGLONG addr;
        SIZE_T size;
        char junk[0x1000];
        char junk2[0x512];
        char junk3[0x321];
    } k_protect_mem_request, * pk_protect_mem_request;

    /*
        Driver IOCTL codes
    */
#define ioctl_read_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x708, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ioctl_write_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x709, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ioctl_get_module_base CTL_CODE(FILE_DEVICE_UNKNOWN, 0x710, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) 
#define ioctl_protect_virutal_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x711, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) 
#define ioctl_allocate_virtual_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x712, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)


};
