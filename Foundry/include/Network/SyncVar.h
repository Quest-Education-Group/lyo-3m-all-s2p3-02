#ifndef FOUNDRY_SYNCVAR__H_
#define FOUNDRY_SYNCVAR__H_

#include "Servers/NetworkServer.h"

#define SyncVar(type, name) \
static const char CONCAT(__name__, __LINE__)[] = name; \
Syncvar<type, CONCAT(__name__, __LINE__)>

enum class SyncVarDirection : uint8
{
    RECEIVE_ONLY,
    SEND_ONLY,
    BIDIRECTIONNAL
};

struct ISyncVar
{
    virtual ~ISyncVar() = default;

protected:
    virtual char8 Size() const = 0;
    virtual void ValueChanged() = 0;
    virtual void* const Data() = 0;
    constexpr virtual SyncVarDirection GetDirection() = 0;

    friend class NetworkServer;
};

template <typename T, const char* Name, SyncVarDirection DIR = SyncVarDirection::BIDIRECTIONNAL>
struct Syncvar : ISyncVar
{
public:
    Syncvar(T const& data);
    Syncvar(Syncvar const& other) = delete;
    ~Syncvar() override;

    void ValueChanged() override;

    Syncvar& operator=(T const& other) requires (DIR == SyncVarDirection::SEND_ONLY || DIR == SyncVarDirection::BIDIRECTIONNAL);
    Syncvar& operator=(Syncvar const& other) = delete;

    T operator+(T const& other) requires requires(T a, T b)   { a + b; };
    T operator++() requires requires(T a, T b)  { a + b; };
    T operator++(int) requires requires(T a, T b)  { a + b; };
    void operator+=(T const& other) requires requires(T a, T b) { a += b; };

    T operator-(T const& other) requires requires(T a, T b)   { a - b; };
    T operator--() requires requires(T a, T b)  { a - b; };
    T operator--(int) requires requires(T a, T b)  { a - b; };
    void operator-=(T const& other) requires requires(T a, T b) { a -= b; };

    char8 Size() const override { return sizeof(T); }
    void* const Data() override { return &m_Data; }
    constexpr SyncVarDirection GetDirection() override { return DIR; }

    Event<void(T&)> OnValueChange;
private:
    void SendSyncvar();

private:
    T m_Data;
};

template <typename T, const char* Name, SyncVarDirection DIR>
Syncvar<T, Name, DIR>::Syncvar(const T& data) : m_Data(data)
{
    NetworkServer::GetRegistry()[Name] = this;
    SendSyncvar();
}

template <typename T, const char* Name, SyncVarDirection DIR>
Syncvar<T, Name, DIR>::~Syncvar()
{
      NetworkServer::GetRegistry().erase(Name);
}

template <typename T, const char* Name, SyncVarDirection DIR>
void Syncvar<T, Name, DIR>::ValueChanged()
{
    OnValueChange.Invoke(m_Data);
}

template <typename T, const char* Name, SyncVarDirection DIR>
Syncvar<T, Name, DIR>& Syncvar<T, Name, DIR>::operator=(T const& other) requires (DIR == SyncVarDirection::SEND_ONLY ||
    DIR == SyncVarDirection::BIDIRECTIONNAL)
{
    if (m_Data == other) return *this;
    m_Data = other;
    SendSyncvar();
    return *this;
}

template <typename T, const char* Name, SyncVarDirection DIR>
T Syncvar<T, Name, DIR>::operator+(T const& other) requires requires (T a, T b) { a + b; }
{
    return m_Data + other;
}

template <typename T, const char* Name, SyncVarDirection DIR>
T Syncvar<T, Name, DIR>::operator++() requires requires (T a, T b) { a + b; }
{
    return m_Data++;
}

template <typename T, const char* Name, SyncVarDirection DIR>
T Syncvar<T, Name, DIR>::operator++(int) requires requires (T a, T b) { a + b; }
{
    T temp = m_Data;
    operator++();
    return m_Data;
}

template <typename T, const char* Name, SyncVarDirection DIR>
void Syncvar<T, Name, DIR>::operator+=(T const& other) requires requires (T a, T b) { a += b; }
{
    m_Data += other;
    SendSyncvar();
}

template <typename T, const char* Name, SyncVarDirection DIR>
T Syncvar<T, Name, DIR>::operator-(T const& other) requires requires (T a, T b) { a - b; }
{
    return m_Data - other;
}

template <typename T, const char* Name, SyncVarDirection DIR>
T Syncvar<T, Name, DIR>::operator--() requires requires (T a, T b) { a - b; }
{
    return m_Data--;
}

template <typename T, const char* Name, SyncVarDirection DIR>
T Syncvar<T, Name, DIR>::operator--(int) requires requires (T a, T b) { a - b; }
{
    T temp;
    operator--();
    return temp;
}

template <typename T, const char* Name, SyncVarDirection DIR>
void Syncvar<T, Name, DIR>::operator-=(T const& other) requires requires (T a, T b) { a -= b; }
{
    m_Data -= other;
    SendSyncvar();
}

template <typename T, const char* Name, SyncVarDirection DIR>
void Syncvar<T, Name, DIR>::SendSyncvar()
{
    Package package;
    package.nameSize = strlen(Name);
    std::memcpy(package.name, Name, package.nameSize);
    package.dataSize = sizeof(m_Data);
    std::memcpy(package.data, &m_Data, package.dataSize);

    NetworkServer::SendPackage(package);
}

#endif
