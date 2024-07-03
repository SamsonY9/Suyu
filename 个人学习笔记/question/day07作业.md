1. 执行以下程序

   char *str;
   cin >> str;
   cout << str;
   若输入abcd 1234，则输出（D ）

   A   abcd
   B   abcd 1234
   C   1234
   D   输出乱码或错误





2. 执行以下程序

   char a[200] = {0};
   cin.getline(a, 200, ' ');
   cout << a;
   若输入abcd 1234，则输出（ A）

   A   abcd
   B   abcd 1234
   C   1234
   D   输出乱码或错误





3. 编写一个类，实现简单的栈。栈中有以下操作，并自行写出测试用例，每个函数都需要测试到。

   ``` c++
   class Stack {
   public:
   	bool empty();	//判断栈是否为空
   	bool full();	//判断栈是否已满
   	void push(int); //元素入栈
   	void pop();     //元素出栈
   	int  top();		//获取栈顶元素
   //...
   };
   ```

   数据成员：如果保存int型数据，需要通过int*保存元素的地址，还需要指定容量、还需要栈顶标志。



4. 安装log4cpp，尝试将log4cpp官网的示例代码跑通

​	根据讲义的安装介绍部分进行。



5. 统计一篇英文(The_Holy_Bible.txt)文章中出现的单词和词频。

   输入：某篇文章的绝对路径

   输出：词典文件dict.txt（词典中的内容为每一行都是一个“单词 词频”）

   词典的存储格式如下。

   |   a 66          |
   |   abandon 77    |
   |   public 88     |
   |    ...........  |
   |_________________|
   代码设计：

   ``` c++
   struct Record
   {
   	string _word;
   	int _frequency;
   };
   
   class Dictionary
   {
   public:
   	//......
       void read(const std::string &filename);
       void store(const std::string &filename);
   private:
       vector<Record> _dict;
   };
   ```


   提示：因为我们需要统计圣经文件中单词以及该单词在文件中出现的次数，所以可以看去读圣经文件，然后将单词存到数据结构中，并记录单词的次数，如果单词第二次出现的时候，只需要修改单词的次数（也就是这里说的单词的频率），这样当统计完整个圣经文件后，数据都存在数据结构vector了。接着遍历vector数据结构就可以将单词以及单词次数(也就是频率)存储到另外一个文件。(当然如果不存到另外一个文件，就只能打印到终端了)

   注意：在读圣经文件的时候，有可能字符串是不合法的，比如：abc123 abc？这样的字符串，处理方式两种：直接不统计这样的字符串或者将非法字母去掉即可。











