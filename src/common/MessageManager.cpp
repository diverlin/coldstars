#include "MessageManager.hpp"


MessageManager& MessageManager::Instance()
{
  	static MessageManager instance;
	return instance;
}

void MessageManager::SendEvent(BaseGameEntity* receiver, const Message& message)
{
  	//receiver->HandleMessage(message);
}

void MessageManager::NewMessage(double delay,
                       		int    sender_id,
                       		int    receiver_id,
                       		int    type_id,
                       		void*  extra)
{
  	BaseGameEntity* sender   = EntityManager::Instance().GetEntityById(sender_id);
  	BaseGameEntity* receiver = EntityManager::Instance().GetEntityById(receiver_id);

  	if (receiver == NULL)
  	{
    		return;
  	}
  
    	Message message(NO_DELAY, sender_id, receiver_id, type_id, extra);
  
                  
  	if (delay <= 0.0f)                                                        
  	{
    		SendEvent(receiver, message);
    		return;
  	}
  	else
  	{
    		//double CurrentTime = Clock->GetCurrentTime(); 
    		//telegram.DispatchTime = CurrentTime + delay;
	}
	
    	messages_queue.insert(message);   
}

void MessageManager::UpdateQueue()
{ 
  	//double CurrentTime = Clock->GetCurrentTime();

  	//while( !messages_queue.empty() && (messages_queue.begin()->DispatchTime < CurrentTime) && (messages_queue.begin()->DispatchTime > 0) )
  	{
  		const Message& message = *messages_queue.begin();
  	
    		BaseGameEntity* receiver = EntityManager::Instance().GetEntityById(message.receiver_id);
    		SendEvent(receiver, message);

    		messages_queue.erase(messages_queue.begin());
  	}
}



