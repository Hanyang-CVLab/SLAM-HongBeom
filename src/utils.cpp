/*
https://github.com/Shiaoming/ALIKE-cpp
BSD 3-Clause License

Copyright (c) 2022, Zhao Xiaoming
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <string>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <sstream>

namespace alike
{
    void load_imu_timestamps(std::string filename, std::vector<double> &vTimeStamps)
    {
        std::ifstream fTimes;
        fTimes.open(filename.c_str());
        vTimeStamps.reserve(5000);


        while(!fTimes.eof())
        {
            std::string s;
            getline(fTimes,s);
            if (!s.empty())
            {
                double t = std::stod(s) / 1e9;
                vTimeStamps.push_back(t);
            }
        }

        fTimes.close();
    }



    bool startsWith(std::string s, std::string sub)
    {
        return s.find(sub) == 0 ? true : false;
    }

    bool endsWith(std::string s, std::string sub)
    {
        if (s.rfind(sub) == -1)
        {
            return false;
        }
        else
        {
            return s.rfind(sub) == (s.length() - sub.length()) ? true : false;
        }
    }

    int isFileExist(std::string path)
    {
        return !access(path.c_str(), F_OK);
    }    

    bool isFile(std::string filename)
    {
        struct stat buffer;
        return (stat(filename.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode));
    }

    bool isDir(std::string filefodler)
    {
        struct stat buffer;
        return (stat(filefodler.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
    }

    void getFileNames(std::string path, std::vector<std::string> &filenames)
    {
        DIR *pDir;
        struct dirent *ptr;
        if (!(pDir = opendir(path.c_str())))
        {
            std::cout << "Folder doesn't Exist!" << std::endl;
            return;
        }
        while ((ptr = readdir(pDir)) != 0)
        {
            if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
            {
                filenames.push_back(path + "/" + ptr->d_name);
            }
        }
        closedir(pDir);
    }    
}