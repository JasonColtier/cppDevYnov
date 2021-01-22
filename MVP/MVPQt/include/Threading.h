#pragma once

#include "BackgroundWorker.h"

template<typename Model, typename View>
class Threading
{
public:
    Threading()
        :m_pBackgroundWorker(std::make_unique<BackgroundWorker>())
    {
        m_pBackgroundWorker->Sync([this]()//je dis d'exécuter un job sur la queue
        {
            Model(m_pBackgroundWorker.get()); // on construit un modèle dans un thread à part. N'a pas de rapport avec le modèle du Presenter !
            //le model vie dans la backgroundworker
            //get pour récupérer le pointeur
        });
        View();
    }

protected:
    std::unique_ptr<BackgroundWorker> m_pBackgroundWorker;
};
