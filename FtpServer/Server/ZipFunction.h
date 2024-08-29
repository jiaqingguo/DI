
#ifndef ZIP_FUNCTION
#define ZIP_FUNCTION

/*******************************************************************************
**  AREA1  :  include header files area
*******************************************************************************/


#include <filesystem>
#include <fstream>
#include <iostream>
#include "libzip/include/zip.h"
//#include <string>
//#include <vector>
#include <windows.h>

namespace fs = std::filesystem;

void extractZip(std::filesystem::path zip_file_path, const std::string& output_dir);


void CompressFile2Zip(std::filesystem::path unZipFilePath, const char* relativeName, zip_t* zipArchive);

void CompressFile(std::filesystem::path unZipFilePath, std::filesystem::path zipFilePath);

void CompressDirectory2Zip(std::filesystem::path rootDirectoryPath,
    std::filesystem::path directoryPath,
    zip_t* zipArchive);

void CompressDirectory(std::filesystem::path directoryPath,
    std::filesystem::path zipFilePath);


// 只支持多个文件 目录的话会缺少层级;
void CompressMultFile(const std::vector<fs::path>& paths, const fs::path& zipFilePath);

void CompressMult2Zip(const std::vector<fs::path>& paths, const fs::path& zipFilePath);

#endif