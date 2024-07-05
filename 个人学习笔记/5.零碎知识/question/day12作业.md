1. 词频统计的作业再用map容器去实现一次，体验一下使用vector/map时程序执行的速度

   提示：++dict[word];
   
   
   
   回顾题目：
   
   统计一篇英文(The_Holy_Bible.txt)文章中出现的单词和词频。
   
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
   
      注意：在读圣经文件的时候，有可能字符串是不合法的，比如：abc123 abc？这样的字符串，处理方式两种：直接不统计这样的字符串或者将非法字母去掉即可。

> 之前用vector实现时，对于单词的内容和它出现的次数，是采用一个Record对象来存储的，再将很多个Record由vector进行存储。
>
> 实际上，可以将单词和它出现的次数组装成一个pair，由map存储这种pair

``` c++
class Dictionary
{
public:
	//......
    void read(const std::string &filename);
    void store(const std::string &filename);
private:
    map<string,int> _dict;
};
```





2. 文本查询
   该程序将读取用户指定的任意文本文件【当前目录下的china_daily.txt】，然后允许用户从该文件中查找单词。查询的结果是该单词出现的次数，并列出每次出现所在的行。如果某单词在同一行中多次出现，程序将只显示该行一次。行号按升序显示。

   要求：
   a. 它必须允许用户指明要处理的文件名字。

   b. 程序将存储该文件的内容，以便输出每个单词所在的原始行。
   vector< string > lines;

   c. 它必须将每一行分解为各个单词，并记录每个单词所在的所有行。
   在输出行号时，应保证以升序输出，并且不重复。

   map<string, set< int > > wordNumbers;
   map<string, int> dict;

   d. 对特定单词的查询将返回出现该单词的所有行的行号。

   e. 输出某单词所在的行文本时，程序必须能根据给定的行号从输入
   文件中获取相应的行。

   示例：
   使用提供的文件内容，然后查找单词 "element"。输出的前几行为：
   \---------------------------------------------
   element occurs 125 times.
   (line 62) element with a given key.
   (line 64) second element with the same key.
   (line 153) element |==| operator.
   (line 250) the element type.
   (line 398) corresponding element.
   \---------------------------------------------

   ``` c++
   //程序接口[可选]:
   class TextQuery
   {
   public:
   	//读取文件，处理内容，将需要的信息
   	void readFile(const string & filename);
       //查找单词
   	void query(const string & word);
   private:
   	//把每一行的原始信息存储下来
   	vector<string> _lines;
       //单词和行号
   	map<string, set<int> > _wordNumbers;
       //单词和词频
   	map<string, int> _dict;
   };
   
   //程序测试用例
   int main(int argc, char *argv[])
   {
   	string queryWord("hello");
   	TextQuery tq;
   	tq.readFile("test.dat");
   	tq.query(queryWord);
   	return 0;
   }
   ```

   