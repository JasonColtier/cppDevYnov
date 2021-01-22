#pragma once
#include <functional>
#include <list>
#include <mutex>

using Job = std::function<void()>;
using Jobs = std::list<Job>;
//pour gérer les threads
class BackgroundWorker
{
    
public:
    BackgroundWorker();
    ~BackgroundWorker();

    void Wait();
    void Stop();
    void Sync(const Job& job);
    void Async(const Job& job);

private:
    void Start();

    std::condition_variable m_synchronizer;
    std::mutex m_mutex;//verrou pour bloquer qqc sur un thread et qu'il puisse pas être accéder depuis un autre thread
    std::unique_ptr<std::thread> m_pThread;
    Jobs m_jobs;

    
    volatile bool m_isRunning;//volatile
    //int toto = 1; si toto n'est pas volatile, c'est comme si on écrivait while(1)
    //while (toto){//avec une variable volatile on dit qu'elle peut être modifiée ailleurs
    //
    //
    //}
    
};
