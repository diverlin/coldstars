#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <set>


const double NO_DELAY = 0.0f;
const int    NO_ADDITIONAL_INFO   = 0;

                   

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

		void SendEvent(BaseGameEntity*, const Message&);

  		MessageManager(){}
		MessageManager(const MessageManager&);
  		MessageManager& operator=(const MessageManager&);
};



#endif
