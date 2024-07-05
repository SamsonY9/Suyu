# RAII

> (**R**esource **A**cquisition **I**s **I**nitialization)的缩写，翻译成中文是“**资源获取就是初始化**”

这个翻译仍然令人费解。通俗地说，所谓**RAII**就是资源在你拿到时就已经初始化好了，一旦你不再需要这个资源，该资源可以自动释放。

对于C++语言来说，即资源在构造函数中初始化（可以在构造函数中调用单独的初始化函数），在析构函数中释放或清理。常见的情形就是函数调用中，创建C++对象时分配资源，当C++对象出了作用域时会自动被清理和释放（不管这个这个对象是如何出作用域的——中间某个步骤不满足提前return掉还是正常走完全部流程后 return）。

```C++
class HeapObjectWrapper
{
public:
    HeapObjectWrapper(int size)
    {
        m_p = new char[size];
    }

    ~HeapObjectWrapper()
    {
        delete[] m_p;
        m_p = NULL;
    }

private:
    char*  m_p;
};

```

上述代码中heapObj对象一旦出了其作用域，会自动调用其析构函数释放堆内存。当然，RAII惯用法中的对资源的”分配“和”释放“的含义可以延伸出成各种外延和内涵来，如对多线程锁的获取和释放，我们在实际开发中也常常遇到以下情景：

```c++
void SomeFunction()
{
    得到某把锁；
    if (条件1)
    {
        if (条件2)
        {
            某些操作1
            释放锁;
            return;
        }
        else (条件3)
        {
            某些操作2
            释放锁;
            return;
        }
	}

    if (条件3)
    {
        某些操作3
        释放锁;
        return;
    }

    某些操作4
    释放锁;
}

```

是一段非常常见的逻辑，为了避免死锁，我们必须在每个可能退出的分支上释放锁。随着逻辑写得越来越复杂，我们忘记在某个退出分支加上释放锁的代码的可能性也越来越大。而**RAII**惯用法正好解决了这个问题，我们可以将锁包裹成一个对象，在构造函数中获取锁，在析构函数中释放锁，伪码如下：

```C++
class SomeLockGuard
{
public:
    SomeLockGuard()
    {
        //加锁
        m_lock.lock();
    }

    ~SomeLockGuard()
    {
        //解锁
        m_lock.unlock();
    }

private:
    SomeLock  m_lock;
};

void SomeFunction()
{
    SomeLockGuard lockWrapper;
    if (条件1)
    {
        if (条件2)
        {
            某些操作1
            return;
        }
        else (条件3)
        {
            某些操作2
            return;
        }
    }

    if (条件3)
    {
        某些操作3
        return;
    }

    某些操作4
}

```

使用了RAII惯用法之后，我们再也不必在每个函数出口处加上释放锁的代码了，因为锁会在函数调用结束后自动释放。

> 最后，RAII总结如下：
>
> - 资源在析构函数中被释放
> - 该类的实例是堆栈分配的
> - 资源是在构造函数中获取的。

RAII代表“资源获取是初始化”。

> 常见的例子有：
>
> - 文件操作
> - 智能指针
> - 互斥量

