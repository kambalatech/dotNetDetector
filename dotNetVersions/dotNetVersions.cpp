#include <string>
#include <vector>
#include "StringHelper.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

std::wstring CheckFor45PlusVersion(int releaseKey)
{
	std::wstring ret;
	if (releaseKey >= 528040)
		return ret = L"4.8";
	if (releaseKey >= 461808)
		ret = L"4.7.2";
	if (releaseKey >= 461308)
		return ret = L"4.7.1";
	if (releaseKey >= 460798)
		return ret = L"4.7";
	if (releaseKey >= 394802)
		return ret = L"4.6.2";
	if (releaseKey >= 394254)
		return ret = L"4.6.1";
	if (releaseKey >= 393295)
		return ret = L"4.6";
	if (releaseKey >= 379893)
		return ret = L"4.5.2";
	if (releaseKey >= 378675)
		return ret = L"4.5.1";
	if (releaseKey >= 378389)
		return ret = L"4.5";
	// This code should never execute. A non-null release key should mean
	// that 4.5 or later is installed.
	return ret;
}
#define TOTALBYTES    8192
#define BYTEINCREMENT 4096
//Writes the version
	void WriteVersion(std::wstring version, int spLevel = 0)
	{
		version = StringHelper::trim(version);
		
		if (version.empty())
			return;

		std::wstring spLevelString = L"";
		if (spLevel > 0)
		{
			spLevelString = L" Service Pack ";
			//spLevelString.append(spLevel);
		}
		_tprintf(TEXT("%s%s %d\n"), version.c_str(), spLevelString.c_str(), spLevel); //(uint32_t)		
	}

	LONG GetDWORDRegKey(HKEY hKey, const std::wstring strValueName, DWORD &nValue, DWORD nDefaultValue)
	{
		nValue = nDefaultValue;
		DWORD dwBufferSize(sizeof(DWORD));
		DWORD nResult(0);
		LONG nError = ::RegQueryValueExW(hKey,
			strValueName.c_str(),
			0,
			NULL,
			reinterpret_cast<LPBYTE>(&nResult),
			&dwBufferSize);
		if (ERROR_SUCCESS == nError)
		{
			nValue = nResult;
		}
		return nError;
	}
	LONG GetStringRegKey(HKEY hKey, const std::wstring strValueName, std::wstring &strValue, const std::wstring strDefaultValue = L"")
	{	
		strValue = strDefaultValue;
		WCHAR szBuffer[512];
		DWORD dwBufferSize = sizeof(szBuffer);
		ULONG nError;
		nError = RegQueryValueExW(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
		if (ERROR_SUCCESS == nError)
		{
			strValue = szBuffer;
		}
		return nError;
	}

	int GetSubKeysCount(HKEY hKey)
	{
		TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
		DWORD    cbName;                   // size of name string 
		TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
		DWORD    cchClassName = MAX_PATH;  // size of class string 
		DWORD    cSubKeys = 0;               // number of subkeys 
		DWORD    cbMaxSubKey;              // longest subkey size 
		DWORD    cchMaxClass;              // longest class string 
		DWORD    cValues;              // number of values for key 
		DWORD    cchMaxValue;          // longest value name 
		DWORD    cbMaxValueData;       // longest value data 
		DWORD    cbSecurityDescriptor; // size of security descriptor 
		FILETIME ftLastWriteTime;      // last write time 

		DWORD i, retCode;

		TCHAR  achValue[MAX_VALUE_NAME];
		DWORD cchValue = MAX_VALUE_NAME;

		// Get the class name and the value count. 
		retCode = RegQueryInfoKey(
			hKey,                    // key handle 
			achClass,                // buffer for class name 
			&cchClassName,           // size of class string 
			NULL,                    // reserved 
			&cSubKeys,               // number of subkeys 
			&cbMaxSubKey,            // longest subkey size 
			&cchMaxClass,            // longest class string 
			&cValues,                // number of values for this key 
			&cchMaxValue,            // longest value name 
			&cbMaxValueData,         // longest value data 
			&cbSecurityDescriptor,   // security descriptor 
			&ftLastWriteTime);       // last write time 	

		
		printf("\nNumber of subkeys: %d\n", cSubKeys);
		for (i = 0; i < cSubKeys; i++)
		{
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i,
				achKey,
				&cbName,
				NULL,
				NULL,
				NULL,
				&ftLastWriteTime);
			if (retCode == ERROR_SUCCESS)
			{
				_tprintf(TEXT("(%d) %s\n"), i + 1, achKey);

				std::wstring keyvalue = achKey;
				std::wstring value;
				//GetStringRegKey(hKey, achKey, value, keyvalue);
				//_tprintf(TEXT("(%d) %s\n"), i + 1, value);
			}
		}
		return cSubKeys;

	}
	void QueryKey(HKEY hKey)
	{
		TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
		DWORD    cbName;                   // size of name string 
		TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
		DWORD    cchClassName = MAX_PATH;  // size of class string 
		DWORD    cSubKeys = 0;               // number of subkeys 
		DWORD    cbMaxSubKey;              // longest subkey size 
		DWORD    cchMaxClass;              // longest class string 
		DWORD    cValues;              // number of values for key 
		DWORD    cchMaxValue;          // longest value name 
		DWORD    cbMaxValueData;       // longest value data 
		DWORD    cbSecurityDescriptor; // size of security descriptor 
		FILETIME ftLastWriteTime;      // last write time 

		DWORD i, retCode;

		TCHAR  achValue[MAX_VALUE_NAME];
		DWORD cchValue = MAX_VALUE_NAME;

		// Get the class name and the value count. 
		retCode = RegQueryInfoKey(
			hKey,                    // key handle 
			achClass,                // buffer for class name 
			&cchClassName,           // size of class string 
			NULL,                    // reserved 
			&cSubKeys,               // number of subkeys 
			&cbMaxSubKey,            // longest subkey size 
			&cchMaxClass,            // longest class string 
			&cValues,                // number of values for this key 
			&cchMaxValue,            // longest value name 
			&cbMaxValueData,         // longest value data 
			&cbSecurityDescriptor,   // security descriptor 
			&ftLastWriteTime);       // last write time 

		// Enumerate the subkeys, until RegEnumKeyEx fails.

		if (cSubKeys)
		{
			

			for (i = 0; i < cSubKeys; i++)
			{
				cbName = MAX_KEY_LENGTH;
				retCode = RegEnumKeyEx(hKey, i,
					achKey,
					&cbName,
					NULL,
					NULL,
					NULL,
					&ftLastWriteTime);
				if (retCode == ERROR_SUCCESS)
				{
					//_tprintf(TEXT("(%d) %s\n"), i + 1, achKey);
					if (achKey[0] == 'v')
					{
						std::wstring v4 = L"v4";
						if (!v4.compare(achKey))
						{
							continue;
						}
						//_tprintf(TEXT("(%d) %s\n"), i + 1, achKey);
						std::wstring key= L"SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\";
							
						key.append(achKey);
						HKEY ndpKey;
						std::wstring keyInstall = L"Install";
						std::wstring keyVersion = L"Version";
						std::wstring keySP = L"SP";
						std::wstring ValueVersion = L"";
						DWORD ValueInstall = 0;
						DWORD ValueSP = 0;
							

						if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
							key.c_str(),//TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\"),
							0,
							KEY_READ,
							&ndpKey) == ERROR_SUCCESS
							)
						{
							if (GetStringRegKey(ndpKey, keyVersion, ValueVersion) == ERROR_SUCCESS)
							{

								if (GetDWORDRegKey(ndpKey, keyInstall, ValueInstall, 0) == ERROR_SUCCESS)
								{
									GetDWORDRegKey(ndpKey, keySP, ValueSP, 0);
										
									if(ValueSP > 0 && ValueInstall == 1)
									{
										WriteVersion(ValueVersion, ValueSP);							
											
									}
									else
									{
										WriteVersion(ValueVersion);
									}
										
										
								}
										
									
							}
								
							RegCloseKey(ndpKey);
						}
						
					}
					
				}
			}
		}

		// Enumerate the key values. 

		if (cValues)
		{
			printf("\nNumber of values: %d\n", cValues);

			for (i = 0, retCode = ERROR_SUCCESS; i < cValues; i++)
			{
				cchValue = MAX_VALUE_NAME;
				achValue[0] = '\0';
				retCode = RegEnumValue(hKey, i,
					achValue,
					&cchValue,
					NULL,
					NULL,
					NULL,
					NULL);

				if (retCode == ERROR_SUCCESS)
				{
					_tprintf(TEXT("(%d) %s\n"), i + 1, achValue);
				}
			}
		}
	}
	static void Get45PlusFromRegistry()
	{
		std::wstring keyRelease = L"Release";// L"SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full\\)";
		std::wstring keyVersion = L"Version";
		std::wstring Value = L"";
		DWORD value;


		HKEY ndpKey;
		int SubKeysCount = 0;

		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
			TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full\\"),
			0,
			KEY_READ,
			&ndpKey) == ERROR_SUCCESS
			)
		{
			if (GetStringRegKey(ndpKey, keyVersion, Value) == ERROR_SUCCESS)
			{
				WriteVersion(Value);
			}
			else
			{
				GetDWORDRegKey(ndpKey, keyRelease, value, 0);
				WriteVersion(CheckFor45PlusVersion(value));
			}
			RegCloseKey(ndpKey);
		}		
	}
	void printSome()
	{
		HKEY hTestKey;

		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
			TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\"),
			0,
			KEY_READ,
			&hTestKey) == ERROR_SUCCESS
			)
		{
			QueryKey(hTestKey);
		}

		RegCloseKey(hTestKey);
	}
	int __cdecl _tmain()
	{
		_tprintf(TEXT("dotNet Version above 4.5 installed on your system is : "));
		Get45PlusFromRegistry();
		_tprintf(TEXT("\nCurrently installed \"classic\" .NET Versions in the system:\n"));
		printSome();

		char wait;
		scanf_s("%c", &wait);
		return 0;
	}

	
