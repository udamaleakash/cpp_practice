#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

extern "C"
{
    // buffer to return data
    static char result[1024];

    // function to read CSV and return formatted string
    const char *read_csv(const char *filename)
    {
        std::ifstream file(filename);
        if (!file)
        {
            strcpy(result, "Error: File not found");
            return result;
        }

        std::string line;
        std::string output = "";

        while (getline(file, line))
        {
            std::stringstream ss(line);
            std::string id, name, salary;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, salary, ',');
            output += "ID:" + id + " Name:" + name + " Salary:" + salary + "\n";
        }
        strncpy(result, output.c_str(), sizeof(result) - 1);
        result[sizeof(result) - 1] = '\0';

        return result;
    }
    void display()
    {

    }
}