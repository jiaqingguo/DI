

/*******************************************************************************
**  AREA1  :  include header files area
*******************************************************************************/


#include <iostream>
#include <cassert>
#include "ZipFunction.h"

//将wstring转换成string  
std::string wstring2string(std::wstring wstr)
{
    std::string result;
    //获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
    char* buffer = new char[len + 1];
    //宽字节编码转换成多字节编码  
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
    buffer[len] = '\0';
    //删除缓冲区并返回值  
    result.append(buffer);
    delete[] buffer;
    return result;
}

#define WstringToString(str)\
    std::wstring wide_str = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>{}.from_bytes(str);\
    size_t len = wide_str.size() * 4;\
    setlocale(LC_CTYPE, "");\
    char* p = new char[len];\
    size_t len2;\
    wcstombs_s(&len2, p, len, wide_str.c_str(), len);\
    std::string str1(p);\
    str = str1;\
    delete[] p;

std::wstring charToWString(const char* input, UINT codePage = CP_UTF8) {
    // 获取所需的宽字符数量
    int wideCharSize = MultiByteToWideChar(codePage, 0, input, -1, nullptr, 0);
    std::wstring wideString(wideCharSize, L'\0');

    // 进行转换
    MultiByteToWideChar(codePage, 0, input, -1, &wideString[0], wideCharSize);

    return wideString;
}


void extractZip(std::filesystem::path zip_file_path, const std::string& output_dir) {
    // 打开 ZIP 文件
    int err = 0;
    zip_t* zip = zip_open(zip_file_path.generic_u8string().c_str(), ZIP_RDONLY, &err);
    if (!zip) {
        zip_error_t zip_error;
        zip_error_init(&zip_error);
        zip_error_set(&zip_error, err, 0);
        std::cerr << "Failed to open zip file: " << zip_file_path << " - " << zip_error_strerror(&zip_error) << std::endl;
        zip_error_fini(&zip_error);
        return;
    }

    // 创建输出目录
    fs::create_directories(output_dir);

    // 获取 ZIP 文件中的文件数量
    zip_uint64_t num_entries = zip_get_num_entries(zip, 0);
    for (zip_uint64_t i = 0; i < num_entries; ++i) {
      //  const char* name = zip_get_name(zip, i, 0);
        const char* name = zip_get_name(zip, i, ZIP_FL_ENC_UTF_8); // 尝试使用 UTF-8 编码
        if (!name) {
            std::cerr << "Failed to get name of entry " << i << std::endl;
            continue;
        }
        
        std::wstring wideStr = charToWString(name);
        std::string strName = wstring2string(wideStr);
        fs::path output_file_path = fs::path(output_dir) / strName;
      
        // 创建目录
        if (strName.back() == '/') {
            fs::create_directories(output_file_path);
            continue;
        }

        zip_file_t* zip_file = zip_fopen(zip, strName.c_str(), 0);
        if (!zip_file) {
            std::cerr << "Failed to open entry " << strName << ": " << zip_strerror(zip) << std::endl;
            continue;
        }
        ////// 如果是目录，创建目录
        //if (name[strlen(name) - 1] == '/') {
        //    fs::create_directories(output_file_path);
        //    continue;
        //}

        //// 创建输出文件并写入内容
        //zip_file_t* zip_file = zip_fopen(zip, name, 0);
        //if (!zip_file) {
        //    std::cerr << "Failed to open entry " << name << std::endl;
        //    continue;
        //}

        // 读取文件内容
        std::ofstream output_file(output_file_path, std::ios::binary);
        if (!output_file.is_open()) {
            std::cerr << "Failed to create output file: " << output_file_path<<"  "<< zip_strerror(zip) << std::endl;
            zip_fclose(zip_file);
            continue;
        }

        char buffer[8192];
        zip_int64_t read_size;
        while ((read_size = zip_fread(zip_file, buffer, sizeof(buffer))) > 0) {
            output_file.write(buffer, read_size);
        }

        zip_fclose(zip_file);
        output_file.close();
    }

    zip_close(zip);
}


