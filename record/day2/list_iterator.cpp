#include <iostream>

namespace Learning{
    template<typename T>
    class ListItem;

    template<typename T>
    std::ostream& operator<<(std::ostream& out, ListItem<T>& d);

    template<typename T>
    class ListItem{
    public:
        ListItem(const T& t): m_data(t), m_next(nullptr) {}
        /*std::forward通常是用于完美转发的，它会将输入的参数原封不动地传递到下一个函数中，这个“原封不动”指的是，如果输入的参数是左值，那么传递给下一个函数的参数的也是左值；如果输入的参数是右值，那么传递给下一个函数的参数的也是右值。*/
        ListItem(T&& t): m_data(std::forward<T>(t)), m_next(nullptr) {}

        //将多个参数完美转发到子构造
        template<typename... Types>
        ListItem(Types&&... args): m_data(std::forward<Types>(args)...), m_next(nullptr) {}

        void setNext(ListItem<T>* n) {
            m_next = n;
        }

        ListItem<T>* next() {
            return m_next;
        }

        friend std::ostream& operator<< <T>(std::ostream& out, ListItem& d);

    private:
        T m_data;// T* to T
        ListItem<T>* m_next;
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& out, ListItem<T>& item) {
        out << item.m_data;
        return out;
    }

}


namespace Learning{
    template<typename T>
    class list{
    public:
        list(): m_head(nullptr) {}
        void push(const T& t) {
            ListItem<T>* data = new ListItem<T>(t);
            data->setNext(m_head);
            m_head = data;
        }

        template<typename... Types>
        void emplace(Types&&... args) {
            ListItem<T>* data = new ListItem<T>(std::forward<Types>(args)...);
            data->setNext(m_head);
            m_head = data;
        }

        ListItem<T>* front() {
            return m_head;
        }

    private:
        ListItem<T>* m_head;
    };
}

/**
 * 使用过STL都知道，iterator主要是用来遍历容器中的数据节点，那么上面这个list，我们的主要功能是能够不用在外部知道list的实现原理，使用iterator来遍历数据。
 * 所以iterator的主要功能有：
 * 1. 支持++，遍历元素。
 * 2. 支持*，取元素程序。
 * 3. 支持->，指针操作。
 * 4. 支持==和!=操作，比较iterator是否到了结尾。
**/
namespace Learning{
    template<typename T>
    class ListIterator{
        public:
            using value_type = T;
            using reference = T&;
            using const_reference = const T&;
            using pointer = T*;
            using const_pointer = const T*;
            using size_type = size_t;
            //ptrdiff_t是C/C++标准库中定义的一个与机器相关的数据类型。ptrdiff_t类型变量通常用来保存两个指针减法操作的结果。
            using difference_type = ptrdiff_t;

            ListIterator(pointer p = nullptr): m_it(p) {}

            bool operator==(const ListIterator& rhs) const{
                return m_it == rhs.m_it;
            }

            bool operator!=(const ListIterator& rhs) const{
                return m_it != rhs.m_it;
            }

            ListIterator& operator++() {
                m_it = m_it->next();
                return *this;
            }

            ListIterator& operator++(int) {
                // == *m_it;
                value_type tmp = *this;
                ++&*this;
                return tmp;
            }

            reference operator*() {
                return *m_it;
            }

            pointer operator->() {
                return m_it;
            }
        
        private:
            pointer m_it;
    };
}

int main() {
    Learning::list<std::string> nameList;
    
    nameList.push(std::string("Jack"));
    
    nameList.push("Peter");
    nameList.push("Joke");
    nameList.push("Charry");

    Learning::ListIterator<Learning::ListItem<std::string>> iter(nameList.front());
    Learning::ListIterator<Learning::ListItem<std::string>> end;

    while(iter != end) {
        std::cout << *iter << std::endl;
        ++iter;
    }

    return 0;
}