#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "Signal.h"
#include "Trigger.h"

//suffix pour dire qu'une méthode est linkable depuis le modèle
//juste pour du débuggage, on pourrait après checker si la fonction est bien linkable

#define SUFFIX_MODEL_LINKABLE(x) x ## _linkableFromModel //##pour concaténer une stream    si x = tata  => tata_linkableFromModel
#define SUFFIX_VIEW_LINKABLE(x) x ## _linkableFromView
#define SUFFIX_EVENT(x) x ## _event
#define SUFFIX_OBS(x) x ## _obs

//va faire une déclaration de fonction pour nous
#define DEFINE_EVENT(eventName, ...) \
	Signal<__VA_ARGS__> SUFFIX_EVENT(eventName);

#define DECLARE_MODEL_FUNCTION_LINKABLE(functionName, ...) \
	void SUFFIX_MODEL_LINKABLE(functionName)(__VA_ARGS__);

#define DECLARE_VIEW_FUNCTION_LINKABLE(functionName, ...) \
	void SUFFIX_VIEW_LINKABLE(functionName)(__VA_ARGS__);

#define DEFINE_MODEL_FUNCTION_LINKABLE(className, functionName, ...) \
	void className::SUFFIX_MODEL_LINKABLE(functionName)(__VA_ARGS__)

#define DEFINE_VIEW_FUNCTION_LINKABLE(className, functionName, ...) \
	void className::SUFFIX_VIEW_LINKABLE(functionName)(__VA_ARGS__)

#define TRIG_EVENT(eventName, ...) \
	SUFFIX_EVENT(eventName)(__VA_ARGS__);

#define CALL_INSIDE_VIEW(functionName, ...) \
	SUFFIX_MODEL_LINKABLE(functionName)(__VA_ARGS__);

#define CALL_INSIDE_MODEL(functionName, ...) \
	SUFFIX_VIEW_LINKABLE(functionName)(__VA_ARGS__);

#define DISPATCH_FROM_VIEW(viewEvent, modelFunction, ...) \
	m_pView->SUFFIX_EVENT(viewEvent).Connect(m_pModel.get(), & ## __VA_ARGS__ ## ::SUFFIX_VIEW_LINKABLE(modelFunction));

#define DISPATCH_FROM_MODEL(modelEvent, viewFunction, ...) \
	m_pModel->SUFFIX_EVENT(modelEvent).Connect(m_pView.get(), & ## __VA_ARGS__ ## ::SUFFIX_MODEL_LINKABLE(viewFunction));

#define DECLARE_OBS(name, type) \
	Trigger<type> SUFFIX_OBS(name);

//sync variables nommées pareil
#define SYNC_OBS(name) \
	m_pView->SUFFIX_OBS(name).ConnectTyped([this](auto copy)	\
	{															\
		m_pModel->SUFFIX_OBS(name) = copy;						\
	});															\
	m_pModel->SUFFIX_OBS(name).ConnectTyped([this](auto copy)	\
	{															\
		m_pView->SUFFIX_OBS(name) = copy;						\
	});

//pour synchro des var nommées différemment
#define SYNC_DIFFERENT_OBS(viewName, modelName)						\
	m_pView->SUFFIX_OBS(viewName).ConnectTyped([this](auto copy)	\
	{																\
		m_pModel->SUFFIX_OBS(modelName) = copy;						\
	});																\
	m_pModel->SUFFIX_OBS(modelName).ConnectTyped([this](auto copy)	\
	{																\
		m_pView->SUFFIX_OBS(viewName) = copy;						\
	});

#endif // DISPATCHER_H
