#include <iostream>
#include <cstring>

class myString
{
public:
    explicit myString(const char* str)
    {
        size_t str_size = strlen(str); // sprawdzamy size stringa

        data = (char*)malloc(str_size + 1); // alokujemy str_size + 1 bajtow i trzymamy pointer do tej pamieci w data
        memcpy(data, str, str_size + 1); // kopiujemy ze str do data str_size +1 bajtow

        size = str_size + 1;
    }

    // myString('a', 15) = 'aaaaaaaaaaaaaaaa'
    myString(char ch, size_t size)
    {
        this->size = size + 1;
        auto& member_size = this->size;

        data = (char*)malloc(member_size);

        for(size_t i = 0; i < member_size - 1; ++i)
        {
            data[i] = ch;
        }
        data[member_size] = '\0';
    }

    myString(const myString& other)
    {
        size = other.size;

        data = (char*)malloc(size);
        memcpy(data, other.data, size);
    }

    myString(myString&& other)  noexcept {
        data = other.data;
        size = other.size;

        other.data = nullptr;
    }

    // str1 = "asdsadasda";
    // str1 = myString{"xddddd"};

    myString& operator=(myString&& other) noexcept {
        if(data)
            free(data);

        data = other.data;
        size = other.size;

        other.data = nullptr;

        return *this;
    }

    myString& operator=(const myString& other) {
        if(data)
            free(data);

        size = other.size;

        data = (char*)malloc(size);
        memcpy(data, other.data, size);

        return *this;
    }

    myString& operator+(const myString& other) {
        size_t combined_size = other.size + size;
        char* original_data = data;
        data = (char*) malloc(combined_size - 1);

        for(size_t i = 0; i <= size - 2; ++i)
        {
            data[i] = original_data[i];
        }

        for(size_t i = 0; i < other.size; ++i)
        {
            data[size - 1 + i] = other.data[i];
        }

        free(original_data);

        return *this;
    }

    ~myString()
    {
        if(data)
            free(data);
    }

    friend std::ostream& operator<<(std::ostream&, const myString&);

    friend myString operator+(const myString& first, const myString& second);

private:
    char* data;
    size_t size;
};

std::ostream& operator<<(std::ostream& out, const myString& str)
{
    if(str.data)
        out << str.data;

    return out;
}

//myString operator+(const myString& first, const myString& second)
//{
//
//}


int main()
{
    myString strink{"dupajasiukaruzela"};
    myString strink2{ "nowystring" };
    std::cout << "strink1 value: " << strink << std::endl;

//    myString strink3{std::move(strink)};
//    std::cout << "strink1 value: " << strink << std::endl;
//    std::cout << "strink2 value: " << strink2 << std::endl;

    strink + strink2;

    std::cout << "strink3 value: " << strink << std::endl;


    return 0;
}
