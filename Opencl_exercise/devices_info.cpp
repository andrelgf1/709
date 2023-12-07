/*
 ============================================================================
 Author        : G. Barlas
 Version       : 1.0
 Last modified : July 2018
 License       : Released under the GNU GPL 3.0
 Description   : 
 To build use  : g++ devices_info.cpp -lOpenCL -o devices_info
 ============================================================================
 */

#include <iostream>

#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

using namespace std;

const int MAXNUMDEV=10;
int main()
{
    cl_int errNum;
    cl_uint numPlatforms;
    cl_platform_id platformIds[MAXNUMDEV];
    cl_device_id devID[MAXNUMDEV];
    cl_uint numDev;
    
    // Get a reference to an object representing number of plataforms 
    // / Query the number of available OpenCL platforms without retrieving the actual platform IDs. 
    // Determine how many OpenCL platforms are available on the system without allocating memory for the platform IDs
    errNum = clGetPlatformIDs(MAXNUMDEV, platformIds, &numPlatforms);
    if (errNum != CL_SUCCESS || numPlatforms <= 0)
    {
        cerr << "Failed to find any OpenCL platforms." << endl;
        return 1;
    }

    cout << endl << "Number of OpenCL platforms: " << numPlatforms << endl << endl;

    for (cl_uint plat = 0; plat < numPlatforms; ++plat){
    
        // Get platform name
        char platName[256];
        errNum = clGetPlatformInfo(platformIds[plat], CL_PLATFORM_NAME, sizeof(platName), platName, nullptr);
        if (errNum != CL_SUCCESS)
        {
            cerr << "Failed to get platform name." << endl;
            continue;
        }
        cout << "  Name: " << platName << endl<< endl;


        // Get the device IDs matching the CL_DEVICE_TYPE parameter, up to the MAXNUMDEV limit
        errNum = clGetDeviceIDs( platformIds[plat],CL_DEVICE_TYPE_ALL, MAXNUMDEV, devID, &numDev);
        if (errNum != CL_SUCCESS || numDev <= 0)
        {
            cerr << "Failed to find any OpenCL devices." << endl<< endl;
            return 2;
        }
        cout << "       Number of OpenCL ' "<< platName<< " ' devices: " << numDev << endl << endl;
        // Go thru the number of devices in each plataform .
        for (cl_uint dev = 0; dev < numDev; ++dev){

            // Get device name
            char devName[100];
            errNum = clGetDeviceInfo(devID[dev], CL_DEVICE_NAME, sizeof(devName), (void*)devName, nullptr);
            if(errNum == CL_SUCCESS)
                cout << "           Device " << dev << " is : " << devName << endl<< endl;
           

            // Get OpenCL version
            char version[256];
            errNum = clGetDeviceInfo(devID[dev], CL_DEVICE_VERSION, sizeof(version), version, nullptr);
            if (errNum == CL_SUCCESS)
                cout << "                   OpenCL Version Supoorted : " << version << endl<< endl;
            
             // Get number of compute units
            cl_uint compUnits;
            errNum = clGetDeviceInfo(devID[dev], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(compUnits), &compUnits, nullptr);
            if (errNum == CL_SUCCESS)
                cout << "                   Compute Units: " << compUnits << endl<< endl;
            
            // Get global memory size
            cl_ulong gMSize;
            errNum = clGetDeviceInfo(devID[dev], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(gMSize), &gMSize, nullptr);
            if (errNum == CL_SUCCESS)
                cout << "                   Global Memory Size: " << gMSize / (1024 * 1024) << " MB" << endl<< endl;
            

            // Get local memory size
            cl_ulong lMSize;
            errNum = clGetDeviceInfo(devID[dev], CL_DEVICE_LOCAL_MEM_SIZE, sizeof(lMSize), &lMSize, nullptr);
            if (errNum == CL_SUCCESS)
                cout << "                   Local Memory Size: " << lMSize / 1024 << " KB" << endl<< endl<< endl<< endl;
            
        }
    }
    return 0;   
}
