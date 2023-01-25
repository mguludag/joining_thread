#ifndef JOINING_THREAD_HPP
#define JOINING_THREAD_HPP

#include <thread>

class joining_thread : public std::thread
{
public:
    joining_thread() : std::thread() {}

    joining_thread( joining_thread&& other ) noexcept : std::thread(static_cast<std::thread&&>(other)) {}

    template< class Function, class... Args >
    explicit joining_thread( Function&& f, Args&&... args ) : 
        std::thread(std::forward<Function>(f), std::forward<Args>(args)...) {}

    ~joining_thread() { joinable() ? join() : void(); }

    joining_thread& operator=( joining_thread && other ) noexcept 
        { return static_cast<joining_thread&>(std::thread::operator=(static_cast<std::thread&&>(other))); };

    bool joinable() const noexcept { return std::thread::joinable(); };

    std::thread::id get_id() const noexcept { return std::thread::get_id(); };

    std::thread::native_handle_type native_handle() { return std::thread::native_handle(); }

    static unsigned int hardware_concurrency() noexcept { return std::thread::hardware_concurrency(); }

    void join() { std::thread::join(); }
    
    void detach() { std::thread::detach(); }

    void swap( joining_thread& other ) noexcept { std::thread::swap(static_cast<std::thread&>(other)); };
};

#endif