void CompressFile2Zip(std::filesystem::path unZipFilePath, const char* relativeName, zip_t* zipArchive)
{
    std::cerr << "CompressFile2Zip " << unZipFilePath << std::endl;
    std::ifstream file(unZipFilePath, std::ios::binary);
    file.seekg(0, std::ios::end);
    size_t bufferSize = file.tellg();
    char* bufferData = (char*)malloc(bufferSize);

    file.seekg(0, std::ios::beg);
    file.read(bufferData, bufferSize);

    //第四个参数如果非0，会自动托管申请的资源，直到zip_close之前自动销毁。
    zip_source_t* source =
        zip_source_buffer(zipArchive, bufferData, bufferSize, 1);

    if (source)
    {
        if (zip_file_add(zipArchive, relativeName, source, ZIP_FL_OVERWRITE) < 0) {
            std::cerr << "Failed to add file " << unZipFilePath
                << " to zip: " << zip_strerror(zipArchive) << std::endl;
            zip_source_free(source);
        }
    }
    else {
        std::cerr << "Failed to create zip source for " << unZipFilePath << ": "
            << zip_strerror(zipArchive) << std::endl;
    }
}

void CompressFile(std::filesystem::path unZipFilePath, std::filesystem::path zipFilePath)
{
    int errorCode = 0;
    zip_t* zipArchive = zip_open(zipFilePath.generic_u8string().c_str(),
        ZIP_CREATE | ZIP_TRUNCATE, &errorCode);
    if (zipArchive)
    {
        CompressFile2Zip(unZipFilePath, unZipFilePath.filename().string().c_str(),
            zipArchive);

        errorCode = zip_close(zipArchive);
        if (errorCode != 0)
        {
            zip_error_t zipError;
            zip_error_init_with_code(&zipError, errorCode);
            std::cerr << zip_error_strerror(&zipError) << std::endl;
            zip_error_fini(&zipError);
        }
    }
    else {
        zip_error_t zipError;
        zip_error_init_with_code(&zipError, errorCode);
        std::cerr << "Failed to open output file " << zipFilePath << ": "
            << zip_error_strerror(&zipError) << std::endl;
        zip_error_fini(&zipError);
    }
}

void CompressDirectory2Zip(std::filesystem::path rootDirectoryPath,
    std::filesystem::path directoryPath,
    zip_t* zipArchive)
{
    if (rootDirectoryPath != directoryPath)
    {
        std::cerr << "CompressFile2Zip " << rootDirectoryPath << std::endl;
        auto pathCs = std::filesystem::relative(directoryPath, rootDirectoryPath);
        if (zip_dir_add(zipArchive, std::filesystem::relative(directoryPath, rootDirectoryPath).generic_u8string().c_str(), ZIP_FL_ENC_UTF_8) < 0)
        {
            std::cerr << "Failed to add directory " << directoryPath
                << " to zip: " << zip_strerror(zipArchive) << std::endl;
        }
    }

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
    {
        if (entry.is_regular_file())
        {
            CompressFile2Zip(
                entry.path()/*.generic_u8string()*/,
                std::filesystem::relative(entry.path(), rootDirectoryPath)
                .generic_u8string()
                .c_str(),
                zipArchive);
        }
        else if (entry.is_directory())
        {
            CompressDirectory2Zip(rootDirectoryPath, entry.path()/*.generic_u8string()*/,
                zipArchive);
        }
    }
}

