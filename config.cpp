#include <fstream>
#include <iostream>
#include <string>

std::string get_config_value(const std::string &filename, const std::string &key)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Error: Unable to open configuration file " << filename << std::endl;
    return "";
  }

  std::string line;
  while (std::getline(file, line))
  {
    // Remove leading/trailing whitespaces
    size_t start = line.find_first_not_of(" \t");
    if (start != std::string::npos)
    {
      line = line.substr(start);
    }

    // Remove trailing whitespaces
    size_t end = line.find_last_not_of(" \t");
    if (end != std::string::npos)
    {
      line = line.substr(0, end + 1);
    }

    // Check if line starts with the key followed by an equal sign
    if (line.find(key + "=") == 0)
    {
      // Extract the value after the equal sign
      return line.substr(key.size() + 1);
    }
  }

  // Key not found in the file
  return "";
  
}
