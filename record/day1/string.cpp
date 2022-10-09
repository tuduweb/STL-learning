#include <iostream>
#include <cstring>

class String {
public:
    String(const char* str = nullptr); //默认构造
    String(const String& other); // 默认拷贝
    /**
     * 先举个生活例子，你有一本书，你不想看，但我很想看，那么我有哪些方法可以让我能看这本书？
     * 有两种做法，一种是你直接把书交给我，
     * 另一种是我去买一些稿纸来，然后照着你这本书一字一句抄到稿纸上。
     * 显然，第二种方法很浪费时间，但这正是有些深拷贝构造函数的做法，
     * 而移动构造函数便能像第一种做法一样省时，第一种做法在 C++ 中叫做完美转发。
     *
     * 移动语义：
     * 源对象资源的控制权全部交给目标对象。
     */
    String(String&& other) noexcept; //移动构造函数
    String(char* s, int len);
    ~String();

    //获取原始数据
    const char* data() const {
        return buffer;
    }
    const size_t length() const {
        return m_length;
    }

    char& operator[](size_t index) {
        return buffer[index];
    }

    /*
    * 拷贝构造函数使用传入对象的值生成一个新的对象的实例
    * 赋值运算符是将对象的值复制给一个已经存在的实例
    * @return: 这是默认的，返回自己的引用
    */
    String& operator=(const String& other) {
        if (&other != this) {
            delete[] buffer;
            String(other.buffer);
        }
        return *this;
    }

    /*
    * 移动赋值操作即把参数传进来的对象的所有权转移到this指向的对象
    * 掏空other对象的所有
    */
    String& operator=(String&& other) {
        if (&other != this) {
            delete[] buffer;
            buffer = other.buffer;
            m_length = other.m_length;
            other.buffer = nullptr;
            //other.m_length = 0;
        }
        return *this;
    }

    /*
    * 关于是返回对象本身还是返回对象引用
    * 如果函数返回在函数中创建的临时对象，则不要使用引用
    * 如果函数返回的是通过引用或指针传递给它的对象，则应当按引用返回对象
    * 如果先创建一个对象，然后返回改对象的副本，则可以使用返回对象
    */
    String operator+(const String& other) {
        /** 以下实现方法报错 原因是在析构时,delete; 终极原因是下面计算错误了
        size_t length = (m_length - 1) + (other.m_length - 1) + 1;
        char* newBuffer = new char[length];
        std::strcpy(newBuffer, buffer);
        std::strcat(newBuffer, other.buffer);

        delete[] buffer;
        buffer = newBuffer;
        m_length = length;
         **/
        String _str;
        
        if (nullptr == this->buffer) {
            _str = other;
        }
        else if (nullptr == other.buffer) {
            _str = *this;
        }
        else {
            _str.buffer = new char[m_length + other.m_length + 1];
            std::strcpy(_str.buffer, this->buffer);
            std::strcat(_str.buffer, other.buffer);
            _str.m_length = std::strlen(_str.buffer);
        }

        return _str;
    }

    bool operator==(const String& other) {
        if (m_length != other.m_length)
            return false;

        return 0 == std::strcmp(buffer, other.buffer);
    }

    friend std::ostream& operator<<(std::ostream& output, const String& str) {
        if(nullptr == str.buffer) {
            output << "";
        }else{
            output << str.buffer;
        }
        return output;
    }

    friend std::istream& operator>>(std::istream& input, String& str) {
        //need to add size judgement
        input >> str.buffer;
        return input;
    }

private:
    char* buffer;
    size_t m_length;
};

String::String(const char* str) {
    if (str == nullptr) {
        m_length = 0;
        buffer = nullptr;
        return;
    }
    m_length = std::strlen(str);
    buffer = new char[m_length + 1];
    std::strcpy(buffer, str);
    //std::cout << "constructor" <<  this << std::endl;
}

String::String(const String& other) : String(other.buffer) {

}

String::String(String&& other) noexcept {
    //掏空other对象
    buffer = nullptr;
    buffer = other.buffer;
    m_length = other.m_length;

    other.buffer = nullptr;
    other.m_length = 0;
}

String::~String() {
    delete[] buffer;
}

int main() {
    std::cout << "hello myStream class" << std::endl;

    using namespace std;

#if 1
    String str1("Hello");
    cout << str1.data() << endl;
    cout << str1.length() << endl;

    String str2 = "World";
    cout << str2.data() << endl;
    cout << str2.length() << endl;

    String str3 = str1 + str2;
    cout << str3.data() << endl;
    cout << str3.length() << endl;
#else
    String str4("StringTest");
    String str5(str4);
    cout << str5.data() << endl;
    cout << str5.length() << endl;
#endif

    cout << str3 << endl;

    cin >> str3;
    cout << str3 << endl;
    return 0;
}