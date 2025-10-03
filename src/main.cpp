#include <iostream>
#include <cstring>
#include <string>
#include <filesystem>   
#include <unistd.h>
#include <vector>

namespace filesystem = std::filesystem;

char* parseSystem(char* variable)
{
    char* variableValue = getenv(variable);
    return variableValue;
}
bool checkSystemVariable(char* variable)
{
    char* posibleVariable = getenv(variable);

    if ( posibleVariable == NULL)
    {
        std::cout<<""<<std::endl;
        return false;

    }else
    {
        return true;
    }
}
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');
    
    if (start == std::string::npos) return "";
    return str.substr(start, end - start + 1);
}
void printCommandWithArguments( std::string command, std::string arguments)
{
    arguments = trim(arguments);
    
    if (!arguments.empty())
    {
        if(arguments.front() == '$')
        {
            arguments.erase(0,1);
            char* variable =  arguments.data();
            if (checkSystemVariable(variable))
            {
                variable = parseSystem(variable);
                std::cout<<"Команда "<<command<<" имеет аргументы: "<<variable<<std::endl;
            }
            else
            {
                std::cout<<"Команда "<<command<<" не имеет таких аргумент, такой системной переменной не существует."<<std::endl;
            }
        }else
        {
            std::cout<<"Команда "<<command<<" имеет аргументы: ";
            std::cout<<arguments<<std::endl;
        }
    }
    else
    {
        std::cout<<"Команда "<<command<<" не имеет аргументов."<<std::endl;
    }
    
}
bool exit()
{
    std::cout<<"=>"<<" Выполняется выход, до свидания.";
    return false;
}
std::vector<std::string> getCommandAndArguments(std::string& executeLine, int lineLenght)
{
    std::vector<std::string> commandAndArguments;
    std::string command;
    std::string arguments;
    int countOfSpaces = 0;

    for (int i = 0; i < lineLenght; i++)
    {
        if (executeLine[i] == ' ' && countOfSpaces == 0)
        {
            countOfSpaces++;
            command = executeLine.substr(0, i);
            arguments = executeLine.substr(i, lineLenght);

            commandAndArguments.push_back(command);
            commandAndArguments.push_back(arguments);
            break;
        }
    }
    if(countOfSpaces == 0)
    {
        command = executeLine;
        commandAndArguments.push_back(command);
        commandAndArguments.push_back(arguments);
    }
    return commandAndArguments;
}
void systemInvite(){
    // std::string vfsDirectory = "VFS";
    // std::string logDirectory = "logs";
    std::string homeDirectory = getenv("HOME");
    const std::string GREEN = "\033[32m";
    const std::string RESET = "\033[0m";
    char* userName = getlogin();
    std::cout<<GREEN<<userName<<homeDirectory<<">> "<<RESET;
}
void executeCommand(std::string executeLine, bool& whileLife)
{
    executeLine = trim(executeLine);

    int lineLenght = executeLine.length();
    std::string command = getCommandAndArguments(executeLine, lineLenght)[0];
    std::string arguments = getCommandAndArguments(executeLine, lineLenght)[1];

    if (command == "exit")
    {
        whileLife = exit();
    }
    else if (command == ""){}

    else if (command == "ls" || command == "cd")
    {
        printCommandWithArguments(command, arguments);
    }
    else if (command.find_first_not_of('$'))
    {
        command.erase(0,1);
        char* variable =  command.data();
        if (checkSystemVariable(variable))
        {
            std::cout<<parseSystem(variable)<<std::endl;
        }
    }
    else
    {
        std::cout<<"Команда "<<command<<" не найдена или не существует."<<std::endl;
    }

}
void lifeWhile()
{
    bool isInWork = true;
    std::string command;

    while(isInWork)
    {
        if (isInWork == false)
        {
            break;
        }
        else
        {   
            systemInvite();
            std::getline(std::cin, command);
            executeCommand(command, isInWork);
        }
    }
}
int main()
{   
    lifeWhile();
    
    return 0;
}