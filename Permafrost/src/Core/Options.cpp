#include "Permafrost/Core/Options.h"

#include <fstream>

#include "Permafrost/Core/Log.h"

const std::string TRIM_DELIMITERS = "\f\n\r\t\v";

#pragma region ParsingFunctions

std::string LeftTrim(const std::string& Str)
{
    std::string::size_type s = Str.find_first_not_of(TRIM_DELIMITERS);
    if (s == std::string::npos)
        return "";
    return Str.substr(s);
}

std::string RightTrim(const std::string& Str)
{
    std::string::size_type s = Str.find_last_not_of(TRIM_DELIMITERS);
    if (s == std::string::npos)
        return "";
    return Str.substr(0, s + 1);
}

std::string Trim(const std::string& Str)
{
    return RightTrim(LeftTrim(Str));
}

bool IsComment(const std::string& Str)
{
    std::string TrimmedStr = LeftTrim(Str);
    return TrimmedStr[0] == '#';
}

bool IsEmpty(const std::string& Str)
{
    std::string TrimmedStr = LeftTrim(Str);
    return TrimmedStr.empty();
}

bool IsProperty(const std::string& Str)
{
    std::string TrimmedStr = LeftTrim(Str);

    //Check that there is an affectation
    std::string::size_type s = TrimmedStr.find_first_of("=");
    if (s == std::string::npos)
    {
        return false;
    }

    //Check the Key validity
    std::string Key = TrimmedStr.substr(0, s);
    Key = Trim(Key);
    return !Key.empty();
}

std::pair<std::string, std::string> ParseProperty(const std::string& Str)
{
    std::string TrimmedStr = Trim(Str);
    std::string::size_type s = TrimmedStr.find_first_of("=");
    std::string Key = Trim(TrimmedStr.substr(0, s));
    std::string Val = Trim(TrimmedStr.substr(s+1));

    return std::pair<std::string, std::string>(Key, Val);
}

#pragma endregion ParsingFunctions


void Options::Clear()
{
    Options.clear();
}

bool Options::Contains(const std::string& Key) const
{
    return Options.find(Key) != Options.end();
}

void Options::Add(const std::string Key, const std::string& Value)
{
    Options.insert(std::make_pair(Key, Value));
}

void Options::Remove(const std::string& Key)
{
    auto It = Options.find(Key);    
    if (It != Options.end())
    {
        Options.erase(It);
    }
}

const std::string& Options::GetString(const std::string& Key) const
{
    auto It = Options.find(Key);
    assert(It != Options.end());
    
    return It->second;
}

i32  Options::GetInteger(const std::string& Key) const
{
    return std::stoi(GetString(Key)); 
}

f32  Options::GetFloat(const std::string& Key) const    
{
    return std::stof(GetString(Key));
}

bool Options::Parse(int argc, char** argv)
{
    return true;
}

bool Options::Load(const std::string& Filename)
{

    LOG_DEBUG("Loading Properties File '{0}'", Filename);
    std::ifstream Stream(Filename);

    if (!Stream.is_open())
    {
        LOG_ERROR("Failed to open Properties File '{0}'", Filename);
        return false;
    }

    std::unordered_map<std::string, std::string> Properties;
    u32 LineNumber = 0;
    std::string Line;
    while (std::getline(Stream, Line))
    {
        LineNumber++;
        if (IsComment(Line) || IsEmpty(Line)) continue;

        if (IsProperty(Line))
        {
            std::pair<std::string, std::string> Property = ParseProperty(Line);
            Properties.insert(Property);
            continue;
        }

        LOG_ERROR("Invalid Properties File '{0}' @ Line {1}", Filename, LineNumber);
        return false;
    }

    //Options update is deferred to prevent Corruption on Parse failure
    for (auto Pair : Properties)
    {
        Options[Pair.first] = Pair.second;
    }
    return true;
}

bool Options::Save(const std::string& Filename)
{
    LOG_DEBUG("Saving Properties File '{0}'", Filename);
    
    std::ofstream Stream(Filename);
    if (!Stream.is_open())
    {
        LOG_ERROR("Failed to open Properties File '{0}'", Filename);
        return false;
    }

    //Write all the Properties line by line
    for (auto Properties : Options)
    {
        Stream << Properties.first << " = " << Properties.second << "\n";
    }
    
    return true;
}