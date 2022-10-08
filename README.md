## STL-Learning

深入学习STL库。

### 来源 & 思想

作者：陈硕
链接：https://www.zhihu.com/question/53085291/answer/133458242
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

首先明确，不是整个 C++ 标准库都叫 STL，STL 主要包括泛型容器及其 iterator、泛型算法这三块内容。

你可以先写一个 non-template 的 string，学会基本的 copy control，因为 STL container 都是 value semantics。

再写一个 iterator，学会基本的 operator overloading，你这个 iterator 可以返回随机数，用来初始化一个 std::vector。

然后定 scope，这恐怕是最难的，决定了做这个项目的性价比：
1. scope 定小了工作量不够，学不到东西；
2. 定大了事倍功半，写了很多体力活的代码，不划算。

可以考虑：
1. 要不要支持 C++11？主要是要不要用 rvalue reference？
2. 要不要支持异常安全？是不是可以假设禁用异常？
3. container 要不要支持 allocator？
4. 哪些功能不必实现？list::sort() ？checked iterator？
5. algorithm 要实现哪些？next_permutation() 要不要写？如果实现 count()，你多半还需要了解一下 traits 。input iterator 和 forward iterator 要不要区别对待？

接下来就可以一点一点堆代码了，先写 list<T> 和 vector<T>，看看能不能装下你的 string 和 std::string。

写 vector 需要知道 placement new 的用法，还要会直接调用析构函数。

vector 的 iterator 可以偷懒用 T*，list 的 iterator 必须自己写，写完了看看能不能和 STL 的 algorithm 配合。要不要实现关联容器就看你自己的意愿了。

goals: 

correctness, efficiency, easy understandable.

non-goals: 

feature completeness, conforming to standard.