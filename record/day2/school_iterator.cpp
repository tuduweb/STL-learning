#include <iostream>
#include <string>

using namespace std;

//student data struct
class Student{
public:
    Student(const string& name, int schoolId, const string& college)
        : name(name), schoolId(schoolId), collage(college) {
            //
    }
    
    void showInfo() {
        std::cout << "姓名: " << name << "\t学号: " << schoolId << "\t学院 " << collage << std::endl;
    }

    // string name() const{
    //     return m_name;
    // }

    // int schoolId() const{
    //     return m_schoolId;
    // }

    // string collage() const{
    //     return m_college;
    // }

public:
    string m_name;
    int m_schoolId;
    string m_collage;

    string name;
    int schoolId;
    string collage;
};


class Iterator{
public:
    //判断下一个元素是否有元素
    virtual bool hasNext() = 0;
    //返回当前元素, 并走向下一个位置
    virtual Student next() = 0;
};

#include <vector>

class ComputerIterator: public Iterator
{
public:
    ComputerIterator(const vector<Student>& info)
    : m_info(info), m_curPos(0) {
        //
    }
    
    bool hasNext() override{
        return m_curPos < m_info.size();
    }

    Student next() override{
        Student curStu = m_info[m_curPos++];
        return curStu;
    }

private:
    vector<Student> m_info;
    int m_curPos;
};

//抽象聚合类
class Aggregate{
public:
    virtual void addStudent(const Student& stu) = 0;
    virtual void deleteStudent(const Student& stu) = 0;
    virtual Iterator* createIterator() = 0;
};

class ComputerAggregate: public Aggregate{
public:
    void addStudent(const Student& stu) override{
        m_info.emplace_back(stu);
    }

    void deleteStudent(const Student& stu) override{
        vector<Student>::const_iterator it = m_info.begin();
        while(m_info.end() != it) {
            if(it->name == stu.name && it->schoolId == stu.schoolId && it->collage == stu.collage) {
                break;
            }
            ++it;
        }
        m_info.erase(it);
    }

    //创建迭代器
    Iterator* createIterator() override{
        return new ComputerIterator(m_info);
    }

private:
    vector<Student> m_info;
};

int main() {
    Aggregate* computerCollege = new ComputerAggregate();
	computerCollege->addStudent(Student("索隆", 11, "计算机"));
	computerCollege->addStudent(Student("香克斯", 12, "计算机"));
	computerCollege->addStudent(Student("路飞", 33, "计算机"));
	computerCollege->addStudent(Student("娜美", 14, "计算机"));
	computerCollege->addStudent(Student("山治", 45, "计算机"));

	Iterator* it = computerCollege->createIterator();
	cout << "*************   计算机学院   **************" << endl;
	while (it->hasNext())
	{
		it->next().showInfo();
	}

    return 0;
}