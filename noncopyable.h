#ifndef WEISHEN_BASE_NONCOPYABLE_H
#define WEISHEN_BASE_NONCOPYABLE_H

namespace weishen
{

class noncopyable
{
public:
    noncopyable(const noncopyable&) = delete;
    void operator=(const noncopyable&) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

}
#endif
