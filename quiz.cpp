#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <boost/algorithm/string.hpp>

using namespace boost::algorithm;

bool loaddata(std::string filepath, std::vector<std::string> &lines)
{
    std::ifstream file;
    file.open(filepath.c_str());

    if (file.good())
    {
        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
        return true;
    }
    else
        return false;
}

std::vector<std::string> sesja2(std::vector<std::string> &lines, int ang)
{
    std::vector<std::string> bads;
    std::string ques, ans, corr;

    int licznik = 1;

    int n = lines.size();
    while (!lines.empty())
    {
        int curr_ques = rand() % lines.size();
        std::string curr = lines[curr_ques];

        if (ang == 1)
        {
            trim(ques = curr.substr(0, curr.find('-') - 1));
            trim(corr = curr.substr(curr.find('-') + 2, curr.size()));
        }
        else if (ang == 2)
        {
            trim(corr = curr.substr(0, curr.find('-') - 1));
            trim(ques = curr.substr(curr.find('-') + 2, curr.size()));
        }

        std::cout << licznik << "/" << n  << " "  << ques << ": ";
        std::cin >> std::ws;
        std::getline(std::cin, ans);
        trim(ans);

        if (ans == corr)
        {
            std::cout << "correct!\n";
        }
        else
        {
            std::cout << corr << std::endl;
            bads.push_back(curr);
        }

         licznik++;

        // Usunięcie bieżącego elementu
        lines.erase(lines.begin() + curr_ques);
    }
    return bads;
}

int main()
{
    system("clear");
    srand((unsigned)time(NULL));

    int ang = 2;

    std::cout << "1) ang -> pl\n";
    std::cout << "2) pl -> ang\n";

    std::cout << "wybor: ";
    std::cin >> ang;

    std::cin.ignore();

    std::vector<std::string> lines;

    if (loaddata("./slowka/slowka2.txt", lines))
    {
        while (!lines.empty())
            lines = sesja2(lines, ang);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}