void CompressDirectory(std::filesystem::path directoryPath,
    std::filesystem::path zipFilePath)
{
    int errorCode = 0;
    zip_t* zipArchive = zip_open(zipFilePath.generic_u8string().c_str(),
        ZIP_CREATE | ZIP_TRUNCATE, &errorCode);
    if (zipArchive)
    {
        CompressDirectory2Zip(directoryPath, directoryPath, zipArchive);

        errorCode = zip_close(zipArchive);
        if (errorCode != 0)
        {
            zip_error_t zipError;
            zip_error_init_with_code(&zipError, errorCode);
            std::cerr << zip_error_strerror(&zipError) << std::endl;
            zip_error_fini(&zipError);
        }
    }
    else {
        zip_error_t zipError;
        zip_error_init_with_code(&zipError, errorCode);
        std::cerr << "Failed to open output file " << zipFilePath << ": "
            << zip_error_strerror(&zipError) << std::endl;
        zip_error_fini(&zipError);
    }
}



// 只支持多个文件 目录的话会缺少层级;
void CompressMultFile(const std::vector<fs::path>& paths, const fs::path& zipFilePath) {
    int errorCode = 0;
    zip_t* zipArchive = zip_open(zipFilePath.u8string().c_str(), ZIP_CREATE | ZIP_TRUNCATE, &errorCode);
    if (!zipArchive) {
        zip_error_t zipError;
        zip_error_init_with_code(&zipError, errorCode);
        std::cerr << "Failed to open output file " << zipFilePath << ": " << zip_error_strerror(&zipError) << std::endl;
        zip_error_fini(&zipError);
        return;
    }

    for (const auto& path : paths)
    {
        if (fs::exists(path))
        {
            if (fs::is_regular_file(path)) {
                CompressFile2Zip(path, path.filename().u8string().c_str(), zipArchive);
            }
            else if (fs::is_directory(path)) {
                CompressDirectory2Zip(path, path, zipArchive);
            }
        }
        else {
            std::cerr << "Path does not exist: " << path << std::endl;
        }
    }

    // 关闭 ZIP 文件
    errorCode = zip_close(zipArchive);
    if (errorCode != 0) {
        zip_error_t zipError;
        zip_error_init_with_code(&zipError, errorCode);
        std::cerr << zip_error_strerror(&zipError) << std::endl;
        zip_error_fini(&zipError);
    }
}

bool CompressMult2Zip(const std::vector<fs::path>& paths, const fs::path& zipFilePath)
{
    int errorCode = 0;
    zip_t* zipArchive = zip_open(zipFilePath.u8string().c_str(), ZIP_CREATE | ZIP_TRUNCATE, &errorCode);
    if (!zipArchive) {
        zip_error_t zipError;
        zip_error_init_with_code(&zipError, errorCode);
        std::cerr << "Failed to open output file " << zipFilePath << ": " << zip_error_strerror(&zipError) << std::endl;
        zip_error_fini(&zipError);
        return false;
    }
    if (paths.size() == 1)   /// if else 的区别在   CompressDirectory2Zip(path.parent_path(), path, zipArchive);  CompressDirectory2Zip(path, path, zipArchive);
    {
        for (const auto& path : paths)
        {
            if (fs::exists(path))
            {
                if (fs::is_regular_file(path))
                {
                    CompressFile2Zip(path, path.filename().u8string().c_str(), zipArchive);
                }
                else if (fs::is_directory(path))
                {
                    CompressDirectory2Zip(path, path, zipArchive);
                }
            }
            else {
                std::cerr << "Path does not exist: " << path << std::endl;
            }
        }
    }
    else  
    {
        for (const auto& path : paths)
        {
            if (fs::exists(path))
            {
                if (fs::is_regular_file(path))
                {
                    CompressFile2Zip(path, path.filename().u8string().c_str(), zipArchive);
                }
                else if (fs::is_directory(path))
                {
                    CompressDirectory2Zip(path.parent_path(), path, zipArchive);
                }
            }
            else {
                std::cerr << "Path does not exist: " << path << std::endl;
            }
        }

    }

    
    // 关闭 ZIP 文件
    errorCode = zip_close(zipArchive);
    if (errorCode != 0) 
    {
        zip_error_t zipError;
        zip_error_init_with_code(&zipError, errorCode);
        std::cerr << zip_error_strerror(&zipError) << std::endl;
        zip_error_fini(&zipError);
    }
    return true;
}