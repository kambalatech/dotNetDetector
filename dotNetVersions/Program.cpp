//#include "Program.h"
//#include "winreg.h"
//#include "winerror.h"
//
//namespace DotNetVersions
//{
//
//	void Program::Main(std::vector<std::wstring> &args)
//	{
//		bool batchMode = false;
//
//		if (args.size() > 0 && (args[0] == L"/help" || args[0] == L"-help" || args[0] == L"--help" || args[0] == L"/?" || args[0] == L"-?" || args[0] == L"--?"))
//		{
//			std::wcout << L"Writes all the currently installed versions of \"classic\" .NET platform in the system.\r\nUse --b, -b or /b to use in a batch, showing only the installed versions, without any extra informational lines.";
//		}
//		else
//		{
//			if (args.size() > 0 && (args[0] == L"/b" || args[0] == L"-b" || args[0] == L"--b"))
//			{
//				batchMode = true;
//			}
//
//			if (!batchMode)
//			{
//				std::wcout << L"Currently installed \"classic\" .NET Versions in the system:" << std::endl;
//			}
//
//			//Show all the installed versions
//			Get1To45VersionFromRegistry();
//			Get45PlusFromRegistry();
//		}
//
//		if (!batchMode)
//		{
//			char ch;
//			scanf("%c", &ch);			
//		}
//	}
//
//	void Program::WriteVersion(const std::wstring &version, const std::wstring &spLevel)
//	{
//		version = StringHelper::trim(version);
//		if (version.empty())
//		{
//			return;
//		}
//
//		std::wstring spLevelString = L"";
//		if (!spLevel.empty())
//		{
//			spLevelString = L" Service Pack " + spLevel;
//		}
//
//		std::wcout << StringHelper::formatSimple(L"{0}{1}", version, spLevelString) << std::endl;
//	}
//
//	LONG GetStringRegKey(HKEY hKey, const std::wstring &strValueName, std::wstring &strValue, const std::wstring &strDefaultValue)
//	{
//		strValue = strDefaultValue;
//		WCHAR szBuffer[512];
//		DWORD dwBufferSize = sizeof(szBuffer);
//		ULONG nError;
//		nError = RegQueryValueExW(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
//		if (ERROR_SUCCESS == nError)
//		{
//			strValue = szBuffer;
//		}
//		return nError;
//	}
//
//	int OpenSubKey(const std::wstring subkey)
//	{
//		HKEY hKey;
//		LONG lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"(SOFTWARE\Microsoft\NET Framework Setup\NDP\)", 0, KEY_READ, &hKey);
//		bool bExistsAndSuccess(lRes == ERROR_SUCCESS);
//		bool bDoesNotExistsSpecifically(lRes == ERROR_FILE_NOT_FOUND);
//
//		
//		if (lResult != ERROR_SUCCESS)
//		{
//			if (lResult == ERROR_FILE_NOT_FOUND) {
//				printf("Key not found.\n");
//				return TRUE;
//			}
//			else {
//				printf("Error opening key.\n");
//				return FALSE;
//			}
//		}
//	}
//
//	void Program::Get1To45VersionFromRegistry()
//	{
//		// Opens the registry key for the .NET Framework entry.
////C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
////ORIGINAL LINE: using (RegistryKey ndpKey = Registry.LocalMachine.OpenSubKey("TangibleTempVerbatimOpenTagSOFTWARETangibleTempVerbatimBackslashMicrosoftTangibleTempVerbatimBackslashNET Framework SetupTangibleTempVerbatimBackslashNDPTangibleTempVerbatimBackslashTangibleTempVerbatimCloseTag"))
//		{
//			RegistryKey ndpKey = OpenSubKey(LR"(SOFTWARE\Microsoft\NET Framework Setup\NDP\)");
//			for (auto versionKeyName : *ndpKey.GetSubKeyNames())
//			{
//				// Skip .NET Framework 4.5 version information.
//				if (versionKeyName == L"v4")
//				{
//					continue;
//				}
//
//				if (versionKeyName.StartsWith(L"v"))
//				{
//
//					RegistryKey *versionKey = ndpKey.OpenSubKey(versionKeyName);
//					// Get the .NET Framework version value.
//					std::wstring name = std::any_cast<std::wstring>(versionKey->GetValue(L"Version", L""));
//					// Get the service pack (SP) number.
////C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
//					std::wstring sp = versionKey->GetValue(L"SP", L"").ToString();
//
//					// Get the installation flag, or an empty string if there is none.
////C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
//					std::wstring install = versionKey->GetValue(L"Install", L"").ToString();
//					if (install.empty()) // No install info; it must be in a child subkey.
//					{
//						WriteVersion(name);
//					}
//					else
//					{
//						if (!(sp.empty()) && install == L"1")
//						{
//							WriteVersion(name, sp);
//						}
//					}
//					if (!name.empty())
//					{
//						continue;
//					}
//					for (auto subKeyName : *versionKey->GetSubKeyNames())
//					{
//						RegistryKey *subKey = versionKey->OpenSubKey(subKeyName);
//						name = std::any_cast<std::wstring>(subKey->GetValue(L"Version", L""));
//						if (!name.empty())
//						{
////C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
//							sp = subKey->GetValue(L"SP", L"").ToString();
//						}
//
////C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
//						install = subKey->GetValue(L"Install", L"").ToString();
//						if (install.empty()) //No install info; it must be later.
//						{
//							WriteVersion(name);
//						}
//						else
//						{
//							if (!(sp.empty()) && install == L"1")
//							{
//								WriteVersion(name, sp);
//							}
//							else if (install == L"1")
//							{
//								WriteVersion(name);
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//

