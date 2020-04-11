#pragma once

#include "UI.hpp"

#include <float.h>

#include <vector>
#include <string>
#include <map>

#include <future>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <string>
#include <vector>
#include <list>

#define MAX_FILE_DIALOG_NAME_BUFFER 1024

#ifndef CUSTOM_IMGUIFILEDIALOG_CONFIG
#include "UIFileBrowserConfig.hpp"
#else
#include CUSTOM_IMGUIFILEDIALOG_CONFIG
#endif

typedef void* UserDatas;

struct FileInfoStruct
{
	char type = ' ';
	std::string filePath;
	std::string fileName;
	std::string ext;
};

class ImGuiFileDialog
{
private:
	std::vector<FileInfoStruct> m_FileList;
	std::map<std::string, ImVec4> m_FilterColor;
	//std::string m_SelectedFileName;
	std::map<std::string, bool> m_SelectedFileNames; // map for have binary search
	std::string m_SelectedExt;
	std::string m_CurrentPath;
	std::vector<std::string> m_CurrentPath_Decomposition;
	std::string m_Name;
	bool m_ShowDialog = false;
	bool m_ShowDrives = false;
	std::string m_LastSelectedFileName; // for shift multi selectio

public:
	static char FileNameBuffer[MAX_FILE_DIALOG_NAME_BUFFER];
	static char DirectoryNameBuffer[MAX_FILE_DIALOG_NAME_BUFFER];
	static char SearchBuffer[MAX_FILE_DIALOG_NAME_BUFFER];
	static int FilterIndex;
	bool IsOk = false;
	bool m_AnyWindowsHovered = false;
	bool m_CreateDirectoryMode = false;

private:
	std::string dlg_key;
	std::string dlg_name;
	const char *dlg_filters{};
	std::string dlg_path;
	std::string dlg_defaultFileName;
	std::string dlg_defaultExt;
	std::function<void(std::string, UserDatas, bool*)> dlg_optionsPane;
	size_t dlg_optionsPaneWidth = 0;
	std::string searchTag;
	UserDatas dlg_userDatas;
	size_t dlg_countSelectionMax = 1; // 0 for infinite
	bool dlg_modal = false;

public:
	static ImGuiFileDialog* Instance()
	{
		static auto *_instance = new ImGuiFileDialog();
		return _instance;
	}

protected:
	ImGuiFileDialog(); // Prevent construction
	ImGuiFileDialog(const ImGuiFileDialog&) {}; // Prevent construction by copying
	ImGuiFileDialog& operator =(const ImGuiFileDialog&) { return *this; }; // Prevent assignment
	~ImGuiFileDialog(); // Prevent unwanted destruction

public: // standard dialog
	void OpenDialog(const std::string& vKey, const char* vName, const char* vFilters,
		const std::string& vPath, const std::string& vDefaultFileName,
		const std::function<void(std::string, UserDatas, bool*)>& vOptionsPane, const size_t&  vOptionsPaneWidth = 250,
		const int& vCountSelectionMax = 1, UserDatas vUserDatas = 0);
	void OpenDialog(const std::string& vKey, const char* vName, const char* vFilters,
		const std::string& vDefaultFileName, 
		const std::function<void(std::string, UserDatas, bool*)>& vOptionsPane, const size_t&  vOptionsPaneWidth = 250,
		const int& vCountSelectionMax = 1, UserDatas vUserDatas = 0);
	void OpenDialog(const std::string& vKey, const char* vName, const char* vFilters,
		const std::string& vPath, const std::string& vDefaultFileName, 
		const int& vCountSelectionMax = 1, UserDatas vUserDatas = 0);
	void OpenDialog(const std::string& vKey, const char* vName, const char* vFilters,
		const std::string& vFilePathName, const int& vCountSelectionMax = 1, 
		UserDatas vUserDatas = 0);

public: // modal dialog
	void OpenModal(const std::string& vKey, const char* vName, const char* vFilters,
		const std::string& vPath, const std::string& vDefaultFileName,
		const std::function<void(std::string, UserDatas, bool*)>& vOptionsPane, const size_t&  vOptionsPaneWidth = 250,
		const int& vCountSelectionMax = 1, UserDatas vUserDatas = 0);
	void OpenModal(const std::string& vKey, const char* vName, const char* vFilters,
		const std::string& vDefaultFileName,
		const std::function<void(std::string, UserDatas, bool*)>& vOptionsPane, const size_t&  vOptionsPaneWidth = 250,
		const int& vCountSelectionMax = 1, UserDatas vUserDatas = 0);
	void OpenModal(const std::string& vKey, const char* vName, const char* vFilters,
		const std::string& vPath, const std::string& vDefaultFileName,
		const int& vCountSelectionMax = 1, UserDatas vUserDatas = 0);
	void OpenModal(const std::string& vKey, const char* vName, const char* vFilters,
		const std::string& vFilePathName, const int& vCountSelectionMax = 1,
		UserDatas vUserDatas = 0);

	bool FileDialog(const std::string& vKey, ImGuiWindowFlags vFlags = ImGuiWindowFlags_NoCollapse,
		ImVec2 vMinSize = ImVec2(0,0), ImVec2 vMaxSize = ImVec2(FLT_MAX, FLT_MAX));
	void CloseDialog(const std::string& vKey);

	std::string GetFilepathName();
	std::string GetCurrentPath();
	std::string GetCurrentFileName();
	std::string GetCurrentFilter();
	UserDatas GetUserDatas();
	std::map<std::string, std::string> GetSelection(); // return map<FileName, FilePathName>

	void SetFilterColor(const std::string& vFilter, ImVec4 vColor);
	bool GetFilterColor(const std::string& vFilter, ImVec4 *vColor);
	void ClearFilterColor();

private:
	bool SelectDirectory(const FileInfoStruct& vInfos);

	void SelectFileName(const FileInfoStruct& vInfos);
	void RemoveFileNameInSelection(const std::string& vFileName);
	void AddFileNameInSelection(const std::string& vFileName, bool vSetLastSelectionFileName);

	void CheckFilter();

	void SetPath(const std::string& vPath);
	void ScanDir(const std::string& vPath);
	void SetCurrentDir(const std::string& vPath);
	bool CreateDir(const std::string& vPath);
	void ComposeNewPath(std::vector<std::string>::iterator vIter);
	void GetDrives();
};

namespace Engine
{
	class UIFileBrowser
	{
	public:
		static void drawGui()
		{ 
			// open Dialog Simple
			if (ImGui::Button("Open File Dialog"))
				ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp\0.h\0.hpp\0\0", ".");

			// display
			if (ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey")) 
			{
				// action if OK
				if (ImGuiFileDialog::Instance()->IsOk == true)
				{
					std::string filePathName = ImGuiFileDialog::Instance()->GetFilepathName();
					std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
					// action
				}
				// close
				ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
			}
		}
	};
}