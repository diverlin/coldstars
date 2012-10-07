#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <set>
                 
#include "../spaceobjects/BaseSpaceEntity.hpp"   

class MessageManager
{
	public:
		static MessageManager& Instance();

  		void NewMessage(double delay,
                       		int    sender_id,
                       		int    receiver_id,
                       		int    type_id,
                       		void*  extra);

		void UpdateQueue();
		
	private:  
		std::set<Message> messages_queue;

		void SendEvent(BaseSpaceEntity*, const Message&);

  		MessageManager(){}
		MessageManager(const MessageManager&);
  		MessageManager& operator=(const MessageManager&);
};



#endif
