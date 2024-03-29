#ifdef __APPLE__
#include <filesystem>
#endif

void folderDir(const char path[], FILE * fp, int level) {
#if defined(_WIN32)
    char find_path[128];
    strcpy(find_path, path);
    strcat(find_path, "*");
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    bool bContinue = true;
    hFind = FindFirstFile(find_path, &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
    	return;
	}
    while (bContinue) {
        if (stricmp(FindFileData.cFileName, "..") && stricmp(FindFileData.cFileName, ".")){
            for (int i=0; i<level; ++i) {
		      fputs("  ",fp);
			}
            fputs(FindFileData.cFileName,fp);
			fputs("\n",fp);
            if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){
                strcpy(find_path, path);
				strcat(find_path, FindFileData.cFileName);
				strcat(find_path, "\\");
                folderdir(find_path,fp, level + 1);
            }
        }
        bContinue = FindNextFile(hFind, &FindFileData);
    }
	fclose(fp);
#elif defined(__APPLE__)
    for (const auto & file: std::__fs::filesystem::directory_iterator(path)) {
        if (file.is_directory()) {
            const char * filePath = file.path().c_str();
            const char * index = strstr(filePath, path);
            if (index != nullptr) {
                const char * filename = index + strlen(path);
                fputs(filename, fp);
                fputs("\n",fp);
            }
        }
    }
    fclose(fp);
#endif
}
