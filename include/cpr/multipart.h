#ifndef CPR_MULTIPART_H
#define CPR_MULTIPART_H

#include <initializer_list>
#include <string>
#include <vector>

namespace cpr {

struct File 
{
	File(std::string filePath, std::vector<unsigned char> fileBytes) : filepath(std::move(filePath)), filebytes(std::move(fileBytes)) {}
	std::string filepath;
	std::vector<unsigned char> filebytes;
};

struct Part 
{
    Part(const std::string& name, const std::string& value, const std::string& content_type = {})
            : name{name}, value{value}, content_type{content_type}, is_file{false} {}
    Part(const std::string& name, const int& value, const std::string& content_type = {})
            : name{name}, value{std::to_string(value)}, content_type{content_type}, is_file{false} {
    }
    Part(std::string name_, File file_, std::string content_type_ = {})
            : name(std::move(name_)), value(std::move(file_.filepath)), content_type(std::move(content_type_)), file_bytes(std::move(file_.filebytes)), is_file{true} {}

    std::string name;
    std::string value;
    std::string content_type;
	std::vector<unsigned char> file_bytes;
    bool is_file;
};

class Multipart {
  public:
    Multipart(const std::initializer_list<Part>& parts);

    std::vector<Part> parts;
};

} // namespace cpr

#endif
