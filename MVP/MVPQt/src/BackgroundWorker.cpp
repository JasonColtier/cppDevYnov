#include "BackgroundWorker.h"

#include <iostream>
#include <ostream>

//au démarrage on dit au thread de gérer la fonction start
BackgroundWorker::BackgroundWorker() : m_isRunning(false)
{
   m_pThread = std::make_unique<std::thread>([this]()//récupération de l'instance
   {
      m_isRunning = true;
      Start();
   });
}

BackgroundWorker::~BackgroundWorker()
{
   if(m_isRunning)
      Stop();

   
}

void BackgroundWorker::Wait()
{
   std::unique_lock<std::mutex> lock(m_mutex);
   while (!m_jobs.empty())//on attend tant qu'on a pas de jobs
   {
      m_synchronizer.wait(lock);
   }
}

void BackgroundWorker::Stop()
{
   {
      std::lock_guard<std::mutex> l(m_mutex);//le mutex verouille les deux lignes du dessous
      m_isRunning = false;
      m_synchronizer.notify_one();
   }
   m_pThread->join();
}

//quand j'envoie un job de façon synchrone
void BackgroundWorker::Sync(const Job& job)
{
   std::lock_guard<std::mutex> lock(m_mutex);
   m_jobs.push_back(job);
   m_synchronizer.notify_one();//notify pour notifier le dernier mutex locké que la tache est terminée
   
}

void BackgroundWorker::Async(const Job& job)
{
   std::condition_variable event;
   auto finished = false;

   std::unique_lock<std::mutex> lock(m_mutex);
   const auto lambda = [this, &job,&finished,&event]()
   {
      job();
      std::lock_guard<std::mutex> l(m_mutex);
      finished = true;
      event.notify_one();
   };

   m_jobs.emplace_back(lambda);
   m_synchronizer.notify_one();

   while (!finished)
   {
      event.wait(lock);
   }
}

void BackgroundWorker::Start()
{
   std::unique_lock<std::mutex> lock(m_mutex);//on verouille le mutex
   while (m_isRunning)
   {
      while (m_isRunning && m_jobs.empty())
      {
         m_synchronizer.wait(lock);//on attend si on a pas de job  
      }

      while (!m_jobs.empty())
      {
         const auto size = m_jobs.size();//combien de jobs en attente
         std::cout << "pending jobs : "<<size <<std::endl;
         const auto firstJob = m_jobs.front();//on récupère le premier job
         m_jobs.pop_front();//on la sort de la liste
         lock.unlock();//on unlock parce qu'on a besoin de traitre la tache sur le thread
         firstJob(); //on la traite
         lock.lock();
      }
      m_synchronizer.notify_all();
      
   }

   m_synchronizer.notify_all();
}
