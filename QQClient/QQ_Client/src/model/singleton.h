#ifndef SINGLETON_H
#define SINGLETON_H

#include <QMutex>
#include <QMutexLocker>
#include <QScopedPointer>

static QMutex mutex;//实例互斥锁。static使该全局变量只在这个源文件中可用

/**
 * 单例模板类
 */
template<typename T>
class Singleton
{
public:
    ~Singleton(){}

    // 此处进行了两次m_Instance == NULL的判断，
    // 是借鉴了Java的单例模式实现时，
    // 使用的所谓的“双检锁”机制。
    // 因为进行一次加锁和解锁是需要付出对应的代价的，
    // 而进行两次判断，就可以避免多次加锁与解锁操作，
    static T& getInstance()
    {
        if(Singleton::instance==nullptr)
        {
            QMutexLocker locker(&mutex);
            if(Singleton::instance==nullptr)
            {
                Singleton::instance = new T;
            }
        }
        return *instance; //返回引用，避免用户不小心删除掉指针
    }

protected:
    Singleton(){}
    Singleton(const Singleton<T>&);
    Singleton<T>& operator=(const Singleton<T>);

private:
    static T *instance;
};

template<typename T>
T* Singleton<T>::instance;


#endif // SINGLETON_H
